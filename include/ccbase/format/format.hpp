/*
** File Name:	format.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z9DCE86DF_558B_497F_B6CC_4DCDFD6070FC
#define Z9DCE86DF_558B_497F_B6CC_4DCDFD6070FC

#include <ccbase/platform/attributes.hpp>
#include <ccbase/format/formatter.hpp>

namespace cc {

template <class Char, class Traits = std::char_traits<Char>, class... Args>
basic_formatter<Char, Traits, sizeof...(Args)>
write(
	std::basic_ostream<Char, Traits>& os,
	const boost::basic_string_ref<Char, Traits>& fmt,
	const Args&&... args
)
{
	auto fmt = basic_formatter<Char, Traits, sizeof...(Args)>{fmt};
	apply(fmt, os, std::forward<Args>(args)...);
	return fmt;
}

template <class Char, class Traits = std::char_traits<Char>, class Arg>
CC_ALWAYS_INLINE void
write(std::basic_ostream<Char, Traits>& os, const Arg& arg)
{
	os << arg;
}

template <class Char, class Traits = std::char_traits<Char>, class... Args>
basic_formatter<Char, Traits, sizeof...(Args)>
writeln(std::basic_ostream<Char, Traits>& os, const Args&&... args)
{
	auto tmp = write(os, args...);
	os << std::endl;
	return tmp;
}

template <class... Args>
basic_formatter<Char, Traits, sizeof...(Args)>
print(const Args&&... args)
{
	return write(std::cout, std::forward<Args>(args)...);
}

template <class... Args>
basic_formatter<Char, Traits, sizeof...(Args)>
println(const Args&&... args)
{
	return writeln(std::cout, std::forward<Args>(args)...);
}

template <class... Args>
basic_formatter<Char, Traits, sizeof...(Args)>
err(const Args&&... args)
{
	return write(std::cerr, std::forward<Args>(args)...);
}

template <class... Ts>
basic_formatter<Char, Traits, sizeof...(Args)>
errln(const Args&&... args)
{
	return writeln(std::cerr, std::forward<Args>(args)...);
}

/*
** These functions require the format string argument, because we would not know
** the type of string to return otherwise.
*/

template <class Char, class Traits, class... Args>
auto format(
	const boost::basic_string_ref<Char, Traits>& fmt,
	const Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	write(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

template <class Char, class Traits, class... Args>
auto formatln(
	const boost::basic_string_ref<Char, Traits>& fmt,
	const Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	writeln(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

}

#endif
