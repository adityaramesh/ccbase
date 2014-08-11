/*
** File Name:	swizzle.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z013001A5_50A0_4A0A_AAF0_261F72496363
#define Z013001A5_50A0_4A0A_AAF0_261F72496363

#include <mpl/sequence.hpp>

namespace mpl {

template <class Indices, class Head, class S>
struct swizzle_impl;

template <
	class    T,
	class... Ts,
	class    Head,
	class    S
>
struct swizzle_impl<
	sequence<T, Ts...>,
	Head,
	S
>
{
	using t = at<T::value, S>;
	using head = append<t, Head>;

	using type = typename swizzle_impl<
		sequence<Ts...>, head, S
	>::type;
};

template <class Head, class S>
struct swizzle_impl<
	sequence<>,
	Head,
	S
>
{
	using type = Head;
};

template <class Indices, class S>
using swizzle = typename swizzle_impl<
	Indices,
	sequence<>,
	S
>::type;

}

#endif
