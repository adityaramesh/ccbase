/*
** File Name: constant.hpp
** Author:    Aditya Ramesh
** Date:      01/17/2015
** Contact:   _@adityaramesh.com
*/

#ifndef Z9DA9D911_A246_4724_A9CA_5A29932E3C77
#define Z9DA9D911_A246_4724_A9CA_5A29932E3C77

#include <cstdint>
#include <utility>

namespace cc {
namespace mpl {

template <bool N>
using bool_ = std::integral_constant<bool, N>;

template <char N>
using char_ = std::integral_constant<char, N>;

template <short N>
using short_ = std::integral_constant<short, N>;

template <int N>
using int_ = std::integral_constant<int, N>;

template <long N>
using long_ = std::integral_constant<long, N>;

template <unsigned char N>
using uchar_ = std::integral_constant<unsigned char, N>;

template <unsigned short N>
using ushort_ = std::integral_constant<unsigned short, N>;

template <unsigned int N>
using uint_ = std::integral_constant<unsigned int, N>;

template <unsigned long N>
using ulong_ = std::integral_constant<unsigned long, N>;

template <size_t N>
using size_t = std::integral_constant<size_t, N>;

template <intmax_t N>
using intmax_t = std::integral_constant<intmax_t, N>;

template <uintmax_t N>
using uintmax_t = std::integral_constant<uintmax_t, N>;

template <class T, class Var>
using cast = std::integral_constant<T, Var::value>;

}}

#endif
