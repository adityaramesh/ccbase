/*
** File Name:	type_traits.hpp
** Author:	Aditya Ramesh
** Date:	06/02/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z407E6497_9BD9_49B3_946C_BE3B546C5D40
#define Z407E6497_9BD9_49B3_946C_BE3B546C5D40

#include <type_traits>
#include <utility>

namespace cc
{

template <class... Ts>
struct common_type_impl;

template <class T, class... Ts>
struct common_type_impl<T, Ts...>
{
	using type = decltype(
		std::declval<T>() +
		std::declval<typename common_type_impl<Ts...>::type>()
	);
};

template <class T>
struct common_type_impl<T>
{
	using type = T;
};

template <class... Ts>
using common_type = typename common_type_impl<Ts...>::type;

}

#endif
