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

namespace detail {

template <class F, class List>
struct apply_list_helper;

/*
** XXX: For some reasons, clang refuses to use this template specialization
** unless `list` has a fully-qualified namespace. I don't think there are any
** other definitions of `list`, so I'm not sure why this is happening. I don't
** have time to debug this right now.
*/
template <class F, class... Ts>
struct apply_list_helper<F, ::cc::mpl::list<Ts...>>
{ using type = apply<F, Ts...>; };

}

/*
** Applies `C` to the values that result from unpacking `List`.
*/
template <class C, class List>
using apply_list = _t<detail::apply_list_helper<C, List>>;

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
	struct helper
	{ using type = list<apply<Fs, Ts>...>; };
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
struct reverse_fold_helper<list<Head, Tail...>, State, F>
{ using type = apply<F, _t<reverse_fold_helper<list<Tail...>, State, F>>, Head>; };

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

}}

#endif
