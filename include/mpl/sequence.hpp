/*
** File Name:	sequence.hpp
** Author:	Aditya Ramesh
** Date:	07/13/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z7B8D69C3_CCF7_48FA_93A9_80063B6C585B
#define Z7B8D69C3_CCF7_48FA_93A9_80063B6C585B

#include <type_traits>
#include <mpl/integer.hpp>

namespace mpl {

/*
** A `sequence` should never be instantiated, so we do not provide a class
** definition.
*/

template <class... Ts>
struct sequence;

/*
** `cat`
*/

template <class S1, class S2>
struct cat_impl;

template <class... Ts, class... Us>
struct cat_impl<sequence<Ts...>, sequence<Us...>>
{
	using type = sequence<Ts..., Us...>;
};

template <class S1, class S2>
using cat = typename cat_impl<S1, S2>::type;

/*
** `prepend`
*/

template <class T, class S>
using prepend = cat<sequence<T>, S>;

/*
** `append`
*/

template <class T, class S>
using append = cat<S, sequence<T>>;

/*
** `size`
*/

template <class S>
struct size_impl;

template <class... Ts>
struct size_impl<sequence<Ts...>>
{
	using type = integer<sizeof...(Ts)>;
};

template <class S>
using size = typename size_impl<S>::type;

/*
** `at`
*/

template <std::uintmax_t Current, std::uintmax_t Index, class S>
struct at_impl;

template <
	std::uintmax_t Current,
	std::uintmax_t Index,
	class          T,
	class...       Ts
>
struct at_impl<Current, Index, sequence<T, Ts...>>
{
	using type =
	typename at_impl<Current + 1, Index, sequence<Ts...>>::type;
};

template <std::uintmax_t Index, class T, class... Ts>
struct at_impl<Index, Index, sequence<T, Ts...>>
{
	using type = T;
};

/*
** We not do provide a definition for this class, because we want to raise an
** error if the compiler attempts to instantiate it. This happens precisely when
** an index is out of bounds.
*/

template <std::uintmax_t Current, std::uintmax_t Index>
struct at_impl<Current, Index, sequence<>>;

template <std::uintmax_t Index, class S>
using at = typename at_impl<0, Index, S>::type;

/*
** `set`
*/

template <
	std::uintmax_t Current,
	std::uintmax_t Index,
	class          Value,
	class          Head,
	class          Tail
>
struct set_impl;

template <
	std::uintmax_t Current,
	std::uintmax_t Index,
	class          Value,
	class...       Ts,
	class          U,
	class...       Us
>
struct set_impl<
	Current,
	Index,
	Value,
	sequence<Ts...>,
	sequence<U, Us...>
>
{
	using type = typename set_impl<
		Current + 1,
		Index,
		Value,
		sequence<Ts..., U>,
		sequence<Us...>
	>::type;
};

template <
	std::uintmax_t Index,
	class          Value,
	class...       Ts,
	class          U,
	class...       Us
>
struct set_impl<
	Index,
	Index,
	Value,
	sequence<Ts...>,
	sequence<U, Us...>
>
{
	using type = sequence<Ts..., Value, Us...>;
};

template <
	std::uintmax_t Index,
	class          Value,
	class          S
>
using set = typename set_impl<
	0,
	Index,
	Value,
	sequence<>,
	S
>::type;

/*
** `insert_at`
*/

template <
	std::uintmax_t Current,
	std::uintmax_t Index,
	class          T,
	class          Head,
	class          Tail
>
struct insert_at_impl;

template <
	std::uintmax_t Current,
	std::uintmax_t Index,
	class          T,
	class          Head,
	class          U,
	class...       Us
>
struct insert_at_impl<
	Current,
	Index,
	T,
	Head,
	sequence<U, Us...>
>
{
	using head = append<U, Head>;
	using type = typename insert_at_impl<
		Current + 1,
		Index,
		T,
		head,
		sequence<Us...>
	>::type;
};

template <
	std::uintmax_t Index,
	class          T,
	class          Head,
	class          U,
	class...       Us
>
struct insert_at_impl<
	Index,
	Index,
	T,
	Head,
	sequence<U, Us...>
>
{
	using tail = sequence<U, Us...>;
	using t = prepend<T, tail>;
	using type = cat<Head, t>;
};

template <
	std::uintmax_t Index,
	class          T,
	class          Head
>
struct insert_at_impl<
	Index,
	Index,
	T,
	Head,
	sequence<>
>
{
	using type = append<T, Head>;
};

template <std::uintmax_t Index, class T, class S>
using insert_at = typename insert_at_impl<
	0, Index, T, sequence<>, S
>::type;

/*
** `erase_at`
*/

template <
	std::uintmax_t Current,
	std::uintmax_t Index,
	class          Head,
	class          Tail
>
struct erase_at_impl;

template <
	std::uintmax_t Current,
	std::uintmax_t Index,
	class          Head,
	class          T,
	class...       Ts
>
struct erase_at_impl<
	Current,
	Index,
	Head,
	sequence<T, Ts...>
>
{
	using type = typename erase_at_impl<
		Current + 1,
		Index,
		append<T, Head>,
		sequence<Ts...>
	>::type;
};

template <
	std::uintmax_t Index,
	class          Head,
	class          T,
	class...       Ts
>
struct erase_at_impl<
	Index,
	Index,
	Head,
	sequence<T, Ts...>
>
{
	using type = cat<Head, sequence<Ts...>>;
};

template <std::uintmax_t Index, class Head>
struct erase_at_impl<
	Index,
	Index,
	Head,
	sequence<>
>;

template <std::uintmax_t Index, class S>
using erase_at = typename erase_at_impl<
	0, Index, sequence<>, S
>::type;

template <class S>
using erase_first = erase_at<0, S>;

template <class S>
using erase_last = erase_at<size<S>::value - 1, S>;

/*
** `contains`
*/

template <class T, class S>
struct contains;

template <class T, class U, class... Us>
struct contains<T, sequence<U, Us...>>
{
	static constexpr bool value =
	contains<T, sequence<Us...>>::value;
};

template <class T, class... Us>
struct contains<T, sequence<T, Us...>> : std::true_type {};

template <class T>
struct contains<T, sequence<>> : std::false_type {};

/*
** `reverse`
*/

template <class Head, class Tail>
struct reverse_impl;

template <class... Ts, class U, class... Us>
struct reverse_impl<sequence<Ts...>, sequence<U, Us...>>
{
	using type =
	typename reverse_impl<
		sequence<U, Ts...>,
		sequence<Us...>
	>::type;
};

template <class Head>
struct reverse_impl<Head, sequence<>>
{
	using type = Head;
};

template <class S>
using reverse = typename reverse_impl<sequence<>, S>::type;

}

#endif
