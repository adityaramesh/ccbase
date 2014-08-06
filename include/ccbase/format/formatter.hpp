/*
** File Name: formatter.hpp
** Author:    Aditya Ramesh
** Date:      08/02/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z0487E9FF_B46E_4414_B607_847246DE0874
#define Z0487E9FF_B46E_4414_B607_847246DE0874

#include <cctype>
#include <ccbase/format/argument.hpp>

namespace cc {

// TODO specialize for Args == 0

// TODO if the `m_str` buffer is used as storage for string operations, then it
// should first be imbued with the same format state as the destination stream

template <class Char, class Traits, uint8_t Args>
class formatter
{
	using string_ref = boost::basic_string_ref<Char, Traits>;
	using m_argument = argument<Char, Traits>;
	using substr = std::tuple<size_t, size_t>;

	/*
	** This array is used to store the indices and lengths of each substring
	** in the format string that occurs between two argument strings. Note
	** that:
	**   - A substring may contain a `$$` or `{{` that should be escaped
	**   when printing.
	**   - A substring may have length zero. This is can happen in cases
	**   like the following: "$" (two empty substrings), "${}${}" (three
	**   empty substrings).
	*/
	std::array<substr, Args + 1> m_substrs;
	std::array<m_argument, Args> m_args;
	std::basic_ostringstream<Char, Traits> m_str{};
public:
	explicit formatter(const boost::basic_string_ref<Char> fmt_str)
	{
		auto cur_index   = size_t{};
		auto cur_substr  = uint8_t{};
		auto cur_arg     = uint8_t{};
		auto outside_arg = bool{true};
		start_substring(0, 0);

		for (;;) {
			if (outside_arg) {
				// Find the next argument.
				while (cur_index != fmt_str.length() &&
					fmt_str[cur_index] != '$')
				{
					++cur_index;
				}
				if (cur_index == fmt_str.length()) {
					end_substring(cur_index, cur_substr);
					break;
				}

				parse_argument(fmt_str, cur_index, cur_substr,
					cur_arg, outside_arg);
			}
			else {
				// Find the beginning of the next attribute.
				while (cur_index != fmt_str.length() &&
					std::isspace(fmt_str[cur_index]))
				{
					++cur_index;
				}

				if (cur_index == fmt_str.length()) {
					throw std::runtime_error{"Unclosed attribute list."};
				}
				else if (fmt_str[cur_index] == '}') {
					++cur_index;
					outside_arg = true;
					start_substring(cur_index, cur_substr);
					continue;
				}

				parse_attribute(fmt_str, cur_index, cur_substr,
					cur_arg, outside_arg);
			}
		}
		
		assert(cur_substr == Args);
		assert(outside_arg);
	}
