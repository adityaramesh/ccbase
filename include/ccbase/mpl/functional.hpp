/*
** File Name: functional.hpp
** Author:    Aditya Ramesh
** Date:      01/13/2015
** Contact:   _@adityaramesh.com
**
** Utilities for functional TMP to improve composability. Based on the following
** header in Eric Niebler's range library:
** https://github.com/ericniebler/range-v3/blob/master/include/range/v3/utility/meta.hpp.
** Niebler's blog post explaining some of the concepts in this header file was
** also very useful.
**
** Note this header depends on `list.hpp`, so we can't move functions from
** `list.hpp` to this file. The former header file is designed to contain the
** minimal functionality necessary to make the implementation of this header
** reasonable.
*/

#ifndef ZB2EFAF00_D7AB_413B_810D_B90D84B03654
#define ZB2EFAF00_D7AB_413B_810D_B90D84B03654

#include <ccbase/mpl/list.hpp>

namespace cc {
namespace mpl {

/*
** Some specialized terminology:
** - A metafunction is a class template with zero or more non-value template
** parameter and a typedef called `type`.
** - A metafunction class is a class template with a publicly-accessible nested
** metafunction called `apply`. In some sense, a metafunction class computes its
** value lazily, since the value is only produced when the nested `apply`
** metafunction is called.
**
** MPL libraries become composable when built around the concepts of
** metafunctions and metafunction classes. In order to use these concepts in
** practice, we need to implement some machinery to work with them.
*/

/*
** Evaluates a metafunction.
*/
template <class T>
using eval = typename T::type;

/*
** Evaluates a metafunction class.
*/
template <class F, class... Args>
using apply = typename F::template apply<Args...>;

/*
** Turns an ordinary class template into a metafunction class.
*/
template <template <class...> class C>
struct quote
{
private:
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... Ts>
	struct helper
	{
		using type = C<Ts...>;
	};
public:
	template <class... Ts>
	using apply = eval<helper<Ts...>>;
};

/*
** Turns a metafunction into a metafunction class.
*/
template <template <class...> class C>
struct quote_trait
{
	template <class... Ts>
	using apply = eval<apply<quote<C>, Ts...>>;
};

/*
** Quotes a class template taking value template parameters.
*/
template <class T, template <T...> class C>
struct quote_v
{
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... Ts>
	struct helper
	{
		using type = C<Ts::type::value...>;
	};
public:
	template <class... Ts>
	using apply = eval<helper<Ts...>>;
};

/*
** Quotes a metafunction taking value template parameters.
*/
template <class T, template <T...> class C>
struct quote_trait_v
{
	template <class... Ts>
	using apply = eval<apply<quote_v<T, C>, Ts...>>;
};

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
	using tail = back<functions>;
	using head = erase_back<functions>;

