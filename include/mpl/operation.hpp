/*
** File Name:	operation.hpp
** Author:	Aditya Ramesh
** Date:	07/11/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZB5495E89_5930_407E_BEF3_557DFDF6AB92
#define ZB5495E89_5930_407E_BEF3_557DFDF6AB92

#include <cstdint>
#include <mpl/integer.hpp>

namespace mpl {

template <class T>
struct identity_impl
{
	using type = T;
};

template <class T>
using identity = identity_impl<T>;

template <class A, class B>
struct add_impl;

template <std::uintmax_t A, std::uintmax_t B>
struct add_impl<integer<A>, integer<B>>
{
	using type = integer<A + B>;
};

template <class T, class U>
using add = add_impl<T, U>;

template <class A, class B>
struct subtract_impl;

template <std::uintmax_t A, std::uintmax_t B>
struct subtract_impl<integer<A>, integer<B>>
{
	using type = integer<A - B>;
};

template <class T, class U>
using subtract = subtract_impl<T, U>;

template <class A, class B>
struct multiply_impl;

template <std::uintmax_t A, std::uintmax_t B>
struct multiply_impl<integer<A>, integer<B>>
{
	using type = integer<A * B>;
};

template <class T, class U>
using multiply = multiply_impl<T, U>;

template <class T>
struct constant
{
	template <class U>
	struct rebind
	{
		using type = T;
	};
};

}

#endif
