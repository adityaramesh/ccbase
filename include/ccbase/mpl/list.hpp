/*
** File Name: list.hpp
** Author:    Aditya Ramesh
** Date:      01/17/2015
** Contact:   _@adityaramesh.com
**
** Defines the MPL list data structure along with the associated fundamental
** operations. Partially based on an MPL library I wrote earlier.
*/

#ifndef ZEC358EB2_B675_43F8_82E6_49742D0C10DF
#define ZEC358EB2_B675_43F8_82E6_49742D0C10DF

#include <ccbase/mpl/constant.hpp>

namespace cc {
namespace mpl {

template <class... Ts>
struct list
{
	using type = list;

	static constexpr std::size_t size() noexcept
	{ return sizeof...(Ts); }
};

template <class List>
using size = size_t<List::size()>;

template <class List>
using empty = bool_<List::size() == 0>;

/*
** The `at` metafunction.
*/

namespace detail {

template <std::size_t Current, std::size_t Index, class List>
struct at_c_helper;

template <std::size_t Current, std::size_t Index, class Head, class... Tail>
struct at_c_helper<Current, Index, list<Head, Tail...>> :
at_c_helper<Current + 1, Index, list<Tail...>> {};

template <std::size_t Index, class Head, class... Tail>
struct at_c_helper<Index, Index, list<Head, Tail...>>
{ using type = Head; };

}

template <std::size_t Index, class List>
using at_c = typename detail::at_c_helper<0, Index, List>::type;

template <class Index, class List>
using at = at_c<Index::type::value, List>;

template <class List>
using front = at_c<0, List>;

template <class List>
using back = at_c<List::size() - 1, List>;

/*
** The `cat` metafunction.
*/

namespace detail {

template <class... Lists>
struct cat_helper;

template <class... As>
struct cat_helper<list<As...>>
{ using type = list<As...>; };

template <class... As, class... Bs>
struct cat_helper<list<As...>, list<Bs...>> :
cat_helper<list<As..., Bs...>> {};

template <class... As, class... Bs, class... Cs>
struct cat_helper<list<As...>, list<Bs...>, list<Cs...>> :
cat_helper<list<As..., Bs..., Cs...>> {};

template <class... As, class... Bs, class... Cs, class... Ds>
struct cat_helper<list<As...>, list<Bs...>, list<Cs...>, list<Ds...>> :
cat_helper<list<As..., Bs..., Cs..., Ds...>> {};

template <class... As, class... Bs, class... Cs, class... Ds, class... Es>
struct cat_helper<list<As...>, list<Bs...>, list<Cs...>, list<Ds...>,
	list<Es...>> :
cat_helper<list<As..., Bs..., Cs..., Ds..., Es...>> {};

template <class... As, class... Bs, class... Cs, class... Ds, class... Es,
	 class... Fs>
struct cat_helper<list<As...>, list<Bs...>, list<Cs...>, list<Ds...>, list<Es...>,
	list<Fs...>> :
cat_helper<list<As..., Bs..., Cs..., Ds..., Es..., Fs...>> {};

template <class... As, class... Bs, class... Cs, class... Ds, class... Es,
	 class... Fs, class... Gs>
struct cat_helper<list<As...>, list<Bs...>, list<Cs...>, list<Ds...>, list<Es...>,
	list<Fs...>, list<Gs...>> :
cat_helper<list<As..., Bs..., Cs..., Ds..., Es..., Fs..., Gs...>> {};

template <class... As, class... Bs, class... Cs, class... Ds, class... Es,
	 class... Fs, class... Gs, class... Hs>
struct cat_helper<list<As...>, list<Bs...>, list<Cs...>, list<Ds...>, list<Es...>,
	list<Fs...>, list<Gs...>, list<Hs...>> :
cat_helper<list<As..., Bs..., Cs..., Ds..., Es..., Fs..., Gs..., Hs...>> {};

template <class... As, class... Bs, class... Cs, class... Ds, class... Es,
	 class... Fs, class... Gs, class... Hs, class... Is>
struct cat_helper<list<As...>, list<Bs...>, list<Cs...>, list<Ds...>, list<Es...>,
	list<Fs...>, list<Gs...>, list<Hs...>, list<Is...>> :
cat_helper<list<As..., Bs..., Cs..., Ds..., Es..., Fs..., Gs..., Hs...,
	Is...>> {};

template <class... As, class... Bs, class... Cs, class... Ds, class... Es,
	 class... Fs, class... Gs, class... Hs, class... Is, class... Js>
struct cat_helper<list<As...>, list<Bs...>, list<Cs...>, list<Ds...>, list<Es...>,
	list<Fs...>, list<Gs...>, list<Hs...>, list<Is...>, list<Js...>> :
cat_helper<list<As..., Bs..., Cs..., Ds..., Es..., Fs..., Gs..., Hs..., Is...,
	Js...>> {};

}

template <class... Lists>
using cat = typename detail::cat_helper<Lists...>::type;

/*
** The `find_first` metafunction.
*/

using no_match = intmax_t<-1>;

namespace detail {

template <std::intmax_t Index, class Value, class List>
struct find_first_helper;

template <std::intmax_t Index, class Value, class Head, class... Tail>
struct find_first_helper<Index, Value, list<Head, Tail...>> :
find_first_helper<Index + 1, Value, list<Tail...>> {};

template <std::intmax_t Index, class Value, class... Tail>
struct find_first_helper<Index, Value, list<Value, Tail...>>
{ using type = intmax_t<Index>; };

template <std::intmax_t Index, class Value>
struct find_first_helper<Index, Value, list<>>
{ using type = no_match; };

}

template <class Value, class List>
using find_first = typename detail::find_first_helper<0, Value, List>::type;

/*
** The `prepend` and `append` metafunctions.
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
** The `set_at` metafunction.
*/

namespace detail {

template <
	std::size_t Current,
	std::size_t Index,
	class          Value,
	class          Head,
	class          Tail
>
struct set_at_helper;

template <
	std::size_t Current,
	std::size_t Index,
	class          Value,
	class...       Ts,
	class          U,
	class...       Us
>
struct set_at_helper<Current, Index, Value, list<Ts...>, list<U, Us...>> :
set_at_helper<Current + 1, Index, Value, list<Ts..., U>, list<Us...>> {};

template <
	std::size_t Index,
	class          Value,
	class...       Ts,
	class          U,
	class...       Us
>
struct set_at_helper<Index, Index, Value, list<Ts...>, list<U, Us...>>
{ using type = list<Ts..., Value, Us...>; };

}

template <std::size_t Index, class Value, class List>
using set_at_c = typename detail::set_at_helper<0, Index, Value, list<>, List>::type;

template <class Index, class Value, class List>
using set_at = set_at_c<Index::type::value, Value, List>;

/*
** The `insert_at` metafunction.
*/

namespace detail {

template <
	std::size_t Current,
	std::size_t Index,
	class          T,
	class          Head,
	class          Tail
>
struct insert_at_helper;

template <
	std::size_t Current,
	std::size_t Index,
	class          T,
	class          Head,
	class          U,
	class...       Us
>
struct insert_at_helper<Current, Index, T, Head, list<U, Us...>> :
insert_at_helper<Current + 1, Index, T, append<U, Head>, list<Us...>> {};

template <
	std::size_t Index,
	class          T,
	class          Head,
	class          U,
	class...       Us
>
struct insert_at_helper<Index, Index, T, Head, list<U, Us...>>
{
	using tail = list<U, Us...>;
	using t = prepend<T, tail>;
	using type = cat<Head, t>;
};

template <
	std::size_t Index,
	class          T,
	class          Head
>
struct insert_at_helper<Index, Index, T, Head, list<>>
{ using type = append<T, Head>; };

}

template <std::size_t Index, class T, class List>
using insert_at_c = typename detail::insert_at_helper<
	0, Index, T, list<>, List
>::type;

template <class Index, class T, class List>
using insert_at = insert_at_c<Index::type::value, T, List>;

/*
** The `erase_at` metafunction.
*/

namespace detail {

template <
	std::size_t Current,
	std::size_t Index,
	class          Head,
	class          Tail
>
struct erase_at_helper;

template <
	std::size_t Current,
	std::size_t Index,
	class          Head,
	class          T,
	class...       Ts
>
struct erase_at_helper<Current, Index, Head, list<T, Ts...>> :
erase_at_helper<Current + 1, Index, append<T, Head>, list<Ts...>> {};

template <
	std::size_t Index,
	class          Head,
	class          T,
	class...       Ts
>
struct erase_at_helper<Index, Index, Head, list<T, Ts...>>
{ using type = cat<Head, list<Ts...>>; };

}

template <std::size_t Index, class List>
using erase_at_c = typename detail::erase_at_helper<
	0, Index, list<>, List
>::type;

template <class Index, class List>
using erase_at = erase_at_c<Index::type::value, List>;

template <class List>
using erase_front = erase_at_c<0, List>;

template <class List>
using erase_back = erase_at_c<List::size() - 1, List>;

/*
** The `replace_at` metafunction.
*/

template <class Index, class T, class List>
using replace_at = insert_at<Index, T, erase_at<Index, List>>;

template <std::size_t Index, class T, class List>
using replace_at_c = replace_at<size_t<Index>, T, List>;

/*
** The `contains` metafunction.
*/

namespace detail {

template <class T, class List>
struct contains_helper;

template <class T, class U, class... Us>
struct contains_helper<T, list<U, Us...>> :
contains_helper<T, list<Us...>> {};

template <class T, class... Us>
struct contains_helper<T, list<T, Us...>> :
std::true_type {};

template <class T>
struct contains_helper<T, list<>> :
std::false_type {};

}

template <class T, class List>
using contains = typename detail::contains_helper<T, List>::type;

/*
** The `reverse` metafunction.
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
** The `repeat` metafunction.
*/

namespace detail {

template <std::size_t N, class T>
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

template <std::size_t N, class T = void>
using repeat_nc = typename detail::repeat_n_helper<N, T>::type;

template <class N, class T = void>
using repeat_n = repeat_nc<N::type::value, T>;

/*
** `to_types` is used to convert an `std::integer_sequence` into a `cc::list`
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
** `to_values` is used to convert a `cc::list` of `std::integral_constants`
** into an `std::integral_sequence`
*/

namespace detail {

template <class List>
struct to_values_helper;

template <class Integer, Integer Value, class... Tail>
struct to_values_helper<list<std::integral_constant<Integer, Value>, Tail...>>
{
	using type = std::integer_sequence<Integer, Value, Tail::value...>;
};

}

template <class List>
using to_values = typename detail::to_values_helper<List>::type;

/*
** `to_value_lists` is used to convert a list of lists of
** `std::integral_constants` into a list of `std::integer_sequence`s. Note that
** unlike `to_values`, `to_value_lists` requires the programmer to specify the
** integral type of the value. This is because it is possible that `List` is
** actually a sequence of empty sequences, in which case we cannot automatically
** infer the integer type.
*/

namespace detail {

template <class Integer, class List>
struct to_value_lists_helper_2
{ using type = to_values<List>; };

template <class Integer>
struct to_value_lists_helper_2<Integer, list<>>
{ using type = std::integer_sequence<Integer>; };

template <class Integer, class List>
struct to_value_lists_helper;

template <class Integer, class... Lists>
struct to_value_lists_helper<Integer, list<Lists...>>
{
	using type = list<typename to_value_lists_helper_2<Integer, Lists>::type...>;
};

}

template <class Integer, class List>
using to_value_lists = typename detail::to_value_lists_helper<Integer, List>::type;

}}

#endif
