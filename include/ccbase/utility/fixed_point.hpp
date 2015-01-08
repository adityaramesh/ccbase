/*
** File Name: fixed_point.hpp
** Author:    Aditya Ramesh
** Date:      01/07/2015
** Contact:   _@adityaramesh.com
*/

#ifndef ZE92EBAFE_95B1_4471_9200_5DB1F8851CB0
#define ZE92EBAFE_95B1_4471_9200_5DB1F8851CB0

#include <ratio>

namespace cc {
namespace detail {

template <char... Ts>
struct seq;

template <class Seq>
struct parse_sign
{
	static constexpr auto sign = intmax_t{1};
	using tail = Seq;
};

template <char... Ts>
struct parse_sign<seq<'+', Ts...>>
{
	static constexpr auto sign = intmax_t{1};
	using tail = seq<Ts...>;
};

template <char... Ts>
struct parse_sign<seq<'-', Ts...>>
{
	static constexpr auto sign = intmax_t{-1};
	using tail = seq<Ts...>;
};

template <bool BeforePoint, intmax_t Num, intmax_t Den, class Seq>
struct parse_frac;

template <bool BeforePoint, intmax_t Num, intmax_t Den>
struct parse_frac<BeforePoint, Num, Den, seq<>>
{
	static constexpr auto num = Num;
	static constexpr auto den = Den;
};

template <intmax_t Num, intmax_t Den, char... Ts>
struct parse_frac<true, Num, Den, seq<'.', Ts...>>
{
	using next = parse_frac<false, Num, Den, seq<Ts...>>;
	static constexpr auto num = next::num;
	static constexpr auto den = next::den;
};

template <intmax_t Num, intmax_t Den, char T, char... Ts>
struct parse_frac<true, Num, Den, seq<T, Ts...>>
{
	static_assert(
		T >= '0' && T <= '9',
		"Expected digit."
	);

	using next = parse_frac<true, 10 * Num + (T - '0'), Den, seq<Ts...>>;
	static constexpr auto num = next::num;
	static constexpr auto den = next::den;
};

template <intmax_t Num, intmax_t Den, char T, char... Ts>
struct parse_frac<false, Num, Den, seq<T, Ts...>>
{
	static_assert(
		T >= '0' && T <= '9',
		"Expected digit."
	);

	using next = parse_frac<false, 10 * Num + (T - '0'), 10 * Den, seq<Ts...>>;
	static constexpr auto num = next::num;
	static constexpr auto den = next::den;
};

}}

template <class Char, Char... Ts>
constexpr auto operator"" _f()
{
	using cc::detail::seq;
	using cc::detail::parse_sign;
	using cc::detail::parse_frac;

	using sign_parser = parse_sign<seq<Ts...>>;
	using tail = typename sign_parser::tail;
	using frac_parser = parse_frac<true, 0, 1, tail>;

	return std::ratio<
		sign_parser::sign * frac_parser::num,
		frac_parser::den
	>{};
}

#define cc_fixed(x) decltype(#x ## _f)

#endif
