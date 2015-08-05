/*
** File Name: list.hpp
** Author:    Aditya Ramesh
** Date:      01/17/2015
** Contact:   _@adityaramesh.com
**
** Defines the `mpl::list` data structure and some fundamental operations.
*/

#ifndef ZEC358EB2_B675_43F8_82E6_49742D0C10DF
#define ZEC358EB2_B675_43F8_82E6_49742D0C10DF

#include <ccbase/mpl/constant.hpp>

namespace cc {
namespace mpl {

using list_index = std::size_t;

template <class... Ts>
struct list
{
	using type = list;
	static constexpr auto size = sizeof...(Ts);
};

template <class List>
using size = std::integral_constant<list_index, List::size>;

template <class List>
using empty = bool_<List::size == 0>;

/*
** `at`
*/

namespace detail {

template <list_index Current, list_index Index, class List>
struct at_impl;

template <list_index Current, list_index Index, class Head, class... Tail>
struct at_impl<Current, Index, list<Head, Tail...>> :
at_impl<Current + 1, Index, list<Tail...>> {};

template <list_index Index, class Head, class... Tail>
struct at_impl<Index, Index, list<Head, Tail...>>
{ using type = Head; };

template <list_index Index, class List>
struct at_helper
{
	static_assert(Index < List::size, "Index out of bounds.");
	using type = typename at_impl<0, Index, List>::type;
};

}

template <list_index Index, class List>
using at_c = typename detail::at_helper<Index, List>::type;

template <class Index, class List>
using at = at_c<Index::value, List>;

template <class List>
using front = at_c<0, List>;

template <class List>
using back = at_c<List::size - 1, List>;

/*
** `cat`
*/

namespace detail {

template <class Head, class Tail>
struct cat_impl;

template <class... Ts, class... Us, class... Lists>
struct cat_impl<mpl::list<Ts...>, mpl::list<mpl::list<Us...>, Lists...>>
{
	using type = typename cat_impl<
		mpl::list<Ts..., Us...>,
		mpl::list<Lists...>
	>::type;
};

template <class Head>
struct cat_impl<Head, mpl::list<>>
{ using type = Head; };

template <class... Lists>
struct cat_helper
{
	static_assert(
		sizeof...(Lists) >= 2,
		"cat must be called with at least two arguments."
	);

