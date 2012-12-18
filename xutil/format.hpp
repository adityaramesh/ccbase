/*
** File Name:	format.hpp
** Author:	Aditya Ramesh
** Date:	12/05/2012
** Contact:	_@adityaramesh.com
**
** set_scientific
** Modifies stream to use scientific notation, using provided precision.
**
** set_fixed
** Modifies stream to use fixed notation, using provided precision.
**
** write
** Writes formatted text to a stream.
**
** writeln
** Writes formatted text to a stream, ending with std::endl.
**
** print
** Writes foramtted text to stdout.
**
** println
** Writes formatted text to stdout, ending with std::endl.
*/

#ifndef Z759404CD_C2FF_45EE_A125_85ABCEF5CF82
#define Z759404CD_C2FF_45EE_A125_85ABCEF5CF82

#include <clocale>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace xu
{

static bool initialize()
{
	std::ios_base::sync_with_stdio(false);
	return true;
}

static bool success = initialize();

void set_scientific(std::ostream& os, const int n = 6)
{
	os << std::scientific << std::setprecision(n);
}

void set_fixed(std::ostream& os, const int n = 6)
{
	os << std::fixed << std::setprecision(n);
}

struct format_error : std::runtime_error
{
	format_error(const std::string& s) : std::runtime_error{s} {}
};

void write_arg(std::ostream& os, const unsigned n)
{
	throw xu::format_error{"Argument cardinality too high."};
}

template <class T, class... Ts>
void write_arg(std::ostream& os, const unsigned n, const T t, const Ts... ts)
{
	if (n) {
		return write_arg(os, n - 1, ts...);
	}
	os << t;
}

template <class... Ts>
void write(std::ostream& os, const char* s, const Ts... ts)
{
	auto f = s;
	auto l = s;
	while (*l) {
		// Case 1. We need to format an argument.
		if (*l == '{' && *(l + 1) != '{') {
			os.write(f, l - f);
			++l;
			unsigned i = 0;
			while (*l && *l != '}') {
				i = 10 * i + (*l++ - '0');
			}
			if (!*l) {
				throw xu::format_error{"Unmatched curly bracket."};
			}
			write_arg(os, i, ts...);
			++l;
			f = l;
		}
		// Case 2. We need to skip past a regular character, i.e. a
		// character that is not a curly bracket.
		else if (*l != '{' && *l != '}') {
			++l;
		}
		// Case 3. We have encountered a double curly bracket ('{{' or
		// '}}'), so we print everything from f to l, including the
		// first curly bracket. Then, we skip past the last curly
		// bracket.
		else {
			++l;
			os.write(f, l - f);
			++l;
			f = l;
		}
	}
	os.write(f, l - f);
}

template <class... Ts>
void writeln(std::ostream& os, const char* s, const Ts... ts)
{
	write(os, s, ts...);
	os << std::endl;
}

template <class... Ts>
void print(const char* s, const Ts... ts)
{
	write(std::cout, s, ts...);
}

template <class... Ts>
void println(const char* s, const Ts... ts)
{
	writeln(std::cout, s, ts...);
}

}

#endif
