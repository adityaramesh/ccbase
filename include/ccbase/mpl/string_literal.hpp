/*
** File Name: string_literal.hpp
** Author:    Aditya Ramesh
** Date:      08/12/2015
** Contact:   _@adityaramesh.com
*/

#ifndef Z29603881_DE00_4185_A430_6E5FD8A51419
#define Z29603881_DE00_4185_A430_6E5FD8A51419

#if defined(__clang__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wgnu-string-literal-operator-template"
#endif

namespace cc {
namespace mpl {

template <class Char, Char... Ts>
CC_ALWAYS_INLINE constexpr
auto operator"" _mpl_string() noexcept
{ return list<char_<Ts>...>{}; }

}}

using cc::mpl::operator"" _mpl_string;

#define mpl_string(x) decltype(x ## _mpl_string)

#if defined(__clang__)
	#pragma GCC diagnostic pop
#endif

#endif
