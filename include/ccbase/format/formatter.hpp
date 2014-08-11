/*
** File Name: formatter.hpp
** Author:    Aditya Ramesh
** Date:      08/02/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z0487E9FF_B46E_4414_B607_847246DE0874
#define Z0487E9FF_B46E_4414_B607_847246DE0874

#include <cctype>
#include <tuple>
#include <utility>

#include <ccbase/platform/attributes.hpp>
#include <ccbase/format/format_argument.hpp>
#include <ccbase/format/argument_wrapper.hpp>

namespace cc {

template <class Char, class Traits>
class basic_formatter
{
public:
	#ifdef CC_FORMAT_MAX_ARG_COUNT
		#if CC_FORMAT_MAX_ARG_COUNT > 255
			#error "Maximum argument count must be below 255."
		#endif
		static constexpr auto max_arg_count = CC_FORMAT_MAX_ARG_COUNT;
	#else
		static constexpr auto max_arg_count = 16;
	#endif

	using ostream           = std::basic_ostream<Char, Traits>;
	using string_ref        = boost::basic_string_ref<Char, Traits>;
	using format_argument_t = basic_format_argument<Char, Traits>;
	using buffer_type       = std::basic_ostringstream<Char, Traits>;
	using index_length_pair = std::tuple<size_t, size_t>;
private:
	string_ref m_fmt_str;

	/*
	** This array is used to store the indices and lengths of each
	** _substring_ in the format string, i.e. a string that occurs between
	** two argument strings. Note that:
	**   - A substring may contain a `$$` or `{{` that should be escaped
	**   when printing.
	**   - A substring may have length zero. This can happen in cases like
	**   the following: "$" (two empty substrings), "${}${}" (three empty
	**   substrings).
	*/
	std::array<index_length_pair, max_arg_count + 1> m_substrs;
	std::array<format_argument_t, max_arg_count> m_lists;
	mutable buffer_type m_buf{};
	uint8_t m_arg_count{0};
	uint8_t m_fmt_args{0};
public:
	explicit basic_formatter(const string_ref& fmt_str) :
	m_fmt_str{fmt_str}
	{
		auto cur_index   = size_t{};
		auto cur_substr  = uint8_t{};
		auto outside_arg = bool{true};
		start_substring(0, 0);

		for (;;) {
			if (outside_arg) {
				// Find the next argument.
				while (cur_index != m_fmt_str.length() &&
					m_fmt_str[cur_index] != '$')
				{
					++cur_index;
				}
				if (cur_index == m_fmt_str.length()) {
					end_substring(cur_index, cur_substr);
					break;
				}

				parse_argument(cur_index, cur_substr, m_fmt_args,
					outside_arg);
			}
			else {
				// Find the beginning of the next attribute.
				while (cur_index != m_fmt_str.length() &&
					std::isspace(m_fmt_str[cur_index]))
				{
					++cur_index;
				}

				if (cur_index == m_fmt_str.length()) {
					throw std::runtime_error{"Unclosed attribute list."};
				}
				else if (m_fmt_str[cur_index] == '}') {
					++cur_index;
					outside_arg = true;
					start_substring(cur_index, cur_substr);

					/*
					** We need to end the last substring
					** manually in certain cases, e.g. when
					** `m_fmt_str == "${}"`.
					*/
					if (cur_index == m_fmt_str.length()) {
						end_substring(cur_index, cur_substr);
						return;
					}
					continue;
				}

				parse_attribute(cur_index, cur_substr, m_fmt_args,
					outside_arg);
			}
		}

		assert(outside_arg);
	}

	const string_ref format_string()
	const noexcept { return m_fmt_str; }

	const index_length_pair& substring(uint8_t n)
	const noexcept { return m_substrs[n]; }

	const format_argument_t& format_argument(uint8_t n)
	const noexcept { return m_lists[n]; }

	const format_argument_t* format_argument_pointer()
	const noexcept { return m_lists.data(); }

	uint8_t arguments() const noexcept 
	{ return m_arg_count; }

	uint8_t format_arguments() const noexcept
	{ return m_fmt_args; }

	buffer_type& buffer() const noexcept
	{ return m_buf; }
