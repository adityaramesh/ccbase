/*
** File Name:	format.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z9DCE86DF_558B_497F_B6CC_4DCDFD6070FC
#define Z9DCE86DF_558B_497F_B6CC_4DCDFD6070FC

#include <iostream>
#include <ccbase/platform/attributes.hpp>
#include <ccbase/format/formatter.hpp>

namespace cc {

#ifdef __GLIBCXX__

/*
** Move constructors for streams *still* have not been added to libstdc++, we
** cannot move the `basic_formatter` class.
*/

template <class Char, class Traits = std::char_traits<Char>, class... Args>
void write(
	std::basic_ostream<Char, Traits>& os,
	const boost::basic_string_ref<Char, Traits>& fmt,
	Args&&... args
)
{
	basic_formatter<Char, Traits> f{fmt};
	f(os, std::forward<Args>(args)...);
}

template <class Char, class Traits = std::char_traits<Char>>
void write(
	std::basic_ostream<Char, Traits>& os,
	boost::basic_string_ref<Char, Traits>& fmt
) noexcept
{
	detail::print_format_substring(fmt, os);
}

template <class Char, class Traits = std::char_traits<Char>>
void write(
	std::basic_ostream<Char, Traits>& os,
	const std::basic_string<Char, Traits> fmt
) noexcept
{
	detail::print_format_substring(boost::basic_string_ref<Char, Traits>{fmt}, os);
}

template <class Char, class Traits = std::char_traits<Char>, class Arg>
void write(std::basic_ostream<Char, Traits>& os, Arg&& arg)
noexcept
{
	os << arg;
}

template <class Char, class Traits = std::char_traits<Char>, class... Args>
void writeln(
	std::basic_ostream<Char, Traits>& os,
	const boost::basic_string_ref<Char, Traits>& fmt,
	Args&&... args
)
{
	write(os, fmt, std::forward<Args>(args)...);
	os << std::endl;
}

template <class Char, class Traits = std::char_traits<Char>>
void writeln(
	std::basic_ostream<Char, Traits>& os,
	boost::basic_string_ref<Char, Traits>& fmt
) noexcept
{
	detail::print_format_substring(fmt, os);
	os << "\n";
}

template <class Char, class Traits = std::char_traits<Char>>
void writeln(
	std::basic_ostream<Char, Traits>& os,
	const std::basic_string<Char, Traits> fmt
) noexcept
{
	detail::print_format_substring(boost::basic_string_ref<Char, Traits>{fmt}, os);
	os << "\n";
}

template <class Char, class Traits = std::char_traits<Char>, class Arg>
void writeln(std::basic_ostream<Char, Traits>& os, Arg&& arg)
noexcept
{
	os << arg << "\n";
}

template <class... Args>
void print(const boost::string_ref& fmt, Args&&... args)
{
	write(std::cout, fmt, std::forward<Args>(args)...);
}

void print(const boost::string_ref& fmt) noexcept
{
	detail::print_format_substring(fmt, std::cout);
}

void print(const std::string fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cout);
}

void print(const char* fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cout);
}

template <class Arg>
void print(Arg&& arg) noexcept
{
	write(std::cout, std::forward<Arg>(arg));
}

template <class... Args>
void println(const boost::string_ref& fmt, Args&&... args)
{
	writeln(std::cout, fmt, std::forward<Args>(args)...);
}

void println(const boost::string_ref& fmt) noexcept
{
	detail::print_format_substring(fmt, std::cout);
	std::cout << "\n";
}

void println(const std::string fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cout);
	std::cout << "\n";
}

void println(const char* fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cout);
	std::cout << "\n";
}

template <class Arg>
void println(Arg&& arg) noexcept
{
	writeln(std::cout, std::forward<Arg>(arg));
}

template <class... Args>
void err(const boost::string_ref& fmt, Args&&... args)
{
	write(std::cerr, fmt, std::forward<Args>(args)...);
}

void err(const boost::string_ref& fmt) noexcept
{
	detail::print_format_substring(fmt, std::cerr);
}

void err(const std::string fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cerr);
}

void err(const char* fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cerr);
}

template <class Arg>
void err(Arg&& arg) noexcept
{
	write(std::cerr, std::forward<Arg>(arg));
}

template <class... Args>
void errln(const boost::string_ref& fmt, Args&&... args)
{
	writeln(std::cerr, fmt, std::forward<Args>(args)...);
}

void errln(const boost::string_ref& fmt) noexcept
{
	detail::print_format_substring(fmt, std::cerr);
	std::cerr << "\n";
}

void errln(const std::string fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cerr);
	std::cerr << "\n";
}

void errln(const char* fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cerr);
	std::cerr << "\n";
}

template <class Arg>
void errln(Arg&& arg) noexcept
{
	writeln(std::cerr, std::forward<Arg>(arg));
}

/*
** These functions require the format string argument, because we would not know
** the type of string to return otherwise.
*/

