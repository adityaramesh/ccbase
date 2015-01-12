/*
** File Name: sequence_operations.hpp
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

template <
	size_t Current,
	size_t Index,
	class Sequence
>
struct at_impl;

template <
	size_t Current,
	size_t Index,
	class Integer,
	Integer Head,
	Integer... Tail
>
struct at_impl<Current, Index, std::integer_sequence<Integer, Head, Tail...>>
{
	static constexpr auto value =
	at_impl<Current + 1, Index, std::index_sequence<Tail...>>::value;
};

template <
	size_t Index,
	class Integer,
	Integer Head,
	Integer... Tail
>
struct at_impl<Index, Index, std::integer_sequence<Integer, Head, Tail...>>
{
	static constexpr auto value = Head;
};

template <size_t Index, class Sequence>
static constexpr auto at = at_impl<0, Index, Sequence>::value;

/*
** The `find` metafunction.
*/

template <size_t Index, size_t Value, class Sequence>
struct find_impl;

template <
	size_t Index,
	size_t Value,
	class Integer,
	Integer Head,
	Integer... Tail
>
struct find_impl<
	Index,
	Value,
	std::integer_sequence<Integer, Head, Tail...>
>
{
	static constexpr auto value = find_impl<
		Index + 1,
		Value,
		std::integer_sequence<Integer, Tail...>
	>::value;
};

template <
	size_t Index,
	size_t Value,
	class Integer,
	Integer... Tail
>
struct find_impl<
	Index,
	Value,
	std::integer_sequence<Integer, Value, Tail...>
>
{
	static constexpr auto value = Index;
};

template <
	size_t Index,
	size_t Value,
	class Integer
>
struct find_impl<
	Index,
	Value,
	std::integer_sequence<Integer>
>
{
	static constexpr auto value = -1;
};

template <size_t Value, class Sequence>
static constexpr auto find = find_impl<0, Value, Sequence>::value;

/*
** The `cat` metafunction.
*/

template <class Seq1, class Seq2>
struct cat_impl;

template <class Integer, Integer... Ts, Integer... Us>
struct cat_impl<std::integer_sequence<Integer, Ts...>, std::integer_sequence<Integer, Us...>>
{
	using type = std::integer_sequence<Integer, Ts..., Us...>;
};

template <class Seq1, class Seq2>
using cat = typename cat_impl<Seq1, Seq2>::type;

/*
** The `append` metafunction.
*/

template <class Seq1, uintmax_t Value>
struct append_impl;


template <class Integer, Integer... Ts, uintmax_t Value>
struct append_impl<std::integer_sequence<Integer, Ts...>, Value>
{
	using type = std::integer_sequence<Integer, Ts..., Integer{Value}>;
};

template <class Seq, uintmax_t Value>
using append = typename append_impl<Seq, Value>::type;

/*
** The `constant_sequence` metafunction.
*/

template <class Integer, size_t Index, size_t Max, size_t Value, Integer... Ts>
struct constant_sequence_impl
{
	using type = typename constant_sequence_impl<
		Integer, Index + 1, Max, Value, Integer(Value), Ts...
	>::type;
};

template <class Integer, size_t Max, size_t Value, Integer... Ts>
struct constant_sequence_impl<Integer, Max, Max, Value, Ts...>
{
	using type = std::integer_sequence<Integer, Ts...>;
};

template <class Integer, size_t Length, size_t Value>
using constant_sequence =
typename constant_sequence_impl<Integer, 0, Length, Value>::type;

}

#endif