	template <class... Ts>
	using apply = apply<tail, apply<compose_helper<head>, Ts...>>;
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

/*
** Creates an nary function by combining n unary functions.
*/
template <class... Fs>
struct combine
{
private:
	template <class... Ts>
	struct helper
	{
		using type = list<apply<Fs, Ts>...>;
	};
public:
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430. (At
	** least I think so. Clang gives a weird error message saying that the
	** sizes of `Fs` and `Ts` are unequal in certain contexts, and using a
	** helper struct solved the problem.)
	*/
	template <class... Ts>
	using apply = eval<helper<Ts...>>;
};

template <class T>
struct id
{ using type = T; };

template <class T>
struct always
{
private:
	template <class...>
	struct helper
	{ using type = T; };
public:
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... Ts>
	using apply = eval<helper<Ts...>>;
};

template <class F, class... Ts>
struct bind_front
{
private:
	template <class... Us>
	struct helper
	{ using type = apply<F, Ts..., Us...>; };
public:
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... Us>
	using apply = eval<helper<Us...>>;
};

template <class F, class... Ts>
struct bind_back
{
private:
	template <class... Us>
	struct helper
	{ using type = apply<F, Us..., Ts...>; };
public:
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... Us>
	using apply = eval<helper<Us...>>;
};

/*
** List application metafunctions.
*/

template <class F, class List>
struct lazy_apply_list;

template <class F, template <class...> class T, class... Ts>
struct lazy_apply_list<F, T<Ts...>>
{
	using type = apply<F, Ts...>;
};

template <class F, class T, T... Ts>
struct lazy_apply_list<F, std::integer_sequence<T, Ts...>>
{
	using type = apply<F, std::integral_constant<T, Ts>...>;
};

template <class C, class List>
using apply_list = eval<lazy_apply_list<C, List>>;

template <class F>
struct reverse_args
{
private:
	template <class List>
	struct helper
	{
		using type = apply_list<F, List>;
	};
public:
	template <class... Ts>
	using apply = eval<helper<reverse<list<Ts...>>>>;
};

/*
** A metafunction class that, when applied, applies `F` by packing `Ts...` into
** a type list.
*/
template <class F, class Q = quote<list>>
struct curry : compose<Q, F> {};

/*
** A metafunction class that, when applied, applies `F` by unpacking the type
** list `T`.
*/
template <class F>
struct uncurry
{
private:
	template <class List>
	struct helper
	{
		using type = eval<lazy_apply_list<F, List>>;
	};
public:
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... List>
	using apply = eval<helper<List...>>;
};

/*
** Joins a list of lists. Different from cat, which concatenates a variadic
** parameter pack of lists.
*/
template <class Lists>
using join = apply_list<quote<cat>, Lists>;

/*
** More list utilities.
**
** TODO:
** - Replace (all), find (all), replace_if, erase_if.
** - Unique.
*/

namespace detail {

template <std::intmax_t Index, class Func, class List>
struct find_first_if_helper;

template <std::intmax_t Index, class Func>
struct find_first_if_helper<Index, Func, list<>>
{ using type = no_match; };

template <std::intmax_t Index, class Func, class Head, class... Tail>
struct find_first_if_helper<Index, Func, list<Head, Tail...>> :
std::conditional_t<
	apply<Func, Head>::value,
	id<size_t<Index>>,
	find_first_if_helper<Index + 1, Func, list<Tail...>>
> {};

}

template <class Func, class List>
using find_first_if = eval<detail::find_first_if_helper<0, Func, List>>;

/*
** The `foldl` and `foldr` metafunctions.
*/

namespace detail {

template <class List, class State, class F>
struct foldl_helper;

template <class State, class F>
struct foldl_helper<list<>, State, F>
{ using type = State; };

template <class Head, class... Tail, class State, class F>
struct foldl_helper<list<Head, Tail...>, State, F> :
foldl_helper<list<Tail...>, apply<F, State, Head>, F> {};

template <class List, class State, class F>
struct foldr_helper;

template <class State, class F>
struct foldr_helper<list<>, State, F>
{ using type = State; };

template <class Head, class... Tail, class State, class F>
struct foldr_helper<list<Head, Tail...>, State, F>
{
	using type = apply<F, eval<foldr_helper<list<Tail...>, State, F>>, Head>;
};

}

template <class List, class State, class F>
using foldl = eval<detail::foldl_helper<List, State, F>>;

template <class List, class State, class F>
using foldr = eval<detail::foldr_helper<List, State, F>>;

/*
** More list functions.
*/

namespace detail {

template <class A, class B, class List>
struct slice_helper
{
	using actions = cat<
		repeat_n<A, quote<erase_front>>,
		repeat_nc<List::size() - B::value - 1, quote<erase_back>>
	>;
	using type = foldl<
		actions,
		List,
		reverse_args<quote<apply>>
	>;
};

}

template <class A, class B, class List>
using slice = eval<detail::slice_helper<A, B, List>>;

template <std::size_t A, std::size_t B, class List>
using slice_c = slice<size_t<A>, size_t<B>, List>;

/*
** Makes an nary version of a binary function (e.g. `plus`, `logical_and`).
*/
template <class F>
using make_nary = compose<
	quote<list>,
	bind_front<quote<repeat_n>, int_<2>>,
	uncurry<combine<
		quote<erase_front>,
		quote<front>
	>>,
	uncurry<bind_back<quote<foldl>, F>>
>;

/*
** The `transform` metafunction.
*/

namespace detail {

template <class List, class F>
struct transform_helper;

template <class... Ts, class F>
struct transform_helper<list<Ts...>, F>
{ using type = list<apply<F, Ts>...>; };

}

template <class List, class F>
using transform = eval<detail::transform_helper<List, F>>;

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

}

template <class List1, class List2, class F>
using zip_with_2 = eval<detail::zip_with_2_helper<List1, List2, F>>;

template <class F, class Lists>
using zip_with =
transform<
	foldl<
		Lists,
		repeat_n<size<front<Lists>>, F>,
		bind_back<quote<zip_with_2>, quote<bind_front>>
	>,
	quote<apply>
>;

template <class Lists>
using zip = zip_with<quote<list>, Lists>;

/*
** Arithmetic operations.
*/

#define mpl_define_binary_arithmetic_op(symbol, name)   \
template <class T, class U>                             \
using name = std::integral_constant<                    \
	decltype(T::type::value symbol U::type::value), \
	T::type::value symbol U::type::value>;

mpl_define_binary_arithmetic_op(+, plus)
mpl_define_binary_arithmetic_op(-, minus)
mpl_define_binary_arithmetic_op(*, multiplies)
mpl_define_binary_arithmetic_op(/, divides)
mpl_define_binary_arithmetic_op(%, modulus)
mpl_define_binary_arithmetic_op(&, bit_and)
mpl_define_binary_arithmetic_op(|, bit_or)
mpl_define_binary_arithmetic_op(^, bit_xor)

#undef mpl_define_binary_arithmetic_op

#define mpl_define_binary_logical_op(symbol, name) \
template <class T, class U>                        \
using name = std::integral_constant<bool,          \
	T::type::value symbol U::type::value>;

mpl_define_binary_logical_op(&&, logical_and)
mpl_define_binary_logical_op(||, logical_or)

#undef mpl_define_binary_logical_op

template <class T>
using negate = std::integral_constant<decltype(-T::type::value), -T::type::value>;

template <class T>
using bit_not = std::integral_constant<decltype(~T::type::value), ~T::type::value>;

#define mpl_define_binary_relational_op(symbol, name)     \
template <class T, class U>                               \
using name = bool_<(T::type::value symbol U::type::value)>;

mpl_define_binary_relational_op(==, equal_to)
mpl_define_binary_relational_op(!=, not_equal_to)
mpl_define_binary_relational_op(>,  greater)
mpl_define_binary_relational_op(>=, greater_equal)
mpl_define_binary_relational_op(<,  less)
mpl_define_binary_relational_op(<=, less_equal)

#undef mpl_define_binary_relational_op

template <bool... Ts>
static constexpr auto all_true = apply<
	uncurry<make_nary<quote<logical_and>>>,
	to_types<std::integer_sequence<bool, Ts...>>
>::value;

template <bool... Ts>
static constexpr auto any_true = apply<
	uncurry<make_nary<quote<logical_or>>>,
	to_types<std::integer_sequence<bool, Ts...>>
>::value;

/*
** Metafunctions for working with multiple streams of data simultaneously.
*/

/*
** Creates a new list by selecting the elements in a list corresponding to the
** given indices.
*/
template <class Indices>
struct select
{
	template <class List>
	using apply =
	foldl<
		Indices,
		list<>,
		compose<
			quote<list>,
			bind_front<quote<repeat_n>, int_<2>>,
			uncurry<combine<
				quote<back>,
				quote<front>
			>>,
			uncurry<combine<
				bind_back<quote<at>, List>,
				quote_trait<id>
			>>,
			uncurry<quote<append>>
		>
	>;
};

template <std::size_t... Indices>
struct select_c
{
private:
	template <class List>
	struct helper
	{
		using type =
		apply<select<list<size_t<Indices>...>>, List>;
	};
public:
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... List>
	using apply = eval<helper<List...>>;
};

template <class Start, class End>
using range = foldl<
	repeat_n<minus<End, Start>>,
	list<Start>,
	compose<
		quote<list>,
		select_c<0, 0>,
		uncurry<combine<
			compose<
				quote<back>,
				bind_front<quote<plus>, int_<1>>,
				bind_front<quote<cast>, char>
			>,
			quote_trait<id>
		>>,
		uncurry<quote<append>>
	>
>;

template <class T, T Start, T End>
using range_c = range<
	std::integral_constant<T, Start>,
	std::integral_constant<T, End>
>;

template <class Start, class End>
using select_range = select<range<Start, End>>;

template <std::size_t Start, std::size_t End>
using select_range_c = select_range<size_t<Start>, size_t<End>>;

namespace detail {

template <bool SkipHead, bool SkipTail, class Start, class End, class List>
struct group_range_helper;

template <class Start, class End, class List>
struct group_range_helper<true, true, Start, End, List>
{
	using type =
	mpl::cat<
		mpl::list<
			mpl::apply<mpl::select_range<Start, End>, List>
		>
	>;
};

template <class Start, class End, class List>
struct group_range_helper<false, true, Start, End, List>
{
	using type =
	mpl::cat<
		mpl::apply<mpl::select_range<int_<0>, mpl::minus<Start, int_<1>>>, List>,
		mpl::list<
			mpl::apply<mpl::select_range<Start, End>, List>
		>
	>;
};

template <class Start, class End, class List>
struct group_range_helper<true, false, Start, End, List>
{
	using type =
	mpl::cat<
		mpl::list<
			mpl::apply<mpl::select_range<Start, End>, List>
		>,
		mpl::apply<mpl::select_range<
			mpl::plus<End, int_<1>>,
			mpl::minus<size<List>, int_<1>>
		>, List>
	>;
};

template <class Start, class End, class List>
struct group_range_helper<false, false, Start, End, List>
{
	using type =
	mpl::cat<
		mpl::apply<mpl::select_range<int_<0>, mpl::minus<Start, int_<1>>>, List>,
		mpl::list<
			mpl::apply<mpl::select_range<Start, End>, List>
		>,
		mpl::apply<mpl::select_range<
			mpl::plus<End, int_<1>>,
			mpl::minus<size<List>, int_<1>>
		>, List>
	>;
};

}

/*
** Groups a range of elements in a list by nesting them within another list.
*/
template <class Start, class End>
struct group_range
{
private:
	template <class List>
	struct helper
	{
		using type =
		eval<detail::group_range_helper<
			equal_to<Start, int_<0>>::type::value,
			equal_to<End, minus<size<List>, int_<1>>>::type::value,
			Start, End, List
		>>;
	};
public:
	/*
	** Indirection here needed to avoid Core Issue 1430:
	** http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430.
	*/
	template <class... List>
	using apply = eval<helper<List...>>;
};

template <std::size_t Start, std::size_t End>
using group_range_c = group_range<size_t<Start>, size_t<End>>;

/*
** Functions involving permutations.
*/

/*
** Given a permutation in cycle notation (e.g. (1 4 3 5)), returns a
** decomposition into two-cycles. Note that we assume permutations are applied
** from left to right. So (1 4 3 5) decomposes into (5 3)(3 4)(4 1), *not* (1
** 4)(4 3)(3 5)!
*/
template <class Perms>
using two_cycles =
zip<list<
	reverse<erase_front<Perms>>,
	reverse<erase_back<Perms>>
>>;

/*
** Miscellaneous helpful metafunctions.
*/

template <template <class...> class F, class T>
struct is_specialization_of : std::false_type {};

template <template <class...> class F, class... Args>
struct is_specialization_of<F, F<Args...>> : std::true_type {};

}}

#endif
