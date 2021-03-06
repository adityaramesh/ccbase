/*
** File Name: operations.hpp
** Author:    Aditya Ramesh
** Date:      08/05/2015
** Contact:   _@adityaramesh.com
**
** Definitions of arithmetic and logical operations.
*/

#ifndef Z1A37E0A0_607A_4903_8947_4A2FA4AD06BC
#define Z1A37E0A0_607A_4903_8947_4A2FA4AD06BC

namespace cc {
namespace mpl {

/*
** Arithmetic operations.
*/

#define mpl_define_binary_arithmetic_op(symbol, name) \
template <class T, class U>                           \
using name = std::integral_constant<                  \
	decltype(T::value symbol U::value),           \
	T::value symbol U::value                      \
>;

#define mpl_make_nary_op(name) \
	template <class... Ts> \
	using name = apply<make_nary<quote<detail::name>>, Ts...>;

namespace detail {

/*
** We first define the associative operations here, and then make the versions
** in the `mpl` namespace variadic.
*/
mpl_define_binary_arithmetic_op(+, plus)
mpl_define_binary_arithmetic_op(*, multiplies)
mpl_define_binary_arithmetic_op(&, bit_and)
mpl_define_binary_arithmetic_op(|, bit_or)
mpl_define_binary_arithmetic_op(^, bit_xor)

}

mpl_make_nary_op(plus)
mpl_make_nary_op(multiplies)
mpl_make_nary_op(bit_and)
mpl_make_nary_op(bit_or)
mpl_make_nary_op(bit_xor)

mpl_define_binary_arithmetic_op(-, minus)
mpl_define_binary_arithmetic_op(/, divides)
mpl_define_binary_arithmetic_op(%, modulus)
mpl_define_binary_arithmetic_op(<<, left_shift)

#undef mpl_define_binary_arithmetic_op

template <class T>
using negate = std::integral_constant<decltype(-T::value), -T::value>;

template <class T>
using bit_not = std::integral_constant<decltype(~T::value), ~T::value>;

/*
** We need the help of a helper struct to implement right shift, in order to
** avoid a parsing error due to the `>>` operator being interpreted as the end
** of the template alias declaration. Let me know if you find a more elegant
** workaround.
*/

namespace detail {

template <class T, class U, T A, U B>
struct right_shift_helper
{ static constexpr auto value = (A >> B); };

}

template <class T, class U>
using right_shift = std::integral_constant<
	decltype(T::value >> U::value),
	detail::right_shift_helper<
		typename T::type, typename U::type,
		T::value, U::value
	>::value
>;

template <class T>
using inc = std::integral_constant<std::remove_cv_t<decltype(T::value)>,
      T::value + 1>;

template <class T>
using dec = std::integral_constant<std::remove_cv_t<decltype(T::value)>,
      T::value - 1>;

namespace detail {

template <class A, class B>
using min = std::conditional_t<A::value <= B::value, A, B>;

template <class A, class B>
using max = std::conditional_t<A::value >= B::value, A, B>;

}

mpl_make_nary_op(min)
mpl_make_nary_op(max)

/*
** Logical operations.
*/

#define mpl_define_binary_logical_op(symbol, name) \
template <class T, class U>                        \
using name = std::integral_constant<bool,          \
	T::value symbol U::value>;

namespace detail {

mpl_define_binary_logical_op(&&, and_)
mpl_define_binary_logical_op(||, or_)

}

#undef mpl_define_binary_logical_op

// AKA `all_of`.
mpl_make_nary_op(and_)
// AKA `any_of`.
mpl_make_nary_op(or_)

#undef mpl_make_nary_op

template <bool... Ts>
using and_c = and_<bool_<Ts>...>;

template <bool... Ts>
using or_c = or_<bool_<Ts>...>;

#define mpl_define_binary_relational_op(symbol, name) \
template <class T, class U>                           \
using name = bool_<(T::value symbol U::value)>;

mpl_define_binary_relational_op(==, equal_to)
mpl_define_binary_relational_op(!=, not_equal_to)
mpl_define_binary_relational_op(>,  greater)
mpl_define_binary_relational_op(>=, greater_equal)
mpl_define_binary_relational_op(<,  less)
mpl_define_binary_relational_op(<=, less_equal)

#undef mpl_define_binary_relational_op

template <class... Ts>
using all_equal = apply<make_nary<quote<equal_to>>, Ts...>;

template <class T>
using not_ = bool_<!T::value>;

/*
** Miscellaneous boolean traits.
*/

template <bool V, class A, class B>
using if_c = std::conditional_t<V, A, B>;

template <class T, class A, class B>
using if_ = if_c<T::value, A, B>;

namespace detail {

template <bool V, class T, class... Ts>
struct is_same_helper;

template <bool V, class T, class U, class... Ts>
struct is_same_helper<V, T, U, Ts...> :
is_same_helper<V && std::is_same<T, U>::value, T, Ts...> {};

template <bool V, class T>
struct is_same_helper<V, T>
{ using type = bool_<V>; };

}

/*
** We use template specialization instead of `fold` because the latter somehow
** results in an ICE on clang 3.6. I don't have the time to make an MWE now.
*/
template <class... Ts>
using is_same = _t<detail::is_same_helper<true, Ts...>>;

}}

#endif
