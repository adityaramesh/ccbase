/*
** File Name: metaparse_test.cpp
** Author:    Aditya Ramesh
** Date:      01/11/2015
** Contact:   _@adityaramesh.com
*/

#include <type_traits>
#include <ccbase/unit_test.hpp>
#include <ccbase/mpl/parse_natural.hpp>
#include <ccbase/mpl/parse_ratio.hpp>
#include <ccbase/mpl/skip_whitespace.hpp>
#include <ccbase/mpl/parse_wsv.hpp>
#include <ccbase/utility/ratio_literal.hpp>

module("test parse natural")
{
	using s1 = std::integer_sequence<char, '0', '0', '0'>;
	using s2 = std::integer_sequence<char, '1', '0', '0'>;
	using s3 = std::integer_sequence<char, '0', '0', '1'>;
	using s4 = std::integer_sequence<char, '0', '1', '0'>;
	using s5 = std::integer_sequence<char, '1', '2', '3'>;

	static_assert(cc::parse_natural<s1>::type::value == 0, "");
	static_assert(cc::parse_natural<s2>::type::value == 100, "");
	static_assert(cc::parse_natural<s3>::type::value == 1, "");
	static_assert(cc::parse_natural<s4>::type::value == 10, "");
	static_assert(cc::parse_natural<s5>::type::value == 123, "");
}

module("test parse ratio")
{
	using s1 = std::integer_sequence<char, '1', '.', '0'>;
	using s2 = std::integer_sequence<char, '0', '1', '.', '0'>;
	using s3 = std::integer_sequence<char, '0', '1', '.', '0', '0'>;
	using s4 = std::integer_sequence<char, '0', '.', '0', '1', '0'>;
	using s5 = std::integer_sequence<char, '.', '0', '1', '0'>;
	using s6 = std::integer_sequence<char, '+', '.', '0', '1', '0'>;
	using s7 = std::integer_sequence<char, '-', '.', '0', '1', '0'>;

	require((cc::cast<double, cc_ratio(0.1)> == 0.1));
	require((cc::cast<double, cc_ratio(.1)> == 0.1));
	require((cc::cast<double, cc_ratio(1)> == 1.0));
	require((cc::cast<double, cc_ratio(1.)> == 1.0));
	require((cc::cast<double, cc_ratio(1.0)> == 1.0));
	require((cc::cast<double, cc_ratio(1.00)> == 1.0));
	require((cc::cast<double, cc_ratio(01.0)> == 1.0));

	require((cc::cast<double, cc_ratio(+0.1)> == 0.1));
	require((cc::cast<double, cc_ratio(+.1)> == 0.1));
	require((cc::cast<double, cc_ratio(+1)> == 1.0));
	require((cc::cast<double, cc_ratio(+1.)> == 1.0));
	require((cc::cast<double, cc_ratio(+1.0)> == 1.0));
	require((cc::cast<double, cc_ratio(+1.00)> == 1.0));
	require((cc::cast<double, cc_ratio(+01.0)> == 1.0));

	require((cc::cast<double, cc_ratio(-0.1)> == -0.1));
	require((cc::cast<double, cc_ratio(-.1)> == -0.1));
	require((cc::cast<double, cc_ratio(-1)> == -1.0));
	require((cc::cast<double, cc_ratio(-1.)> == -1.0));
	require((cc::cast<double, cc_ratio(-1.0)> == -1.0));
	require((cc::cast<double, cc_ratio(-1.00)> == -1.0));
	require((cc::cast<double, cc_ratio(-01.0)> == -1.0));
}

module("test skip whitespace")
{
	using s = std::integer_sequence<char, ' ', '\t', ' ', 'a', 'b', 'c', ' '>;
	using t = std::integer_sequence<char, 'a', 'b', 'c', ' '>;
	using u = cc::skip_whitespace<s>;
	static_assert(std::is_same<t, u>::value, "");
}

module("test parse wsv")
{
	using s = std::integer_sequence<char,
	      ' ', ' ', '0', ' ', '1', '\n',
	      ' ', ' ', '1', '2', '3', ' ', '4', '5', '6', ' ', ' ', '\n',
	      ' ', ' ', '\n',
	      '\n',
	      '0', ' ', '1', ' ', '2'
	>;
	using expected = cc::seq<
		cc::type_seq<std::integer_sequence<uintmax_t, 0, 1>>,
		cc::type_seq<std::integer_sequence<uintmax_t, 123, 456>>,
		cc::type_seq<std::integer_sequence<uintmax_t>>,
		cc::type_seq<std::integer_sequence<uintmax_t>>,
		cc::type_seq<std::integer_sequence<uintmax_t, 0, 1, 2>>
	>;
	using result = cc::parse_wsv<uintmax_t, cc::parse_natural, '\n', s>;
	static_assert(std::is_same<expected, result>::value, "");
}

suite("metaparse test");
