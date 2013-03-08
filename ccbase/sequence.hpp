/*
** File Name:	sequence.hpp
** Author:	Aditya Ramesh
** Date:	03/07/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZEFD4B1E3_68E5_495A_90F5_4C01BBBB7D6D
#define ZEFD4B1E3_68E5_495A_90F5_4C01BBBB7D6D

namespace cc
{

template <class... Ts>
struct sequence {};

template <class A, class B>
struct sequence_cat;

template <class... Ts, class... Us>
struct sequence_cat<sequence<Ts...>, sequence<Us...>>
{
	using type = sequence<Ts..., Us...>;
};

template <class S>
struct sequence_size;

template <class... Ts>
struct sequence_size<sequence<Ts...>>
{
	static constexpr std::size_t value = sizeof...(Ts);
};

template <std::size_t Current, std::size_t Index, class Sequence>
struct sequence_get_impl;

template <std::size_t Current, std::size_t Index, class T, class... Ts>
struct sequence_get_impl<Current, Index, sequence<T, Ts...>>
{
	using type = typename
	sequence_get_impl<Current + 1, Index, sequence<Ts...>>::type;
};

template <std::size_t Index, class T, class... Ts>
struct sequence_get_impl<Index, Index, sequence<T, Ts...>>
{
	using type = T;
};

template <class Head, class Tail>
struct sequence_reverse_impl;

template <class... Ts, class U, class... Us>
struct sequence_reverse_impl<sequence<Ts...>, sequence<U, Us...>>
{
	using type =
	typename sequence_reverse_impl<
		sequence<U, Ts...>,
		sequence<Us...>
	>::type;
};

template <class Head>
struct sequence_reverse_impl<Head, sequence<>>
{
	using type = Head;
};

template <class Sequence>
struct sequence_reverse
{
	using type =
	typename sequence_reverse_impl<
		sequence<>, Sequence
	>::type;
};

/*
** If the compiler attempts to instantiate this type, then there is an index out
** of bounds error. So we do not provide a definition.
*/

template <std::size_t Current, std::size_t Index>
struct sequence_get_impl<Current, Index, sequence<>>;

template <std::size_t Index, class Sequence>
struct sequence_get
{
	using type = typename
	sequence_get_impl<0, Index, Sequence>::type;
};

}

#endif