	using type = typename cat_impl<mpl::list<>, mpl::list<Lists...>>::type;
};

}

template <class... Lists>
using cat = typename detail::cat_helper<Lists...>::type;

/*
** `prepend`, `append`
*/

namespace detail {

template <class Value, class List>
struct prepend_helper;

template <class Value, class... Ts>
struct prepend_helper<Value, list<Ts...>>
{ using type = list<Value, Ts...>; };

template <class Value, class List>
struct append_helper;

template <class Value, class... Ts>
struct append_helper<Value, list<Ts...>>
{ using type = list<Ts..., Value>; };

}

template <class Value, class List>
using prepend = typename detail::prepend_helper<Value, List>::type;

template <class Value, class List>
using append = typename detail::append_helper<Value, List>::type;

/*
** `find_first`
*/

using npos = intmax_t<-1>;

namespace detail {

template <list_index Index, class Value, class List>
struct find_first_helper;

template <list_index Index, class Value, class Head, class... Tail>
struct find_first_helper<Index, Value, list<Head, Tail...>> :
find_first_helper<Index + 1, Value, list<Tail...>> {};

template <list_index Index, class Value, class... Tail>
struct find_first_helper<Index, Value, list<Value, Tail...>>
{ using type = intmax_t<Index>; };

template <list_index Index, class Value>
struct find_first_helper<Index, Value, list<>>
{ using type = npos; };

}

template <class Value, class List>
using find_first = typename detail::find_first_helper<0, Value, List>::type;

/*
** `set_at`
*/

namespace detail {

template <
	list_index Current,
	list_index Index,
	class      Value,
	class      Head,
	class      Tail
>
struct set_at_impl;

template <
	list_index Current,
	list_index Index,
	class      Value,
	class...   Ts,
	class      U,
	class...   Us
>
struct set_at_impl<Current, Index, Value, list<Ts...>, list<U, Us...>> :
set_at_impl<Current + 1, Index, Value, list<Ts..., U>, list<Us...>> {};

template <
	list_index Index,
	class      Value,
	class...   Ts,
	class      U,
	class...   Us
>
struct set_at_impl<Index, Index, Value, list<Ts...>, list<U, Us...>>
{ using type = list<Ts..., Value, Us...>; };

template <list_index Index, class Value, class List>
struct set_at_helper
{
	static_assert(Index < List::size, "Index out of bounds.");
	using type = typename set_at_impl<0, Index, Value, list<>, List>::type;
};

}

template <list_index Index, class Value, class List>
using set_at_c = typename detail::set_at_helper<Index, Value, List>::type;

template <class Index, class Value, class List>
using set_at = set_at_c<Index::value, Value, List>;

/*
** `insert_at`
*/

namespace detail {

template <
	list_index Current,
	list_index Index,
	class      T,
	class      Head,
	class      Tail
>
struct insert_at_impl;

template <
	list_index Current,
	list_index Index,
	class      T,
	class      Head,
	class      U,
	class...   Us
>
struct insert_at_impl<Current, Index, T, Head, list<U, Us...>> :
insert_at_impl<Current + 1, Index, T, append<U, Head>, list<Us...>> {};

template <
	list_index Index,
	class      T,
	class      Head,
	class      U,
	class...   Us
>
struct insert_at_impl<Index, Index, T, Head, list<U, Us...>>
{
	using cur_tail = list<U, Us...>;
	using new_tail = prepend<T, cur_tail>;
	using type     = cat<Head, new_tail>;
};

template <
	list_index Index,
	class      T,
	class      Head
>
struct insert_at_impl<Index, Index, T, Head, list<>>
{ using type = append<T, Head>; };

template <list_index Index, class T, class List>
struct insert_at_helper
{
	static_assert(Index < List::size, "Index out of bounds.");
	using type = typename insert_at_impl<0, Index, T, list<>, List>::type;
};

}

template <list_index Index, class T, class List>
using insert_at_c = typename detail::insert_at_helper<Index, T, List>::type;

template <class Index, class T, class List>
using insert_at = insert_at_c<Index::value, T, List>;

/*
** `erase_at`
*/

namespace detail {

template <
	list_index Current,
	list_index Index,
	class      Head,
	class      Tail
>
struct erase_at_impl;

template <
	list_index Current,
	list_index Index,
	class      Head,
	class      T,
	class...   Ts
>
struct erase_at_impl<Current, Index, Head, list<T, Ts...>> :
erase_at_impl<Current + 1, Index, append<T, Head>, list<Ts...>> {};

template <
	list_index Index,
	class      Head,
	class      T,
	class...   Ts
>
struct erase_at_impl<Index, Index, Head, list<T, Ts...>>
{ using type = cat<Head, list<Ts...>>; };

template <list_index Index, class List>
struct erase_at_helper
{
	static_assert(Index < List::size, "Index out of bounds.");
	using type = typename erase_at_impl<0, Index, list<>, List>::type;
};

}

template <list_index Index, class List>
using erase_at_c = typename detail::erase_at_helper<Index, List>::type;

template <class Index, class List>
using erase_at = erase_at_c<Index::value, List>;

template <class List>
using erase_front = erase_at_c<0, List>;

template <class List>
using erase_back = erase_at_c<List::size - 1, List>;

/*
** `replace_at`
*/

template <list_index Index, class T, class List>
using replace_at_c = insert_at_c<Index, T, erase_at_c<Index, List>>;

template <class Index, class T, class List>
using replace_at = replace_at_c<Index::value, T, List>;

/*
** `contains`
*/

template <class List, class T>
using in = bool_<!std::is_same<find_first<T, List>, npos>::value>;

/*
** `reverse`
*/

namespace detail {

template <class Head, class Tail>
struct reverse_helper;

template <class... Ts, class U, class... Us>
struct reverse_helper<list<Ts...>, list<U, Us...>> :
reverse_helper<list<U, Ts...>, list<Us...>> {};

template <class Head>
struct reverse_helper<Head, list<>>
{ using type = Head; };

}

template <class List>
using reverse = typename detail::reverse_helper<list<>, List>::type;

/*
** `repeat`
*/

namespace detail {

template <list_index N, class T>
struct repeat_n_helper
{
	using type = cat<
		typename repeat_n_helper<N / 2, T>::type,
		typename repeat_n_helper<N / 2, T>::type,
		typename repeat_n_helper<N % 2, T>::type
	>;
};

template <class T>
struct repeat_n_helper<0, T>
{ using type = list<>; };

template <class T>
struct repeat_n_helper<1, T>
{ using type = list<T>; };

}

template <list_index N, class T = void>
using repeat_nc = typename detail::repeat_n_helper<N, T>::type;

template <class N, class T = void>
using repeat_n = repeat_nc<N::value, T>;

/*
** `to_types`
**
** Converts an `std::integer_sequence` to an `mpl::list`.
*/

namespace detail {

template <class List>
struct to_types_helper
{ using type = List; };

template <class Integer, Integer... Ts>
struct to_types_helper<std::integer_sequence<Integer, Ts...>>
{ using type = list<std::integral_constant<Integer, Ts>...>; };

}

template <class List>
using to_types = typename detail::to_types_helper<List>::type;

/*
** `to_values`
**
** Converts an `mpl::list` of `std::integral_constant`s to an
** `std::integer_sequence`.
*/

namespace detail {

template <class List>
struct to_values_helper;

template <class Integer, Integer Value, class... Tail>
struct to_values_helper<list<std::integral_constant<Integer, Value>, Tail...>>
{ using type = std::integer_sequence<Integer, Value, Tail::value...>; };

}

template <class List>
using to_values = typename detail::to_values_helper<List>::type;

}}

#endif