private:
	void parse_argument(
		const boost::string_ref fmt_str,
		uint8_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& cur_arg,
		bool& outside_arg
	)
	{
		/*
		** At this point, `fmt_str[i] == '$'`.
		*/
		if (cur_index == fmt_str.length() - 1) {
			add_argument(cur_arg, cur_arg);
			end_substring(cur_index, cur_substr);
			++cur_index;
			start_substring(cur_index, cur_substr);
			return;
		}

		auto dollar_index = cur_index;
		++cur_index;

		if (fmt_str[cur_index] == '$') {
			++cur_index;
			return;
		}

		// If the index of the argument is not specified, then it is set
		// to `cur_arg`.
		auto index = size_t{cur_arg};

		// Does the argument have an explicit index?
		if (std::isdigit(fmt_str[cur_index])) {
			index = 0;

			// Parse the index of the argument.
			do {
				auto tmp = index;
				index = 10 * index + (fmt_str[cur_index] - '0');
				if (index < tmp) {
					// Overflow occurred.
					throw std::runtime_error{"Argument index too large."};
				}
				++cur_index;
			}
			while (cur_index != fmt_str.length() &&
				std::isdigit(fmt_str[cur_index]));
			
			if (index >= Args) {
				throw std::runtime_error{"Argument index too large."};
			}

			if (cur_index == fmt_str.length()) {
				add_argument(cur_arg, index);
				end_substring(dollar_index, cur_substr);
				start_substring(cur_index, cur_substr);
				return;
			}
		}

		if (fmt_str[cur_index] != '{') {
			add_argument(cur_arg, index);
			end_substring(dollar_index, cur_substr);
			start_substring(cur_index, cur_substr);
			return;
		}

		/*
		** At this point, `fmt_str[cur_index] == '{'`.
		*/
		if (cur_index == fmt_str.length() - 1) {
			throw std::runtime_error{"Unclosed attribute list."};
		}

		++cur_index;
		if (fmt_str[cur_index] == '{') {
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
		const boost::string_ref fmt_str,
		uint8_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& cur_arg,
		bool& outside_arg
	)
	{
		auto attr_start = cur_index;

		while (cur_index != fmt_str.length() &&
			is_attribute_character(fmt_str[cur_index]))
		{
			++cur_index;
		}
		if (cur_index == fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute list."};
		}

		add_attribute(fmt_str.substr(attr_start,
			cur_index - attr_start), cur_arg);

		while (cur_index != fmt_str.length() &&
			std::isspace(fmt_str[cur_index]))
		{
			++cur_index;
		}
		if (cur_index == fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute list."};
		}

		if (fmt_str[cur_index] == '(') {
			++cur_index;
			parse_attribute_arguments(fmt_str, cur_index,
				cur_substr, cur_arg, outside_arg);

			while (std::isspace(fmt_str[cur_index] &&
				cur_index != fmt_str.length())) {
				++cur_index;
			}
			if (cur_index == fmt_str.length()) {
				throw std::runtime_error{"Unclosed attribute list."};
			}
		}

		if (fmt_str[cur_index] == ',') {
			++cur_index;
			return;
		}
		if (fmt_str[cur_index] == '}') {
			++cur_index;
			outside_arg = true;
			start_substring(cur_index, cur_substr);
			return;
		}
		throw std::runtime_error{"Invalid character after attribute."};
	}

	void parse_attribute_arguments(
		const boost::string_ref fmt_str,
		uint8_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& cur_arg,
		bool& outside_arg
	)
	{
		for (;;) {
			while (cur_index != fmt_str.length() &&
				std::isspace(fmt_str[cur_index]))
			{
				++cur_index;
			}
			if (cur_index == fmt_str.length()) {
				throw std::runtime_error{"Unclosed attribute argument list."};
			}

			if (fmt_str[cur_index] == ')') {
				++cur_index;
				return;
			}
			else {
				parse_attribute_argument(fmt_str, cur_index,
					cur_substr, cur_arg, outside_arg);
			}
		}
	}

	bool is_attribute_argument_character(Char c)
	const noexcept
	{
		return std::isalpha(c) || std::isdigit(c);
	}

	void parse_attribute_argument(
		const boost::string_ref fmt_str,
		uint8_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& cur_arg,
		bool& outside_arg
	)
	{
		if (cur_index == fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute argument "
				"list."};
		}

		auto arg_start = cur_index;

		if (fmt_str[cur_index] == '\'') {
			do {
				++cur_index;
			}
			while (cur_index != fmt_str.length() &&
				fmt_str[cur_index] != '\'');
		}
		else {
			while (cur_index != fmt_str.length() &&
				is_attribute_argument_character(fmt_str[cur_index]))
			{
				++cur_index;
			}
		}

		add_attribute_argument(fmt_str.substr(arg_start,
			cur_index - arg_start), cur_arg);

		while (cur_index != fmt_str.length() &&
			std::isspace(fmt_str[cur_index]))
		{
			++cur_index;
		}
		if (cur_index == fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute argument "
				"list."};
		}

		if (fmt_str[cur_arg] == ',') {
			++cur_arg;
		}
		else if (fmt_str[cur_arg] != ')') {
			throw std::runtime_error{"Unexpected character in "
				"attribute argument list."};
		}
	}

	void start_substring(uint8_t& cur_index, uint8_t& cur_substr)
	{
		if (cur_substr == Args + 1) {
			throw std::runtime_error{"Too many arguments."};
		}
		std::get<0>(m_substrs[cur_substr]) = cur_index;
	}

	void end_substring(uint8_t& cur_index, uint8_t& cur_substr)
	{
		std::get<1>(m_substrs[cur_substr]) =
			cur_index - std::get<0>(m_substrs[cur_substr]);
		++cur_substr;
	}

	void add_argument(uint8_t& cur_arg, uint8_t index)
	{
		if (cur_arg >= Args) {
			throw std::runtime_error{"Too many arguments."};
		}
		if (index >= Args) {
			throw std::runtime_error{"Argument index too large."};
		}
		m_args[cur_arg++] = m_argument{index};
	}

	void add_attribute(const string_ref name, uint8_t cur_arg)
	{
		m_args[cur_arg].add_attribute(name);
	}

	void add_attribute_argument(const string_ref name, uint8_t cur_arg)
	{
		m_args[cur_arg][m_args[cur_arg].attributes() - 1].
			add_argument(name);
	}
};

}

#endif
