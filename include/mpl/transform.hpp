/*
** File Name:	transform.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z77C7CF55_363F_41D2_9EFE_A9146C646C1B
#define Z77C7CF55_363F_41D2_9EFE_A9146C646C1B

#include <mpl/apply.hpp>

namespace mpl {

template <
	template <class...> class Function,
	class                     Head,
	class                     Tail
>
struct transform_impl;

template <
	template <class...> class Function,
	class                     Head,
	class                     T,
	class...                  Ts
>
struct transform_impl<
	Function,
	Head,
	sequence<T, Ts...>
>
{
	using t = apply<Function, T>;
	using head = append<t, Head>;
	
	using type = typename transform_impl<
		Function,
		head,
		sequence<Ts...>
	>::type;
};

template <
	template <class...> class Function,
	class                     Head
>
struct transform_impl<
	Function,
	Head,
	sequence<>
>
{
	using type = Head;
};

template <template <class...> class Function, class S>
using transform = typename transform_impl<Function, sequence<>, S>::type;

}

#endif
