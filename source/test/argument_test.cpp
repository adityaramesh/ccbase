/*
** File Name: attribute_test.cpp
** Author:    Aditya Ramesh
** Date:      08/06/2014
** Contact:   _@adityaramesh.com
*/

#include <ccbase/format/argument.hpp>
#include <ccbase/unit_test.hpp>

module("test general formatting")
{
	std::ostringstream dst{};
	std::ostringstream buf{};

	auto arg1 = cc::argument<char, std::char_traits<char>>{0};
	arg1.add_attribute("align");
	arg1[0].add_argument("L");
	arg1[0].add_argument("20");
	arg1[0].add_argument("'>'");

	auto arg2 = cc::argument<char, std::char_traits<char>>{0};
	arg2.add_attribute("align");
	arg2[0].add_argument("R");
	arg2[0].add_argument("20");
	arg2[0].add_argument("'>'");

	auto arg3 = cc::argument<char, std::char_traits<char>>{0};
	arg3.add_attribute("align");
	arg3[0].add_argument("C");
	arg3[0].add_argument("20");
	arg3[0].add_argument("'>'");

	auto arg4 = cc::argument<char, std::char_traits<char>>{0};
	arg4.add_attribute("quote");

	cc::apply(arg1, "test", dst, buf);
	require(dst.str() == "test>>>>>>>>>>>>>>>>");
	dst.str("");

	cc::apply(arg2, "test", dst, buf);
	require(dst.str() == ">>>>>>>>>>>>>>>>test");
	dst.str("");

	cc::apply(arg3, "test", dst, buf);
	require(dst.str() == ">>>>>>>>test>>>>>>>>");
	dst.str("");

	cc::apply(arg4, "test", dst, buf);
	require(dst.str() == "\"test\"");
	dst.str("");
}

module("test number formatting")
{
	std::ostringstream dst{};
	std::ostringstream buf{};

	auto arg1 = cc::argument<char, std::char_traits<char>>{0};
	arg1.add_attribute("sign");
	arg1[0].add_argument("always");

	auto arg2 = cc::argument<char, std::char_traits<char>>{0};
	arg2.add_attribute("sign");
	arg2[0].add_argument("space");

	auto arg3 = cc::argument<char, std::char_traits<char>>{0};
	arg3.add_attribute("money");
	arg3.add_attribute("loc");
	arg3[1].add_argument("en_US");

	auto arg4 = cc::argument<char, std::char_traits<char>>{0};
	arg4.add_attribute("money");
	arg4[0].add_argument("intl");
	arg4.add_attribute("loc");
	arg4[1].add_argument("en_US");

	cc::apply(arg1, 1, dst, buf);
	require(dst.str() == "+1");
	dst.str("");

	cc::apply(arg1, -1, dst, buf);
	require(dst.str() == "-1");
	dst.str("");

	cc::apply(arg2, 1, dst, buf);
	require(dst.str() == " 1");
	dst.str("");

	cc::apply(arg2, -1, dst, buf);
	require(dst.str() == "-1");
	dst.str("");

	cc::apply(arg3, 100, dst, buf);
	require(dst.str() == "$1.00");
	dst.str("");

	cc::apply(arg4, 100, dst, buf);
	require(dst.str() == "USD 1.00");
	dst.str("");
}

module("test integer formatting")
{
	/*
	** Note: I'm not going to bother to test the attributes that just add
	** manipulators, because their functionality is determined by the
	** implementation.
	*/

	std::ostringstream dst{};
	std::ostringstream buf{};

	auto arg1 = cc::argument<char, std::char_traits<char>>{0};
	arg1.add_attribute("bin");

	auto arg2 = cc::argument<char, std::char_traits<char>>{0};
	arg2.add_attribute("bool");

	auto arg3 = cc::argument<char, std::char_traits<char>>{0};
	arg3.add_attribute("char");

	auto arg4 = cc::argument<char, std::char_traits<char>>{0};
	arg4.add_attribute("num");

	auto arg5 = cc::argument<char, std::char_traits<char>>{0};
	arg5.add_attribute("bin");
	arg5.add_attribute("base");

	cc::apply(arg1, 'A', dst, buf);
	require(dst.str() == "01000001");
	dst.str("");

	cc::apply(arg2, 100, dst, buf);
	require(dst.str() == "true");
	dst.str("");

	cc::apply(arg3, 65, dst, buf);
	require(dst.str() == "A");
	dst.str("");

	cc::apply(arg4, 'A', dst, buf);
	require(dst.str() == "65");
	dst.str("");

	cc::apply(arg5, 'A', dst, buf);
	require(dst.str() == "0b01000001");
	dst.str("");
}

module("test float formatting")
{
	/*
	** Note: I'm not going to bother to test the attributes that just add
	** manipulators, because their functionality is determined by the
	** implementation.
	*/

	std::ostringstream dst{};
	std::ostringstream buf{};

	auto arg1 = cc::argument<char, std::char_traits<char>>{0};
	arg1.add_attribute("%");

	cc::apply(arg1, 0.5, dst, buf);
	require(dst.str() == "50.000000%");
	dst.str("");
}

module("test string formatting")
{
	std::ostringstream dst{};
	std::ostringstream buf{};

	auto arg1 = cc::argument<char, std::char_traits<char>>{0};
	arg1.add_attribute("upper");

	auto arg2 = cc::argument<char, std::char_traits<char>>{0};
	arg2.add_attribute("lower");

	cc::apply(arg1, "aAaA", dst, buf);
	require(dst.str() == "AAAA");
	dst.str("");

	cc::apply(arg2, "aAaA", dst, buf);
	require(dst.str() == "aaaa");
	dst.str("");
}

suite("Tests the argument class in the format module.")
