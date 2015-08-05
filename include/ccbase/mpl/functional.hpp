/*
** File Name: functional.hpp
** Author:    Aditya Ramesh
** Date:      01/13/2015
** Contact:   _@adityaramesh.com
**
** Provides functional programming idioms for TMP. Adapted from Eric Niebler's
** [library called _Meta_][meta]. Niebler's blog post explaining some of the
** concepts in this header file was also very useful.
**
** # Development Notes
**
** This header depends on `list.hpp`, so we cannot move functions from
** `list.hpp` to this file. The purpose of former header is to define the list
** data structure, along with a few basic operations that can be implemented
** easily without the help of this file.
**
** [meta]: https://github.com/ericniebler/meta
** "Meta: A tiny metaprogramming library"
*/

#ifndef ZB2EFAF00_D7AB_413B_810D_B90D84B03654
#define ZB2EFAF00_D7AB_413B_810D_B90D84B03654

#include <ccbase/mpl/list.hpp>

namespace cc {
namespace mpl {

/*
** Some terminology:
** - A metafunction is a class template with zero or more non-value template
** parameter and a typedef called `type`.
** - A metafunction class is a class template with a publicly-accessible nested
** metafunction called `apply`. A metafunction class is "lazy" in the sense that
** it only computes the result when the nested `apply` metafunction is called.
**
** MPL libraries become composable when built using the concepts of
** metafunctions and metafunction classes. We first construct some machinery
** that allows us to work with them conveniently.
*/

/*
** Evaluates a metafunction.
*/
template <class T>
using _t = typename T::type;

/*
** Evaluates a metafunction, and obtains the value of the result.
*/
template <class T>
static constexpr auto _v = T::type::value;

/*
** Evaluates a metafunction class.
*/
template <class F, class... Args>
using apply = typename F::template apply<Args...>;

/*
** Defers the instantiation of the template `C` with parameters `Ts` in a lambda
** or let expression.
*/
template <template <class...> class C, class... Ts>
struct defer
{ using type = C<Ts...>; };

/*
** AFAICT, the purpose of lazy metafunctions is to allow us to inherit from them
** when writing helper structs.
*/
#define nd_make_lazy(name)                       \
	namespace lazy {                         \
		template <class... Ts>           \
		using name = defer<name, Ts...>; \
	}

nd_make_lazy(list)
nd_make_lazy(apply)

/*
** Turns an ordinary class template into a metafunction class.
*/
template <template <class...> class C>
struct quote
{
	/*
	** Indirection through defer here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... Ts>
	using apply = _t<defer<C, Ts...>>;
};

/*
** Turns a metafunction into a metafunction class.
*/
template <template <class...> class C>
struct quote_trait
{
	template <class... Ts>
	using apply = _t<apply<quote<C>, Ts...>>;
};

template <class T>
struct id
{ using type = T; };

/*
** Unlike in Niebler's library, composition works by applying the leftmost
** function first. I find that this is a lot more legible.
*/

namespace detail {

template <class List>
struct compose_helper;

template <class... Fs>
struct compose_helper<list<Fs...>>
{
	using functions = list<Fs...>;
	using last      = back<functions>;
	using head      = erase_back<functions>;

