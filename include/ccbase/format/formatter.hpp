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

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <ccbase/format/argument.hpp>
#include <ccbase/platform/attributes.hpp>

namespace cc {

template <uint8_t CurrentIndex, uint8_t TargetIndex, class... Args>
struct select_argument
{
	using next     = select_argument<CurrentIndex + 1, TargetIndex, Args...>;
	using arg_list = boost::mpl::vector<Args...>;
	using target   = typename boost::mpl::at_c<arg_list, TargetIndex>::type;
	
	template <class Arg, class... Args_>
	static CC_ALWAYS_INLINE
	target apply(Arg&&, Args_&&... args)
	{ return next::apply(std::forward<Args_>(args)...); }
};

template <uint8_t TargetIndex, class... Args>
struct select_argument<TargetIndex, TargetIndex, Args...>
{
	using arg_list = boost::mpl::vector<Args...>;
	using target   = typename boost::mpl::at_c<arg_list, TargetIndex>::type;
	
	template <class Arg>
	static CC_ALWAYS_INLINE
	target apply(Arg&& arg)
	{ return std::forward<Arg>(arg); }
};

template <class Char, class Traits, uint8_t Args>
class basic_formatter;

/*
** Prints a substring of a format string, escaping any characters as needed.
*/
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

template <
	bool    PrintArgument,
	uint8_t ArgumentIndex,
	uint8_t SubstringIndex,
	uint8_t MaxSubstringIndex
>
struct formatter_helper;

template <
	uint8_t ArgumentIndex,
	uint8_t SubstringIndex,
	uint8_t MaxSubstringIndex
>
struct formatter_helper<
	true,
	ArgumentIndex,
	SubstringIndex,
	MaxSubstringIndex
>
{
	using next = formatter_helper<
		false,
		ArgumentIndex + 1,
		SubstringIndex,
		MaxSubstringIndex
	>;

	template <
		class Char,
		class Traits,
		uint8_t ArgCount,
		class... Args
	>
	static CC_ALWAYS_INLINE
	void apply(
		const basic_formatter<Char, Traits, ArgCount>& fmt,
		std::basic_ostream<Char, Traits>& os,
		Args&&... args
	)
	{
		auto& arg = fmt.argument(ArgumentIndex);
		auto restore = (bool)arg.count(attribute_function::adds_manipulators);
		std::basic_ios<Char, Traits> state{nullptr};

		if (restore) {
			state.copyfmt(os);
		}

		/*
		** XXX: Currently, the index of the argument is unused. This is
		** because it's not possible to get an element from parameter
		** pack during runtime.
		*/
		using helper = select_argument<0, ArgumentIndex, Args...>;
		auto val = helper::apply(std::forward<Args>(args)...);
		cc::apply(arg, val, os, fmt.buffer());

		if (restore) {
			os.copyfmt(state);
		}

		next::apply(fmt, os, std::forward<Args>(args)...);
	}
};

template <
	uint8_t ArgumentIndex,
	uint8_t SubstringIndex,
	uint8_t MaxSubstringIndex
>
struct formatter_helper<
	false,
	ArgumentIndex,
	SubstringIndex,
	MaxSubstringIndex
>
{
	using next = formatter_helper<
		true,
		ArgumentIndex,
		SubstringIndex + 1,
		MaxSubstringIndex
	>;

	template <
		class Char,
		class Traits,
		uint8_t ArgCount,
		class... Args
	>
	static CC_ALWAYS_INLINE
	void apply(
		const basic_formatter<Char, Traits, ArgCount>& fmt,
		std::basic_ostream<Char, Traits>& os,
		Args&&... args
	)
	{
		auto& pair = fmt.substring(SubstringIndex);
		auto idx   = std::get<0>(pair);
		auto len   = std::get<1>(pair);

		if (len == 0) {
			next::apply(fmt, os, std::forward<Args>(args)...);
			return;
		}

		auto& fmt_str = fmt.format_string();
		auto substr   = fmt_str.substr(idx, len);

		assert(idx != fmt_str.length());
		print_format_substring(substr, os);
		next::apply(fmt, os, std::forward<Args>(args)...);
	}
};

template <
	uint8_t ArgumentIndex,
	uint8_t MaxSubstringIndex
>
struct formatter_helper<
	false,
	ArgumentIndex,
	MaxSubstringIndex,
	MaxSubstringIndex
>
{
	template <
		class Char,
		class Traits,
		uint8_t ArgCount,
		class... Args
	>
	static CC_ALWAYS_INLINE
	void apply(
		const basic_formatter<Char, Traits, ArgCount>& fmt,
		std::basic_ostream<Char, Traits>& os,
		Args&&...
	)
	{
		auto& pair = fmt.substring(MaxSubstringIndex);
		auto idx   = std::get<0>(pair);
		auto len   = std::get<1>(pair);

		if (len == 0) {
			return;
		}

		auto& fmt_str = fmt.format_string();
		auto substr   = fmt_str.substr(idx, len);

		assert(idx != fmt_str.length());
		print_format_substring(substr, os);
	}
};

template <class Char, class Traits, uint8_t Args>
class basic_formatter
{
public:
	using ostream           = std::basic_ostream<Char, Traits>;
	using string_ref        = boost::basic_string_ref<Char, Traits>;
	using argument_type     = argument<Char, Traits>;
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
	std::array<index_length_pair, Args + 1> m_substrs;
	std::array<argument_type, Args> m_args;
	mutable buffer_type m_buf{};
public:
	explicit basic_formatter(const string_ref fmt_str) :
	m_fmt_str{fmt_str}
	{
		auto cur_index   = size_t{};
		auto cur_substr  = uint8_t{};
		auto cur_arg     = uint8_t{};
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

				parse_argument(cur_index, cur_substr, cur_arg,
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
					continue;
				}

				parse_attribute(cur_index, cur_substr, cur_arg,
					outside_arg);
			}
		}

