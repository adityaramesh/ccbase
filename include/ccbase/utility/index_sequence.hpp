/*
** File Name: index_sequence.hpp
** Author:    Aditya Ramesh
** Date:      01/03/2015
** Contact:   _@adityaramesh.com
*/

#ifndef ZF8995D56_732C_4E70_83EE_78FE6E016B50
#define ZF8995D56_732C_4E70_83EE_78FE6E016B50

#include <utility>

namespace cc {

/*
** The `at` metafunction.
*/

template <size_t Current, size_t Index, class Sequence>
struct at_impl;

template <size_t Current, size_t Index, size_t Head, size_t... Tail>
struct at_impl<Current, Index, std::integer_sequence<size_t, Head, Tail...>>
{
	static constexpr auto value =
	at_impl<Current + 1, Index, std::index_sequence<Tail...>>::value;
};

template <size_t Index, size_t Head, size_t... Tail>
struct at_impl<Index, Index, std::integer_sequence<size_t, Head, Tail...>>
{
	static constexpr auto value = Head;
};

template <size_t Index, class Sequence>
static constexpr auto at = at_impl<0, Index, Sequence>::value;

/*
** The `find` metafunction.
*/

template <
	size_t Index,
	size_t Value,
	class Sequence
>
struct find_impl;

template <
	size_t Index,
	size_t Value,
	size_t Head,
	size_t... Tail
>
struct find_impl<
	Index, Value,
	std::integer_sequence<size_t, Head, Tail...>
>
{
	static constexpr auto value =
	find_impl<Index + 1, Value, std::integer_sequence<size_t, Tail...>>::value;
};

template <
	size_t Index,
	size_t Value,
	size_t... Tail
>
struct find_impl<
	Index, Value, std::integer_sequence<size_t, Value, Tail...>
>
{
	static constexpr auto value = Index;
};

template <size_t Value, class Sequence>
static constexpr auto find = find_impl<0, Value, Sequence>::value;

/*
** The `cat` metafunction.
*/

template <class Seq1, class Seq2>
struct cat_impl;

template <size_t... Ts, size_t... Us>
struct cat_impl<std::index_sequence<Ts...>, std::index_sequence<Us...>>
{
	using type = std::index_sequence<Ts..., Us...>;
};

template <class Seq1, class Seq2>
using cat = typename cat_impl<Seq1, Seq2>::type;

/*
** The `constant_sequence` metafunction.
*/

template <size_t Index, size_t Max, size_t Value, size_t... Ts>
struct constant_sequence_impl
{
	using type = typename constant_sequence_impl<
		Index + 1, Max, Value, Value, Ts...
	>::type;
};

template <size_t Max, size_t Value, size_t... Ts>
struct constant_sequence_impl<Max, Max, Value, Ts...>
{
	using type = std::integer_sequence<size_t, Ts...>;
};

template <size_t Length, size_t Value>
using constant_sequence =
typename constant_sequence_impl<0, Length, Value>::type;

}

#endif