	template <class... Ts>
	using apply = apply<last, apply<compose_helper<head>, Ts...>>;
};

template <class F>
struct compose_helper<list<F>>
{
	template <class... Ts>
	using apply = apply<F, Ts...>;
};

}

template <class... Fs>
using compose = apply<quote<detail::compose_helper>, list<Fs...>>;

template <class F, class... Ts>
struct bind_front
{
	template <class... Us>
	using apply = apply<F, Ts..., Us...>;
};

template <class F, class... Ts>
struct bind_back
{
	template <class... Us>
	using apply = apply<F, Us..., Ts...>;
};

namespace lazy {

template <class F, class List>
struct apply_list;

/*
** XXX: For some reasons, clang refuses to use this template specialization
** unless `list` has a fully-qualified namespace. I don't think there are any
** other definitions of `list`, so I'm not sure why this is happening. I don't
** have time to debug this right now.
*/
template <class F, class... Ts>
struct apply_list<F, ::cc::mpl::list<Ts...>> :
lazy::apply<F, Ts...> {};

}

/*
** Applies `C` to the values that result from unpacking `List`.
*/
template <class C, class List>
using apply_list = _t<lazy::apply_list<C, List>>;

/*
** Returns a function that applies `F` by packing `Ts...` into a type list.
*/
template <class F>
using curry = compose<quote<list>, F>;

/*
** Returns a function that applies `F` by unpacking the type list `T`.
*/
template <class F>
using uncurry = bind_front<quote<apply_list>, F>;

template <class F>
using reverse_args = compose<quote<list>, quote<reverse>, uncurry<F>>;

/*
** Takes n functions `f_1, ..., f_n`, and returns a function that creates a list
** whose `i`th element is `f_i(x_i)`, where `x_i` is the `i`th component of the
** parameter pack of inputs `Ts`. Useful in contexts such as `fold`.
*/
template <class... Fs>
struct make_list
{
private:
	template <class... Ts>
	struct helper : lazy::list<apply<Fs, Ts>...> {};
public:
	template <class... Ts>
	using apply = _t<helper<Ts...>>;
};

namespace detail {

template <class List, class State, class F>
struct fold_helper;

template <class State, class F>
struct fold_helper<list<>, State, F>
{ using type = State; };

template <class Head, class... Tail, class State, class F>
struct fold_helper<list<Head, Tail...>, State, F> :
fold_helper<list<Tail...>, apply<F, State, Head>, F> {};

template <class List, class State, class F>
struct reverse_fold_helper;

template <class State, class F>
struct reverse_fold_helper<list<>, State, F>
{ using type = State; };

template <class Head, class... Tail, class State, class F>
struct reverse_fold_helper<list<Head, Tail...>, State, F> :
lazy::apply<F, _t<reverse_fold_helper<list<Tail...>, State, F>>, Head> {};

}

template <class List, class State, class F>
using fold = _t<detail::fold_helper<List, State, F>>;

template <class List, class State, class F>
using reverse_fold = _t<detail::reverse_fold_helper<List, State, F>>;

namespace detail {

template <class List, class F>
struct transform_helper;

template <class... Ts, class F>
struct transform_helper<list<Ts...>, F>
{ using type = list<apply<F, Ts>...>; };

}

/*
** Maps `(a_1, ..., a_n) -> (f(a_1), ..., f(a_n))`.
*/
template <class List, class F>
using transform = _t<detail::transform_helper<List, F>>;

/*
** Joins a list of lists. Different from cat, which concatenates a variadic
** parameter pack of lists.
*/
template <class Lists>
using join = apply_list<quote<cat>, Lists>;

/*
** The `zip` and `zip_with` metafunctions. We first define `zip_with` for the
** special case of a list of two lists, and then generalize it.
*/

namespace detail {

template <class List1, class List2, class F>
struct zip_with_2_helper;

template <class... Ts, class... Us, class F>
struct zip_with_2_helper<list<Ts...>, list<Us...>, F>
{ using type = list<apply<F, Ts, Us>...>; };

template <class List1, class List2, class F>
using zip_with_2 = _t<zip_with_2_helper<List1, List2, F>>;

}

/*
** Maps `[(a_11, ..., a_1n), (a_21, ..., a_2n), ... (a_m1, ..., a_mn)] ->
** (f(a_11, ..., a_m1), f(a_12, ..., a_m2), ..., f(a_1n, ..., a_mn))`.
*/
template <class F, class... Lists>
using zip_with =
transform<
	fold<
		list<Lists...>,
		repeat_n<size<front<list<Lists...>>>, F>,
		bind_back<quote<detail::zip_with_2>, quote<bind_front>>
	>,
	quote<apply>
>;

template <class... Lists>
using zip = zip_with<quote<list>, Lists...>;

/*
** Makes an nary version of a binary function.
*/
template <class F>
using make_nary = compose<
	// TODO: the first two lines can be replaced by a lambda.
	curry<bind_front<quote<repeat_n>, int_<2>>>,
	uncurry<make_list<quote<erase_front>, quote<front>>>,
	uncurry<bind_back<quote<fold>, F>>
>;


/*
** Useful traits.
*/

template <template <class...> class F, class T>
struct is_specialization_of : std::false_type {};

template <template <class...> class F, class... Args>
struct is_specialization_of<F, F<Args...>> : std::true_type {};

// After the above is implemented, include the arithmetic and logical functions
// in a separate header.

///*
//** More list utilities.
//**
//** TODO:
//** - Replace (all), find (all), replace_if, erase_if.
//** - Unique.
//*/
//
//namespace detail {
//
//template <std::intmax_t Index, class Func, class List>
//struct find_first_if_helper;
//
//template <std::intmax_t Index, class Func>
//struct find_first_if_helper<Index, Func, list<>>
//{ using type = no_match; };
//
//template <std::intmax_t Index, class Func, class Head, class... Tail>
//struct find_first_if_helper<Index, Func, list<Head, Tail...>> :
//std::conditional_t<
//	apply<Func, Head>::value,
//	id<size_t<Index>>,
//	find_first_if_helper<Index + 1, Func, list<Tail...>>
//> {};
//
//}
//
//template <class Func, class List>
//using find_first_if = eval<detail::find_first_if_helper<0, Func, List>>;
//
///*
//** More list functions.
//*/
//
//namespace detail {
//
//template <class A, class B, class List>
//struct slice_helper
//{
//	using actions = cat<
//		repeat_n<A, quote<erase_front>>,
//		repeat_nc<List::size() - B::value - 1, quote<erase_back>>
//	>;
//	using type = foldl<
//		actions,
//		List,
//		reverse_args<quote<apply>>
//	>;
//};
//
//}
//
//template <class A, class B, class List>
//using slice = eval<detail::slice_helper<A, B, List>>;
//
//template <std::size_t A, std::size_t B, class List>
//using slice_c = slice<size_t<A>, size_t<B>, List>;
//
///*
//** Functions for list comparison.
//*/
//
//template <class T1, class T2>
//using is_same = bool_<std::is_same<T1, T2>::value>;
//
//namespace detail {
//
//template <bool LengthsEqual, class List1, class List2>
//struct lists_same_helper;
//
//template <class List1, class List2>
//struct lists_same_helper<false, List1, List2>
//{ using type = bool_<false>; };
//
//template <class List1, class List2>
//struct lists_same_helper<true, List1, List2>
//{
//	using type = foldl<
//		transform<
//			zip<list<List1, List2>>,
//			uncurry<quote<is_same>>
//		>,
//		bool_<true>,
//		quote<logical_and>
//	>;
//};
//
//}
//
//template <class List1, class List2>
//using lists_same = eval<detail::lists_same_helper<
//	List1::size() == List2::size(), List1, List2
//>>;
//
//namespace detail {
//
//template <bool MatchPossible, class Query, class List>
//struct starts_with_helper;
//
//template <class Query, class List>
//struct starts_with_helper<false, Query, List>
//{ using type = bool_<false>; };
//
//template <class Query, class List>
//struct starts_with_helper<true, Query, List>
//{
//	using type = lists_same<
//		Query,
//		slice_c<0, Query::size() - 1, List>
//	>;
//};
//
//}
//
//template <class Query, class List>
//using starts_with = eval<detail::starts_with_helper<
//	Query::size() <= List::size(), Query, List
//>>;
//
///*
//** Creates a new list by selecting the elements in a list corresponding to the
//** given indices.
//*/
//template <class Indices>
//struct select
//{
//	template <class List>
//	using apply =
//	foldl<
//		Indices,
//		list<>,
//		compose<
//			quote<list>,
//			bind_front<quote<repeat_n>, int_<2>>,
//			uncurry<combine<
//				quote<back>,
//				quote<front>
//			>>,
//			uncurry<combine<
//				bind_back<quote<at>, List>,
//				quote_trait<id>
//			>>,
//			uncurry<quote<append>>
//		>
//	>;
//};
//
//template <std::size_t... Indices>
//struct select_c
//{
//private:
//	template <class List>
//	struct helper
//	{
//		using type =
//		apply<select<list<size_t<Indices>...>>, List>;
//	};
//public:
//	/*
//	** Indirection here needed to avoid Core Issue 1430:
//	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
//	*/
//	template <class... List>
//	using apply = eval<helper<List...>>;
//};
//
//template <class Start, class End>
//using range = foldl<
//	repeat_n<minus<End, Start>>,
//	list<Start>,
//	compose<
//		quote<list>,
//		select_c<0, 0>,
//		uncurry<combine<
//			compose<
//				quote<back>,
//				bind_front<quote<plus>, int_<1>>,
//				bind_front<quote<cast>, char>
//			>,
//			quote_trait<id>
//		>>,
//		uncurry<quote<append>>
//	>
//>;
//
//template <class T, T Start, T End>
//using range_c = range<
//	std::integral_constant<T, Start>,
//	std::integral_constant<T, End>
//>;
//
//template <class Start, class End>
//using select_range = select<range<Start, End>>;
//
//template <std::size_t Start, std::size_t End>
//using select_range_c = select_range<size_t<Start>, size_t<End>>;

}}

#undef nd_make_lazy
#endif
