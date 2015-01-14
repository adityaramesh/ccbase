/*
** File Name: parse_ratio.hpp
** Author:    Aditya Ramesh
** Date:      01/14/2015
** Contact:   _@adityaramesh.com
*/

#ifndef ZCFBD15C7_0219_4F4E_8DF4_A360B9E52877
#define ZCFBD15C7_0219_4F4E_8DF4_A360B9E52877

#include <ccbase/mpl/sequence_operations.hpp>

namespace cc {

template <class Seq>
struct parse_sign_helper
{
	static constexpr auto sign = intmax_t{1};
	using tail = Seq;
};

template <char... Ts>
struct parse_sign_helper<std::integer_sequence<char, '+', Ts...>>
{
	static constexpr auto sign = intmax_t{1};
	using tail = std::integer_sequence<char, Ts...>;
};

template <char... Ts>
struct parse_sign_helper<std::integer_sequence<char, '-', Ts...>>
{
	static constexpr auto sign = intmax_t{-1};
	using tail = std::integer_sequence<char, Ts...>;
};

template <bool BeforePoint, intmax_t Num, intmax_t Den, class Seq>
struct parse_frac_helper;

template <bool BeforePoint, intmax_t Num, intmax_t Den>
struct parse_frac_helper<BeforePoint, Num, Den, std::integer_sequence<char>>
{
	static constexpr auto num = Num;
	static constexpr auto den = Den;
};

template <intmax_t Num, intmax_t Den, char... Ts>
struct parse_frac_helper<true, Num, Den, std::integer_sequence<char, '.', Ts...>>
{
	using next = parse_frac_helper<
		false, Num, Den,
		std::integer_sequence<char, Ts...>
	>;
	static constexpr auto num = next::num;
	static constexpr auto den = next::den;
};

template <intmax_t Num, intmax_t Den, char T, char... Ts>
struct parse_frac_helper<true, Num, Den, std::integer_sequence<char, T, Ts...>>
{
	static_assert(
		T >= '0' && T <= '9',
		"Expected digit."
	);

	using next = parse_frac_helper<
		true, 10 * Num + (T - '0'), Den,
		std::integer_sequence<char, Ts...>
	>;
	static constexpr auto num = next::num;
	static constexpr auto den = next::den;
};

template <intmax_t Num, intmax_t Den, char T, char... Ts>
struct parse_frac_helper<false, Num, Den, std::integer_sequence<char, T, Ts...>>
{
	static_assert(
		T >= '0' && T <= '9',
		"Expected digit."
	);

	using next = parse_frac_helper<
		false, 10 * Num + (T - '0'), 10 * Den,
		std::integer_sequence<char, Ts...>
	>;
	static constexpr auto num = next::num;
	static constexpr auto den = next::den;
};

template <class Seq>
struct parse_ratio
{
	using valid_initial_chars = std::integer_sequence<
		char, '+', '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	>;

	static_assert(
		Seq::size() >= 1,
		"Sequence is empty."
	);

	static_assert(
		find<at<0, type_seq<Seq>>, type_seq<valid_initial_chars>> != no_match,
		"Expected digit, decimal point, or sign."
	);

	using sign_parser = parse_sign_helper<Seq>;
	using tail = typename sign_parser::tail;
	using frac_parser = parse_frac_helper<true, 0, 1, tail>;
	using type = std::ratio<
		sign_parser::sign * frac_parser::num,
		frac_parser::den
	>;
};

}

#endif
