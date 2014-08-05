/*
** File Name: formatter.hpp
** Author:    Aditya Ramesh
** Date:      08/02/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z0487E9FF_B46E_4414_B607_847246DE0874
#define Z0487E9FF_B46E_4414_B607_847246DE0874

#include <array>
#include <cctype>
#include <cstdint>
#include <boost/utility/string_ref.hpp>

namespace cc {

class argument
{
	static constexpr auto max_attributes = 5;

	std::array<attribute, 5> m_attrs;
	uint8_t m_attr_count{};
	uint8_t m_index{};
public:
	explicit argument(uint8_t index)
	noexcept : m_index{index} {}

	uint8_t index() const noexcept
	{ return m_index; }

	uint8_t attributes() const noexcept
	{ return m_attr_count; }

	argument& add_attribute(attribute_type t)
	noexcept
	{
		assert(m_attr_count != max_attributes);
		m_attrs[m_attr_count++] = attribute{t};
		return *this;
	}

	attribute& attribute(uint8_t n)
	noexcept
	{
		assert(n < attributes());
		return m_attrs[n];
	}

	attribute& attribute(uint8_t n)
	const noexcept
	{
		assert(n < attributes());
		return m_attrs[n];
	}
};

// TODO specialize for Args == 0

// TODO if the `m_str` buffer is used as storage for string operations, then it
// should first be imbued with the same format state as the destination stream

template <class Char, class Traits, uint8_t Args>
class formatter
{
	using string_ref = boost::basic_string_ref<Char, Traits>;
	using substr = std::tuple<size_t, size_t>;

	// This array is used to store the indices and lengths of each substring
	// in the format string that occurs between two argument strings. Note
	// that a substring may contain `$$` or `{{` that should be escaped when
	// printing.
	std::array<substr, Args + 1> m_substrs;
	std::array<arguments, Args> m_args;
	std::basic_ostringstream<Char, Traits> m_str{};
public:
	explicit formatter(const boost::basic_string_ref<Char> fmt_str)
	{
		auto cur_index  = size_t{};
		auto cur_substr = uint8_t{};
		auto cur_arg    = uint8_t{};
		auto mode       = parsing_mode{};
		start_substring(0, 0);

		while (cur_index != fmt_str.length()) {
			if (mode == outside_argument) {
				// Find the next argument.
				while (fmt_str[cur_index] != '$' &&
					cur_index != fmt_str.length()) {
					++cur_index;
				}

				if (cur_index == fmt_str.length()) {
					end_subtring(cur_index, cur_substr);
					break;
				}

				parse_argument(fmt_str, cur_index, cur_substr, cur_arg, mode);
			}
			else if (mode == inside_attribute_list) {
				// Find the beginning of the next attribute.
				while (std::isspace(fmt_str[cur_index]) &&
					cur_index != fmt_str.length()) {
					++cur_index;
				}

				if (cur_index == fmt_str.length()) {
					throw std::runtime_error{"Unclosed attribute list."};
				}
				else if (fmt_str[cur_index] == '}') {
					++cur_index;
					mode = outside_attribute;
					continue;
				}

				parse_attribute(fmt_str, cur_index, cur_substr, cur_arg, mode);
			}
			// TODO should we check for/implement other modes?
			// if not, change the above else if to else
		}

		// TODO check that mode == outside_argument.
	}
private:
	void parse_argument(
		const boost::string_ref fmt_str,
		uint8_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& cur_arg,
		parsing_mode mode
	)
	{
		/*
		** At this point, `fmt_str[i] == '$'`.
		*/
		if (cur_index == fmt_str.length() - 1) {
			add_argument(cur_arg, cur_arg);
			end_substring(cur_index, cur_substr);
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
				return;
			}
		}

		if (fmr_str[cur_index] != '{') {
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

		mode = inside_attribute_list;
	}

	bool is_attribute_character(Char c)
	const noexcept
	{
		return std::isalpha(c) || c == '$' || c == '%';
	}

	void parse_attribute(
		const boost::string_ref fmt_str,
		uint8_t& cur_index,
		uint8_t& cur_substr,
		uint8_t& cur_arg,
		parsing_mode mode
	)
	{
		auto attr_start = cur_index;
		while (is_attribute_character(fmt_str[cur_index]) &&
			cur_index != fmt_str.length())
		{
			++cur_index;
		}

		if (cur_index == fmt_str.length()) {
			throw std::runtime_error{"Unclosed attribute list."};
		}

		add_attribute(fmt_str.substr(attr_start,
			cur_index - attr_start), cur_arg);
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
		break;
	}

	void add_argument(uint8_t& cur_arg, uint8_t index)
	{
		if (cur_arg >= Args) {
			throw std::runtime_error{"Too many arguments."};
		}
		if (index >= Args) {
			throw std::runtime_error{"Argument index too large."};
		}
		m_args[cur_arg++] = argument{index};
	}

	void add_attribute(const boost::string_ref name, uint8_t cur_arg)
	{

	}
};

}

#endif
