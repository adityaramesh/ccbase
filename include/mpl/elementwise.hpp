/*
** File Name:	elementwise.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZAC7333B1_6E60_4B74_932A_D0815AC19A63
#define ZAC7333B1_6E60_4B74_932A_D0815AC19A63

#include <mpl/apply.hpp>

namespace mpl {

template <
	template <class...> class Operation,
	class                     Head,
	class                     S1,
	class                     S2
>
struct elementwise_impl;

template <
	template <class...> class Operation,
	class                     Head,
	class                     T,
	class...                  Ts,
	class                     U,
	class...                  Us
>
struct elementwise_impl<
	Operation,
	Head,
	sequence<T, Ts...>,
	sequence<U, Us...>
>
{
	using t = apply<Operation, T, U>;
	using r = append<t, Head>;
	
	using type = typename elementwise_impl<
		Operation, r, sequence<Ts...>, sequence<Us...>
	>::type;
};

template <template <class...> class Operation, class Head>
struct elementwise_impl<
	Operation,
	Head,
	sequence<>,
	sequence<>
>
{
	using type = Head;
};

template <template <class...> class Operation, class S1, class S2>
using elementwise = typename elementwise_impl<
	Operation, sequence<>, S1, S2
>::type;

}

#endif
