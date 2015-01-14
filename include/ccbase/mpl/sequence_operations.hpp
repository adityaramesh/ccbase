/*
** File Name: sequence_operations.hpp
** Author:    Aditya Ramesh
** Date:      01/03/2015
** Contact:   _@adityaramesh.com
*/

#ifndef ZF8995D56_732C_4E70_83EE_78FE6E016B50
#define ZF8995D56_732C_4E70_83EE_78FE6E016B50

#include <ccbase/mpl/types.hpp>

namespace cc {

/*
** The `at` metafunction.
*/

template <size_t Current, size_t Index, class Seq>
struct at_helper;

template <size_t Current, size_t Index, class Head, class... Tail>
struct at_helper<Current, Index, seq<Head, Tail...>>
{
	using type = typename at_helper<
		Current + 1, Index, seq<Tail...>
	>::type;
};

template <size_t Index, class Head, class... Tail>
struct at_helper<Index, Index, seq<Head, Tail...>>
{
	using type = Head;
};

template <size_t Index, class Seq>
using at = typename at_helper<0, Index, Seq>::type;

/*
** The `find` metafunction.
*/

static constexpr auto no_match = int{-1};

template <size_t Index, class Value, class Seq>
struct find_helper;

template <size_t Index, class Value, class Head, class... Tail>
struct find_helper<Index, Value, seq<Head, Tail...>>
{
	static constexpr auto value =
	find_helper<Index + 1, Value, seq<Tail...>>::value;
};

template <size_t Index, class Value, class... Tail>
struct find_helper<Index, Value, seq<Value, Tail...>>
{
	static constexpr auto value = Index;
};

template <size_t Index, class Value>
struct find_helper<Index, Value, seq<>>
{
	static constexpr auto value = no_match;
};

template <class Value, class Seq>
static constexpr auto find = find_helper<0, Value, Seq>::value;

/*
** The `cat` metafunction.
*/

template <class Seq1, class Seq2>
struct cat_helper;

template <class... Ts, class... Us>
struct cat_helper<seq<Ts...>, seq<Us...>>
{ using type = seq<Ts..., Us...>; };

template <class Seq1, class Seq2>
using cat = typename cat_helper<Seq1, Seq2>::type;

/*
** The `append` metafunction.
*/

template <class Seq1, class Value>
struct append_helper;

template <class... Ts, class Value>
struct append_helper<seq<Ts...>, Value>
{ using type = seq<Ts..., Value>; };

template <class Seq, class Value>
using append = typename append_helper<Seq, Value>::type;

/*
** The `cseq` metafunction.
*/

template <size_t Index, size_t Max, class Value, class... Ts>
struct cseq_helper
{
	using type = typename cseq_helper<
		Index + 1, Max, Value, Value, Ts...
	>::type;
};

template <size_t Max, class Value, class... Ts>
struct cseq_helper<Max, Max, Value, Ts...>
{
	using type = seq<Ts...>;
};

template <size_t Length, class Value>
using cseq = typename cseq_helper<0, Length, Value>::type;

}

#endif
