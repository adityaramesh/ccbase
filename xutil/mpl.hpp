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

template <std::size_t Count, std::size_t Index, class... Ts>
struct switch_impl;

template <std::size_t Count, std::size_t Index, class T, class... Ts>
struct switch_impl<Count, Index, T, Ts...>
{
	using type = typename switch_impl<Count + 1, Index, Ts...>::type;
};

template <std::size_t Count, class T, class... Ts>
struct switch_impl<Count, Count, T, Ts...>
{
	using type = T;
};

template <std::size_t Index, class... Ts>
struct switch_
{
	using type = typename switch_impl<0, sizeof...(Ts), Ts...>::type;
};

}

#endif
