/*
** File Name:	format.hpp
** Author:	Aditya Ramesh
** Date:	12/05/2012
** Contact:	_@adityaramesh.com
*/

#ifndef Z759404CD_C2FF_45EE_A125_85ABCEF5CF82
#define Z759404CD_C2FF_45EE_A125_85ABCEF5CF82

#include <stdexcept>
#include <string>
#include <ccbase/unsync.hpp>

namespace cc
{

struct format_error : std::runtime_error
{
	format_error(const std::string& s) : std::runtime_error{s} {}
};

namespace internal
{

void write_arg(std::ostream& os, const unsigned n)
{
	throw format_error{"Argument cardinality too high."};
}

template <class T, class... Ts>
void write_arg(std::ostream& os, const unsigned n, const T t, const Ts... ts)
{
	if (n) {
		return write_arg(os, n - 1, ts...);
	}
	os << t;
}

}

/*
** Writes formatted text to a stream.
*/
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
				throw format_error{"Unmatched curly bracket."};
			}
			internal::write_arg(os, i, ts...);
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

/*
** Writes formatted text to a stream, ending with `std::endl`.
*/
template <class... Ts>
void writeln(std::ostream& os, const char* s, const Ts... ts)
{
	write(os, s, ts...);
	os << std::endl;
}

/*
** Writes formatted text to `stdout`.
*/
template <class... Ts>
void print(const char* s, const Ts... ts)
{
	write(std::cout, s, ts...);
}

/*
** Writes formatted text to `stdout`, ending with `std::endl`.
*/
template <class... Ts>
void println(const char* s, const Ts... ts)
{
	writeln(std::cout, s, ts...);
}

/*
** Returns a formatted std::string.
*/
template <class... Ts>
std::string format(const char* s, const Ts... ts)
{
	std::ostringstream ss;
	write(ss, s, ts...);
	return ss.str();
}

/*
** Returns a formatted std::string, appending a newline at the end.
*/
template <class... Ts>
std::string formatln(const char* s, const Ts... ts)
{
	std::ostringstream ss;
	writeln(ss, s, ts...);
	return ss.str();
}

}

#endif
