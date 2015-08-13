/*
** File Name: list_operations.hpp
** Author:    Aditya Ramesh
** Date:      08/05/2015
** Contact:   _@adityaramesh.com
**
** Advanced list operations that are easier to implement using `functional.hpp`.
*/

#ifndef ZA52A5035_94F1_4F4E_9587_BD2A3D87A4E3
#define ZA52A5035_94F1_4F4E_9587_BD2A3D87A4E3

namespace cc {
namespace mpl {

/*
** Functions for subindexing.
*/

/*
** Creates a new list from the elements at the given indices in the given list.
*/
template <class List, class... Indices>
using select = fold<
	list<Indices...>,
	list<>,
	compose<
		quote<list>,
		quote<reverse>,
		uncurry<make_list<
			bind_back<quote<at>, List>,
			quote_trait<id>
		>>,
		uncurry<quote<append>>
	>
>;

template <class List, list_index... Indices>
using select_c = select<List, list_index_c<Indices>...>;

template <class Start, class End, class Inc = mpl::int_<1>>
using range = fold<
	repeat_n<divides<minus<End, Start>, Inc>, void>,
	list<Start>,
	compose<
		quote<list>,
		bind_back<quote<select>, list_index_c<0>, list_index_c<0>>,
		uncurry<make_list<
			compose<quote<back>, bind_back<quote<plus>, Inc>>,
			quote_trait<id>
		>>,
		uncurry<quote<append>>
	>
>;

template <class T, T Start, T End, T Inc = 1>
using range_c = range<
	std::integral_constant<T, Start>,
	std::integral_constant<T, End>,
	std::integral_constant<T, Inc>
>;

template <class Start, class End, class List>
using slice = apply_list<
	bind_front<quote<select>, List>,
	range<Start, End>
>;

template <list_index Start, list_index End, class List>
using slice_c = slice<list_index_c<Start>, list_index_c<End>, List>;

namespace detail {

template <class N, class Size, class List>
struct erase_front_n_helper
{ using type = slice<N, dec<size<List>>, List>; };

template <class N, class List>
struct erase_front_n_helper<N, N, List>
{ using type = list<>; };

template <class N, class Size, class List>
struct erase_back_n_helper
{ using type = slice<list_index_c<0>, minus<dec<size<List>>, N>, List>; };

template <class N, class List>
struct erase_back_n_helper<N, N, List>
{ using type = list<>; };

}

template <class N, class List>
using erase_front_n = _t<detail::erase_front_n_helper<N, size<List>, List>>;

template <class N, class List>
using erase_back_n = _t<detail::erase_back_n_helper<N, size<List>, List>>;

template <list_index N, class List>
using erase_front_nc = erase_front_n<list_index_c<N>, List>;

template <list_index N, class List>
using erase_back_nc = erase_back_n<list_index_c<N>, List>;

/*
** Generalizations of basic list operations.
**
** TODO:
** - erase_if
** - replace_if
** - find_all
** - sort, unique
*/

namespace detail {

template <list_index Index, class Func, class List>
struct find_if_helper;

template <list_index Index, class Func>
struct find_if_helper<Index, Func, list<>>
{ using type = no_match; };

template <list_index Index, class Func, class Head, class... Tail>
struct find_if_helper<Index, Func, list<Head, Tail...>> :
if_<
	apply<Func, Head>, id<list_index_c<Index>>,
	find_if_helper<Index + 1, Func, list<Tail...>>
> {};

}

template <class Func, class List>
using find_if = _t<detail::find_if_helper<0, Func, List>>;

/*
** List comparison.
*/

namespace detail {

template <bool LengthsEqual, class List1, class List2>
struct lists_same_helper;

template <class List1, class List2>
struct lists_same_helper<false, List1, List2>
{ using type = bool_<false>; };

template <class... Ts, class... Us>
struct lists_same_helper<true, list<Ts...>, list<Us...>>
{ using type = and_c<std::is_same<Ts, Us>::value...>; };

}

template <class List1, class List2>
using lists_same = _t<detail::lists_same_helper<
	List1::size == List2::size, List1, List2
>>;

namespace detail {

template <bool MatchPossible, class Query, class List>
struct starts_with_helper;

template <class Query, class List>
struct starts_with_helper<false, Query, List>
{ using type = bool_<false>; };

template <class Query, class List>
struct starts_with_helper<true, Query, List>
{ using type = lists_same<Query, slice_c<0, Query::size - 1, List>>; };

}

template <class Query, class List>
using starts_with = _t<detail::starts_with_helper<
	Query::size <= List::size, Query, List
>>;

}}

#endif