template <class Char, class Traits, class... Args>
auto format(
	const boost::basic_string_ref<Char, Traits>& fmt,
	Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	write(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

template <class Char, class Traits, class... Args>
auto formatln(
	const boost::basic_string_ref<Char, Traits>& fmt,
	Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	writeln(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

/*
** These are the overloads for `std::basic_string`.
*/

template <class Char, class Traits = std::char_traits<Char>, class... Args>
void write(
	std::basic_ostream<Char, Traits>& os,
	const std::basic_string<Char, Traits>& fmt,
	Args&&... args
)
{
	basic_formatter<Char, Traits> f{fmt};
	f(os, std::forward<Args>(args)...);
}

template <class Char, class Traits = std::char_traits<Char>, class... Args>
void writeln(
	std::basic_ostream<Char, Traits>& os,
	const std::basic_string<Char, Traits>& fmt,
	Args&&... args
)
{
	write(os, fmt, std::forward<Args>(args)...);
	os << std::endl;
}

/*
** These functions require the format string argument, because we would not know
** the type of string to return otherwise.
*/

template <class Char, class Traits, class... Args>
auto format(
	const std::basic_string<Char, Traits>& fmt,
	Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	write(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

template <class Char, class Traits, class... Args>
auto formatln(
	const std::basic_string<Char, Traits>& fmt,
	Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	writeln(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

/*
** These are the overloads for character literals.
*/

template <class Char, class Traits, class... Args>
void write(
	std::basic_ostream<Char, Traits>& os,
	const Char* fmt,
	Args&&... args
)
{
	basic_formatter<Char, Traits> f{fmt};
	f(os, std::forward<Args>(args)...);
}

template <class Char, class Traits, class... Args>
void writeln(
	std::basic_ostream<Char, Traits>& os,
	const Char* fmt,
	Args&&... args
)
{
	write(os, fmt, std::forward<Args>(args)...);
	os << std::endl;
}

/*
** These functions require the format string argument, because we would not know
** the type of string to return otherwise.
*/

template <class Char, class Traits = std::char_traits<Char>, class... Args>
auto format(const Char* fmt, Args&&... args) ->
std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	write(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

template <class Char, class Traits = std::char_traits<Char>, class... Args>
auto formatln(const Char* fmt, Args&&... args) ->
std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	writeln(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

#else

template <class Char, class Traits = std::char_traits<Char>, class... Args>
basic_formatter<Char, Traits>
write(
	std::basic_ostream<Char, Traits>& os,
	const boost::basic_string_ref<Char, Traits>& fmt,
	Args&&... args
)
{
	auto f = basic_formatter<Char, Traits>{fmt};
	f(os, std::forward<Args>(args)...);
	return f;
}

template <class Char, class Traits = std::char_traits<Char>>
void write(
	std::basic_ostream<Char, Traits>& os,
	boost::basic_string_ref<Char, Traits>& fmt
) noexcept
{
	detail::print_format_substring(fmt, os);
}

template <class Char, class Traits = std::char_traits<Char>>
void write(
	std::basic_ostream<Char, Traits>& os,
	const std::basic_string<Char, Traits> fmt
) noexcept
{
	detail::print_format_substring(boost::basic_string_ref<Char, Traits>{fmt}, os);
}

template <class Char, class Traits = std::char_traits<Char>, class Arg>
void write(std::basic_ostream<Char, Traits>& os, Arg&& arg)
noexcept
{
	os << arg;
}

template <class Char, class Traits = std::char_traits<Char>, class... Args>
basic_formatter<Char, Traits>
writeln(
	std::basic_ostream<Char, Traits>& os,
	const boost::basic_string_ref<Char, Traits>& fmt,
	Args&&... args
)
{
	auto tmp = write(os, fmt, std::forward<Args>(args)...);
	os << std::endl;
	return tmp;
}

template <class Char, class Traits = std::char_traits<Char>>
void writeln(
	std::basic_ostream<Char, Traits>& os,
	boost::basic_string_ref<Char, Traits>& fmt
) noexcept
{
	detail::print_format_substring(fmt, os);
	os << "\n";
}

template <class Char, class Traits = std::char_traits<Char>>
void writeln(
	std::basic_ostream<Char, Traits>& os,
	const std::basic_string<Char, Traits> fmt
) noexcept
{
	detail::print_format_substring(boost::basic_string_ref<Char, Traits>{fmt}, os);
	os << "\n";
}

template <class Char, class Traits = std::char_traits<Char>, class Arg>
void writeln(std::basic_ostream<Char, Traits>& os, Arg&& arg)
noexcept
{
	os << arg << "\n";
}

template <class... Args>
basic_formatter<char, std::char_traits<char>>
print(const boost::string_ref& fmt, Args&&... args)
{
	return write(std::cout, fmt, std::forward<Args>(args)...);
}

void print(const boost::string_ref& fmt) noexcept
{
	detail::print_format_substring(fmt, std::cout);
}

void print(const std::string fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cout);
}

void print(const char* fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cout);
}

template <class Arg>
void print(Arg&& arg) noexcept
{
	write(std::cout, std::forward<Arg>(arg));
}

template <class... Args>
basic_formatter<char, std::char_traits<char>>
println(const boost::string_ref& fmt, Args&&... args)
{
	return writeln(std::cout, fmt, std::forward<Args>(args)...);
}

void println(const boost::string_ref& fmt) noexcept
{
	detail::print_format_substring(fmt, std::cout);
	std::cout << "\n";
}

void println(const std::string fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cout);
	std::cout << "\n";
}

void println(const char* fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cout);
	std::cout << "\n";
}

template <class Arg>
void println(Arg&& arg) noexcept
{
	writeln(std::cout, std::forward<Arg>(arg));
}

template <class... Args>
basic_formatter<char, std::char_traits<char>>
err(const boost::string_ref& fmt, Args&&... args)
{
	return write(std::cerr, fmt, std::forward<Args>(args)...);
}

void err(const boost::string_ref& fmt) noexcept
{
	detail::print_format_substring(fmt, std::cerr);
}

void err(const std::string fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cerr);
}

void err(const char* fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cerr);
}

template <class Arg>
void err(Arg&& arg) noexcept
{
	write(std::cerr, std::forward<Arg>(arg));
}

template <class... Args>
basic_formatter<char, std::char_traits<char>>
errln(const boost::string_ref& fmt, Args&&... args)
{
	return writeln(std::cerr, fmt, std::forward<Args>(args)...);
}

void errln(const boost::string_ref& fmt) noexcept
{
	detail::print_format_substring(fmt, std::cerr);
	std::cerr << "\n";
}

void errln(const std::string fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cerr);
	std::cerr << "\n";
}

void errln(const char* fmt) noexcept
{
	detail::print_format_substring(boost::string_ref{fmt}, std::cerr);
	std::cerr << "\n";
}

template <class Arg>
void errln(Arg&& arg) noexcept
{
	writeln(std::cerr, std::forward<Arg>(arg));
}

/*
** These functions require the format string argument, because we would not know
** the type of string to return otherwise.
*/

template <class Char, class Traits, class... Args>
auto format(
	const boost::basic_string_ref<Char, Traits>& fmt,
	Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	write(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

template <class Char, class Traits, class... Args>
auto formatln(
	const boost::basic_string_ref<Char, Traits>& fmt,
	Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	writeln(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

/*
** These are the overloads for `std::basic_string`.
*/

template <class Char, class Traits = std::char_traits<Char>, class... Args>
basic_formatter<Char, Traits>
write(
	std::basic_ostream<Char, Traits>& os,
	const std::basic_string<Char, Traits>& fmt,
	Args&&... args
)
{
	auto f = basic_formatter<Char, Traits>{fmt};
	f(os, std::forward<Args>(args)...);
	return f;
}

template <class Char, class Traits = std::char_traits<Char>, class... Args>
basic_formatter<Char, Traits>
writeln(
	std::basic_ostream<Char, Traits>& os,
	const std::basic_string<Char, Traits>& fmt,
	Args&&... args
)
{
	auto tmp = write(os, fmt, std::forward<Args>(args)...);
	os << std::endl;
	return tmp;
}

/*
** These functions require the format string argument, because we would not know
** the type of string to return otherwise.
*/

template <class Char, class Traits, class... Args>
auto format(
	const std::basic_string<Char, Traits>& fmt,
	Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	write(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

template <class Char, class Traits, class... Args>
auto formatln(
	const std::basic_string<Char, Traits>& fmt,
	Args&&... args
) -> std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	writeln(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

/*
** These are the overloads for character literals.
*/

template <class Char, class Traits, class... Args>
basic_formatter<Char, Traits>
write(
	std::basic_ostream<Char, Traits>& os,
	const Char* fmt,
	Args&&... args
)
{
	auto f = basic_formatter<Char, Traits>{fmt};
	f(os, std::forward<Args>(args)...);
	return f;
}

template <class Char, class Traits, class... Args>
basic_formatter<Char, Traits>
writeln(
	std::basic_ostream<Char, Traits>& os,
	const Char* fmt,
	Args&&... args
)
{
	auto tmp = write(os, fmt, std::forward<Args>(args)...);
	os << std::endl;
	return tmp;
}

/*
** These functions require the format string argument, because we would not know
** the type of string to return otherwise.
*/

template <class Char, class Traits = std::char_traits<Char>, class... Args>
auto format(const Char* fmt, Args&&... args) ->
std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	write(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

template <class Char, class Traits = std::char_traits<Char>, class... Args>
auto formatln(const Char* fmt, Args&&... args) ->
std::basic_string<Char, Traits>
{
	std::basic_ostringstream<Char, Traits> ss{}; 
	writeln(ss, fmt, std::forward<Args>(args)...);
	return ss.str();
}

#endif

}

#endif