private:
	void parse_argument(
		size_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& m_fmt_args,
		bool& outside_arg
	)
	{
		/*
		** At this point, `m_fmt_str[i] == '$'`.
		*/
		if (cur_index == m_fmt_str.length() - 1) {
			add_format_argument(m_fmt_args, m_fmt_args);
			end_substring(cur_index, cur_substr);
			++cur_index;
			start_substring(cur_index, cur_substr);
			return;
		}

		auto dollar_index = cur_index;
		++cur_index;

		if (m_fmt_str[cur_index] == '$') {
			++cur_index;
			return;
		}

		// Set the index of the next argument if it is not specified.
		auto index = uint8_t(m_arg_count + 1);

		// Does the argument have an explicit index?
		if (std::isdigit(m_fmt_str[cur_index])) {
			index = 0;

			// Parse the index of the argument.
			do {
				auto tmp = index;
				index = 10 * index + (m_fmt_str[cur_index] - '0');
				if (index < tmp) {
					// Overflow occurred.
					throw std::runtime_error{"Argument index "
						"too large."};
				}
				++cur_index;
			}
			while (cur_index != m_fmt_str.length() &&
				std::isdigit(m_fmt_str[cur_index]));
			
			if (index == 0) {
				throw std::runtime_error{"Argument indices are "
					"one-based."};
			}
			else if (index > m_arg_count + 1) {
				throw std::runtime_error{"Argument index greater "
					"than that of any prior argument."};
			}

			if (cur_index == m_fmt_str.length()) {
				add_format_argument(m_fmt_args, index);
				end_substring(dollar_index, cur_substr);
				start_substring(cur_index, cur_substr);
				return;
			}
		}

		/*
		** At this point, we can be sure that we have reached a valid
		** argument.
		*/
		add_format_argument(m_fmt_args, index);
		end_substring(dollar_index, cur_substr);

		if (m_fmt_str[cur_index] != '{') {
			start_substring(cur_index, cur_substr);
			return;
		}

		/*
		** At this point, `m_fmt_str[cur_index] == '{'`.
		*/
		if (cur_index == m_fmt_str.length() - 1) {
			throw std::runtime_error{"Unclosed attribute list."};
		}

		++cur_index;
		if (m_fmt_str[cur_index] == '{') {
			start_substring(cur_index, cur_substr);
			++cur_index;
			return;
		}

		outside_arg = false;
	}

	bool is_attribute_character(Char c)
	const noexcept
	{
		return std::isalpha(c) || c == '%';
	}

	void parse_attribute(
		size_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& m_fmt_args,
		bool& outside_arg
	)
	{
		auto attr_start = cur_index;

		while (cur_index != m_fmt_str.length() &&
			is_attribute_character(m_fmt_str[cur_index]))
		{
			++cur_index;
		}
		if (cur_index == m_fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute list."};
		}

		add_attribute(m_fmt_str.substr(attr_start,
			cur_index - attr_start), m_fmt_args - 1);

		while (cur_index != m_fmt_str.length() &&
			std::isspace(m_fmt_str[cur_index]))
		{
			++cur_index;
		}
		if (cur_index == m_fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute list."};
		}

		if (m_fmt_str[cur_index] == '(') {
			++cur_index;
			parse_attribute_arguments(cur_index, cur_substr,
				m_fmt_args, outside_arg);

			while (std::isspace(m_fmt_str[cur_index] &&
				cur_index != m_fmt_str.length())) {
				++cur_index;
			}
			if (cur_index == m_fmt_str.length()) {
				throw std::runtime_error{"Unclosed attribute list."};
			}
		}

		if (m_fmt_str[cur_index] == ',') {
			++cur_index;
			return;
		}
		if (m_fmt_str[cur_index] == '}') {
			++cur_index;
			outside_arg = true;
			start_substring(cur_index, cur_substr);
			return;
		}
		throw std::runtime_error{"Invalid character after attribute."};
	}

	void parse_attribute_arguments(
		size_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& m_fmt_args,
		bool& outside_arg
	)
	{
		for (;;) {
			while (cur_index != m_fmt_str.length() &&
				std::isspace(m_fmt_str[cur_index]))
			{
				++cur_index;
			}
			if (cur_index == m_fmt_str.length()) {
				throw std::runtime_error{"Unclosed attribute argument list."};
			}

			if (m_fmt_str[cur_index] == ')') {
				++cur_index;
				return;
			}
			else {
				parse_attribute_argument(cur_index, cur_substr,
					m_fmt_args, outside_arg);
			}
		}
	}

	bool is_attribute_argument_character(Char c)
	const noexcept
	{
		return std::isalpha(c) || std::isdigit(c) || c == '.' ||
			c == '-' || c == '_';
	}

	void parse_attribute_argument(
		size_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& m_fmt_args,
		bool& outside_arg
	)
	{
		(void)cur_substr;
		(void)outside_arg;

		if (cur_index == m_fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute argument "
				"list."};
		}

		auto arg_start = cur_index;

		if (m_fmt_str[cur_index] == '\'') {
			do {
				++cur_index;
			}
			while (cur_index != m_fmt_str.length() &&
				m_fmt_str[cur_index] != '\'');

			if (cur_index == m_fmt_str.length()) {
				throw std::runtime_error{"Unclosed attribute "
					"argument list."};
			}
			++cur_index;
		}
		else {
			while (cur_index != m_fmt_str.length() &&
				is_attribute_argument_character(m_fmt_str[cur_index]))
			{
				++cur_index;
			}
		}

		add_attribute_argument(m_fmt_str.substr(arg_start,
			cur_index - arg_start), m_fmt_args - 1);

		while (cur_index != m_fmt_str.length() &&
			std::isspace(m_fmt_str[cur_index]))
		{
			++cur_index;
		}
		if (cur_index == m_fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute argument "
				"list."};
		}

		if (m_fmt_str[cur_index] == ',') {
			++cur_index;
		}
		else if (m_fmt_str[cur_index] != ')') {
			throw std::runtime_error{"Unexpected character in "
				"attribute argument list."};
		}
	}

	void start_substring(size_t cur_index, uint8_t cur_substr)
	{
		if (cur_substr > max_arg_count) { assert(false); }
		std::get<0>(m_substrs[cur_substr]) = cur_index;
	}

	void end_substring(size_t& cur_index, uint8_t& cur_substr)
	{
		std::get<1>(m_substrs[cur_substr]) =
			cur_index - std::get<0>(m_substrs[cur_substr]);
		++cur_substr;
	}

	void add_format_argument(uint8_t& m_fmt_args, uint8_t index)
	{
		if (index > max_arg_count) {
			throw std::runtime_error{"Argument index past limit. "
				"Set CC_FORMAT_MAX_ARG_COUNT to increase this "
				"limit."};
		}
		m_arg_count = std::max(m_arg_count, index);
		m_lists[m_fmt_args] = format_argument_t(index - 1);
		++m_fmt_args;
	}

	void add_attribute(const string_ref name, uint8_t m_fmt_args)
	{
		assert(m_fmt_args < max_arg_count);
		m_lists[m_fmt_args].add_attribute(name);
	}

	void add_attribute_argument(const string_ref name, uint8_t m_fmt_args)
	{
		assert(m_fmt_args < max_arg_count);
		auto& list = m_lists[m_fmt_args];
		list[list.attributes() - 1].add_argument(name);
	}
};

