/*
** File Name:	variadic.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z9DCE86DF_558B_497F_B6CC_4DCDFD6070FC
#define Z9DCE86DF_558B_497F_B6CC_4DCDFD6070FC

#include <cassert>
#include <cstring>
#include <ios>
#include <sstream>
#include <string>

// TODO
//#include <ccbase/platform/attribute.hpp>
#define CC_ALWAYS_INLINE __attribute__((always_inline)) inline

namespace cc
{

namespace internal
{

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
write_arg(std::basic_ostream<T, Traits>& os, const std::size_t n)
noexcept 
{
	os.setstate(std::ios::failbit);
}

template <class T, class Traits = std::char_traits<T>, class U, class... Us>
static CC_ALWAYS_INLINE void
write_arg(
	std::basic_ostream<T, Traits>& os,
	const std::size_t n,
	const U arg,
	const Us... args
) noexcept 
{
	if (n > 0) {
		return write_arg(os, n - 1, args...);
	}
	os << arg;
}

}

template <class T, class Traits = std::char_traits<T>, class... Us>
void write(std::basic_ostream<T, Traits>& os, const T* s, const Us... args)
noexcept
{
	using internal::is_digit;
	using internal::write_arg;

	auto f = s;
	auto l = s;

	// We disallow printing the null string.
	assert(l != nullptr && "Format string is null.");
	// We disallow printing the empty string.
	assert(*l != 0 && "Format string is empty.");

	do {
		if (*l == T{'$'}) {
			if (*(l + 1) != T{'$'}) {
				os.write(f, l - f);
				++l;
				assert(is_digit(*l) && "Expected digit after $.");

				std::size_t i = 0;
				do {
					i = 10 * i + (*l++ - T{'0'});
				}
				while (is_digit(*l));

				write_arg(os, i, args...);
				f = l;
			}
			else {
				++l;
				assert(*l == T{'$'} && "Unexpected token after $.");
				os.write(f, l - f);
				++l;
				f = l;
			}
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
noexcept
{
	write(os, s, args...);
	os << std::endl;
}

template <class T, class... Us>
CC_ALWAYS_INLINE void
print(const T* s, const Us... args)
noexcept
{
	write(std::cout, s, args...);
}

template <class T, class... Us>
CC_ALWAYS_INLINE void
println(const T* s, const Us... args)
noexcept
{
	writeln(std::cout, s, args...);
}

template <class T, class... Us>
CC_ALWAYS_INLINE auto
format(const T* s, const Us... args) noexcept ->
std::basic_string<T, std::char_traits<T>>
{
	std::basic_ostringstream<T, std::char_traits<T>> ss; 
	write(ss, s, args...);
	return ss.str();
}

template <class T, class... Us>
CC_ALWAYS_INLINE auto
formatln(const T* s, const Us... args) noexcept ->
std::basic_string<T, std::char_traits<T>>
{
	std::basic_ostringstream<T, std::char_traits<T>> ss; 
	writeln(ss, s, args...);
	return ss.str();
}

}

#endif
