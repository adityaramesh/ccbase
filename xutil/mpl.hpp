/*
** File Name:	mpl.hpp
** Author:	Aditya Ramesh
** Date:	12/26/2012
** Contact:	_@adityaramesh.com
*/

#ifndef Z429B182F_01EB_473D_8B6A_034AB6CB0CAF
#define Z429B182F_01EB_473D_8B6A_034AB6CB0CAF

namespace xu
{

template <std::size_t Index, std::size_t MaxIndex, class... Ts>
struct switch_impl;

template <std::size_t Index, std::size_t MaxIndex, class T, class... Ts>
struct switch_impl<Index, MaxIndex, T, Ts...>
{
	using type = typename switch_impl<Index + 1, MaxIndex, Ts...>::type;
};

template <std::size_t MaxIndex, class T, class... Ts>
struct switch_impl<MaxIndex, MaxIndex, T, Ts...>
{
	using type = T;
};

template <std::size_t Index, class... Ts>
struct switch_
{
	using type = typename switch_impl<0, sizeof...(Ts) - 1, Ts...>::type;
};

}

#endif