template <class Char, class Traits>
void print_format_substring(
	const boost::basic_string_ref<Char, Traits>& substr,
	std::basic_ostream<Char, Traits>& os
)
{
	auto cur_index = size_t{};

	do {
		// Do we need to escape a '$' or '{'?
		if (cur_index != substr.length() - 1 && substr[cur_index] == '$') {
			if (substr[cur_index + 1] == '$') {
				os << '$';
				cur_index += 2;
			}
			else if (substr[cur_index + 1] == '{') {
				os << "${";
				cur_index += 3;
			}
		}
		else {
			os << substr[cur_index];
			++cur_index;
		}
	}
	while (cur_index != substr.length());
}

template <class Char, class Traits, class... Args>
void apply_impl(
	const basic_formatter<Char, Traits>& fmt,
	std::basic_ostream<Char, Traits>& dst,
	Args&&... args
)
{
	if (fmt.arguments() == 0) {
		print_format_substring(fmt.format_string(), dst);
		return;
	}

	auto arr = std::array<const argument_base*, sizeof...(Args)>{{&args...}};
	fmt.buffer().copyfmt(dst);

	for (auto i = 0; i != 2 * fmt.format_arguments() + 1; ++i) {
		if (i % 2 == 0) {
			auto& pair = fmt.substring(i / 2);
			auto idx   = std::get<0>(pair);
			auto len   = std::get<1>(pair);
			if (len == 0) { continue; }

			auto& fmt_str = fmt.format_string();
			auto substr   = fmt_str.substr(idx, len);
			print_format_substring(substr, dst);
		}
		else {
			auto& arg = fmt.format_argument((i - 1) / 2);
			auto restore = (bool)arg.count(attribute_function::adds_manipulators);
			std::basic_ios<Char, Traits> state{nullptr};

			if (restore) { state.copyfmt(dst); }
			arr[arg.index()]->apply((i - 1) / 2);
			if (restore) { dst.copyfmt(state); }
		}
	}
}

template <class Char, class Traits, class... Args>
void apply(
	const basic_formatter<Char, Traits>& fmt,
	std::basic_ostream<Char, Traits>& dst,
	Args&&... args
)
{
	apply_impl(fmt, dst, 
		(const argument_base&)make_argument_wrapper(
			args, dst, fmt.buffer(), fmt.format_argument_pointer()
		)...
	);
}

using formatter = basic_formatter<char, std::char_traits<char>>;

template <uint8_t Args>
using wformatter = basic_formatter<wchar_t, std::char_traits<wchar_t>>;

template <uint8_t Args>
using u16formatter = basic_formatter<char16_t, std::char_traits<char16_t>>;

template <uint8_t Args>
using u32formatter = basic_formatter<char32_t, std::char_traits<char32_t>>;

}

#endif
