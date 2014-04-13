/*
** File Name:	format.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z9DCE86DF_558B_497F_B6CC_4DCDFD6070FC
#define Z9DCE86DF_558B_497F_B6CC_4DCDFD6070FC

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <ccbase/platform.hpp>

namespace cc {

namespace detail {

/*
** We do not use the `isdigit` function from `<cctype>`, because the only
** characters that we treat as digits for argument indexing purposes are those
** from 0--9.
*/

template <class T>
static CC_ALWAYS_INLINE bool
is_digit(const T t)
noexcept
{
	return T{'0'} <= t && t <= T{'9'};
}

template <class T, class Traits = std::char_traits<T>>
static CC_ALWAYS_INLINE void
write_arg(const std::basic_ostream<T, Traits>&, const std::size_t)
{
	throw std::out_of_range{"Not enough arguments."};
}

template <class T, class Traits = std::char_traits<T>, class U, class... Us>
static CC_ALWAYS_INLINE void
write_arg(
	std::basic_ostream<T, Traits>& os,
	const std::size_t n,
	const U arg,
	const Us... args
)
{
	if (n > 0) {
		return write_arg(os, n - 1, args...);
	}
	os << arg;
}

}

template <class T, class Traits = std::char_traits<T>, class... Us>
void write(std::basic_ostream<T, Traits>& os, const T* s, const Us... args)
{
	using detail::is_digit;
	using detail::write_arg;

	// Used to keep track of the segment of the string to be printed before
	// printing the next format argument.
	auto f = s;
	auto l = s;

	// Used to keep track of the next format argument to be printed.
	auto i = 0u;

	// We disallow printing the null string.
	assert(l != nullptr && "Format string is null.");
	// We disallow printing the empty string.
	assert(*l != 0 && "Format string is empty.");

	do {
		if (*l == T{'$'}) {
			os.write(f, l - f);
			++l;
			f = l;
			write_arg(os, i, args...);
			++i;
		}
		else if (*l == T{'{'}) {
			if (*(l + 1) == T{'$'}) {
				assert(*(l + 2) == '}' && "Expected '}'.");
				os.write(f, l - f);
				os.write("$", 1);
				l += 3;
				f = l;
			}
			else if (*(l + 1) == T{'{'}) {
				++l;
				os.write(f, l - f);
				++l;
				f = l;
			}
			else {
				assert(false && "Invalid use of '{'.");
			}
		}
		else if (*l == T{'}'}) {
			assert(*(l + 1) == '}' && "Unexpected '}'.");
			++l;
			os.write(f, l - f);
			++l;
			f = l;
		}
		else {
			++l;
		}
	}
	while (*l != 0);
	os.write(f, l - f);
}

template <class T, class Traits = std::char_traits<T>, class... Us>
void writeln(std::basic_ostream<T, Traits>& os, const T* s, const Us... args)
{
	write(os, s, args...);
	os << std::endl;
}

template <class T, class... Us>
CC_ALWAYS_INLINE void
print(const T* s, const Us... args)
{
	write(std::cout, s, args...);
}

template <class T, class... Us>
CC_ALWAYS_INLINE void
println(const T* s, const Us... args)
{
	writeln(std::cout, s, args...);
}

template <class T, class... Us>
CC_ALWAYS_INLINE void
err(const T* s, const Us... args)
{
	write(std::cerr, s, args...);
}

template <class T, class... Us>
CC_ALWAYS_INLINE void
errln(const T* s, const Us... args)
{
	writeln(std::cerr, s, args...);
}

template <class T, class... Us>
CC_ALWAYS_INLINE void
finish(const T* s, const Us... args)
{
	println(s, args...);
	std::exit(EXIT_SUCCESS);
}

template <class T, class... Us>
CC_ALWAYS_INLINE void
fail(const T* s, const Us... args)
{
	errln(s, args...);
	std::exit(EXIT_FAILURE);
}

template <class T, class... Us>
CC_ALWAYS_INLINE auto
format(const T* s, const Us... args) ->
std::basic_string<T, std::char_traits<T>>
{
	std::basic_ostringstream<T, std::char_traits<T>> ss; 
	write(ss, s, args...);
	return ss.str();
}

template <class T, class... Us>
CC_ALWAYS_INLINE auto
formatln(const T* s, const Us... args) ->
std::basic_string<T, std::char_traits<T>>
{
	std::basic_ostringstream<T, std::char_traits<T>> ss; 
	writeln(ss, s, args...);
	return ss.str();
}

}

#endif