		assert(outside_arg);

		/*
		** We need to end the last substring manually in certain cases,
		** e.g. when `m_fmt_str == "${}"`.
		*/
		if (cur_substr == Args) {
			assert(std::get<0>(m_substrs[cur_substr]) == m_fmt_str.length());
			end_substring(cur_index, cur_substr);
		}
		if (cur_substr != Args + 1) {
			throw std::runtime_error{"More arguments declared than "
				"provided."};
		}
	}

	const string_ref format_string()
	const noexcept { return m_fmt_str; }

	const index_length_pair& substring(uint8_t n)
	const noexcept { return m_substrs[n]; }

	const argument_type& argument(uint8_t n)
	const noexcept { return m_args[n]; }

	buffer_type& buffer() const noexcept
	{ return m_buf; }
private:
	void parse_argument(
		size_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& cur_arg,
		bool& outside_arg
	)
	{
		/*
		** At this point, `m_fmt_str[i] == '$'`.
		*/
		if (cur_index == m_fmt_str.length() - 1) {
			add_argument(cur_arg, cur_arg);
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

		// If the index of the argument is not specified, then it is set
		// to `cur_arg`.
		auto index = uint8_t{cur_arg};

		// Does the argument have an explicit index?
		if (std::isdigit(m_fmt_str[cur_index])) {
			index = 0;

			// Parse the index of the argument.
			do {
				auto tmp = index;
				index = 10 * index + (m_fmt_str[cur_index] - '0');
				if (index < tmp) {
					// Overflow occurred.
					throw std::runtime_error{"Argument index too large."};
				}
				++cur_index;
			}
			while (cur_index != m_fmt_str.length() &&
				std::isdigit(m_fmt_str[cur_index]));
			
			if (index > Args) {
				throw std::runtime_error{"Argument index too large."};
			}

			if (cur_index == m_fmt_str.length()) {
				add_argument(cur_arg, index);
				end_substring(dollar_index, cur_substr);
				start_substring(cur_index, cur_substr);
				return;
			}
		}

		/*
		** At this point, we can be sure that we have reached a valid
		** argument.
		*/
		add_argument(cur_arg, index);
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
		uint8_t& cur_arg,
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
			cur_index - attr_start), cur_arg - 1);

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
				cur_arg, outside_arg);

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
		uint8_t& cur_arg,
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
					cur_arg, outside_arg);
			}
		}
	}

	bool is_attribute_argument_character(Char c)
	const noexcept
	{
		return std::isalpha(c) || std::isdigit(c);
	}

	void parse_attribute_argument(
		size_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& cur_arg,
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
			cur_index - arg_start), cur_arg - 1);

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
		if (cur_substr == Args + 1) {
			throw std::runtime_error{"Too many arguments."};
		}
		std::get<0>(m_substrs[cur_substr]) = cur_index;
	}

	void end_substring(size_t& cur_index, uint8_t& cur_substr)
	{
		std::get<1>(m_substrs[cur_substr]) =
			cur_index - std::get<0>(m_substrs[cur_substr]);
		++cur_substr;
	}

	void add_argument(uint8_t& cur_arg, uint8_t index)
	{
		if (cur_arg >= Args) {
			throw std::runtime_error{"More arguments declared "
				"than provided."};
		}
		if (index > Args) {
			throw std::runtime_error{"Argument index too large."};
		}
		m_args[cur_arg++] = argument_type{index};
	}

	void add_attribute(const string_ref name, uint8_t cur_arg)
	{
		assert(cur_arg < Args);
		m_args[cur_arg].add_attribute(name);
	}

	void add_attribute_argument(const string_ref name, uint8_t cur_arg)
	{
		assert(cur_arg < Args);
		m_args[cur_arg][m_args[cur_arg].attributes() - 1].
			add_argument(name);
	}
};

template <class Char, class Traits>
class basic_formatter<Char, Traits, 0>
{
public:
	using string_ref = boost::basic_string_ref<Char, Traits>;
private:
	string_ref m_fmt_str;
public:
	explicit basic_formatter(const string_ref fmt_str) :
	m_fmt_str{fmt_str} {}

	const string_ref format_string()
	const noexcept { return m_fmt_str; }
};

template <class Char, class Traits, class... Args>
void apply(
	const basic_formatter<Char, Traits, sizeof...(Args)>& fmt,
	std::basic_ostream<Char, Traits>& dst,
	Args&&... args
)
{
	using helper = formatter_helper<false, 0, 0, sizeof...(Args)>;
	fmt.buffer().copyfmt(dst);
	helper::apply(fmt, dst, std::forward<Args>(args)...);
}

template <class Char, class Traits>
void apply(
	const basic_formatter<Char, Traits, 0>& fmt,
	std::basic_ostream<Char, Traits>& dst
)
{
	print_format_substring(fmt.format_string(), dst);
}

template <uint8_t Args>
using formatter = basic_formatter<char, std::char_traits<char>, Args>;

template <uint8_t Args>
using wformatter = basic_formatter<wchar_t, std::char_traits<wchar_t>, Args>;

template <uint8_t Args>
using u16formatter = basic_formatter<char16_t, std::char_traits<char16_t>, Args>;

template <uint8_t Args>
using u32formatter = basic_formatter<char32_t, std::char_traits<char32_t>, Args>;

}

#endif
