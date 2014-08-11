/*
** File Name: argument_wrapper.hpp
** Author:    Aditya Ramesh
** Date:      08/10/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z4C8EA434_F0E8_4D5D_A416_CBA8FC4FCAEF
#define Z4C8EA434_F0E8_4D5D_A416_CBA8FC4FCAEF

#include <ccbase/format/format_argument.hpp>

namespace cc {

class argument_base
{
public:
	virtual void apply(uint8_t list_idx) const = 0;
};

template <class Char, class Traits, class T>
class argument_wrapper : argument_base
{
	using format_argument = basic_format_argument<Char, Traits>;
	using ostream         = std::basic_ostream<Char, Traits>;
	using ostringstream   = std::basic_ostringstream<Char, Traits>;

	const format_argument* m_list;
	ostream& m_dst;
	ostringstream& m_buf;
	const T& m_arg;
public:
	explicit argument_wrapper(
		const T& arg,
		ostream& dst,
		ostringstream& buf,
		const format_argument* list
	) noexcept : m_list{list}, m_dst{dst}, m_buf{buf}, m_arg{arg} {}

	void apply(uint8_t list_idx) const override 
	{
		cc::apply(m_list[list_idx], m_arg, m_dst, m_buf);
	}
};

template <class Char, class Traits, class T>
argument_wrapper<Char, Traits, T>
make_argument_wrapper(
	const T& arg,
	std::basic_ostream<Char, Traits>& dst,
	std::basic_ostringstream<Char, Traits>& buf,
	const basic_format_argument<Char, Traits>* list
)
{
	return argument_wrapper<Char, Traits, T>{arg, dst, buf, list};
}

}

#endif
