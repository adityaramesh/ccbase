/*
** File Name: format_argument_test.cpp
** Author:    Aditya Ramesh
** Date:      08/06/2014
** Contact:   _@adityaramesh.com
*/

#include <ccbase/format/format_argument.hpp>
#include <ccbase/unit_test.hpp>

using format_argument = cc::basic_format_argument<char, std::char_traits<char>>;

module("test general formatting")
{
	std::ostringstream dst{};
	std::ostringstream buf{};

	auto arg1 = format_argument{0};
	arg1.add_attribute("align");
	arg1[0].add_argument("L");
	arg1[0].add_argument("20");
	arg1[0].add_argument("'>'");

	auto arg2 = format_argument{0};
	arg2.add_attribute("align");
	arg2[0].add_argument("R");
	arg2[0].add_argument("20");
	arg2[0].add_argument("'>'");

	auto arg3 = format_argument{0};
	arg3.add_attribute("align");
	arg3[0].add_argument("C");
	arg3[0].add_argument("20");
	arg3[0].add_argument("'>'");

	auto arg4 = format_argument{0};
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

	auto arg1 = format_argument{0};
	arg1.add_attribute("sign");
	arg1[0].add_argument("always");

	auto arg2 = format_argument{0};
	arg2.add_attribute("sign");
	arg2[0].add_argument("space");

	//auto arg3 = format_argument{0};
	//arg3.add_attribute("money");
	//arg3.add_attribute("loc");
	//arg3[1].add_argument("en_US");

	//auto arg4 = format_argument{0};
	//arg4.add_attribute("money");
	//arg4[0].add_argument("intl");
	//arg4.add_attribute("loc");
	//arg4[1].add_argument("en_US");

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

	//cc::apply(arg3, 100, dst, buf);
	//require(dst.str() == "$1.00");
	//dst.str("");

	//cc::apply(arg4, 100, dst, buf);
	//require(dst.str() == "USD 1.00");
	//dst.str("");
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

	auto arg1 = format_argument{0};
	arg1.add_attribute("bin");

	auto arg2 = format_argument{0};
	arg2.add_attribute("bool");

	auto arg3 = format_argument{0};
	arg3.add_attribute("char");

	auto arg4 = format_argument{0};
	arg4.add_attribute("num");

	auto arg5 = format_argument{0};
	arg5.add_attribute("bin");
	arg5.add_attribute("base");

	auto arg6 = format_argument{0};
	arg6.add_attribute("data");

	auto arg7 = format_argument{0};
	arg7.add_attribute("data");
	arg7[0].add_argument("dec");

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

	cc::apply(arg6, 10, dst, buf);
	require(dst.str() == "10 B");
	dst.str("");

	cc::apply(arg6, 10485760, dst, buf);
	require(dst.str() == "10 MiB");
	dst.str("");

	cc::apply(arg7, 10, dst, buf);
	require(dst.str() == "10 B");
	dst.str("");

	cc::apply(arg7, 10000000, dst, buf);
	require(dst.str() == "10 MB");
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

	auto arg1 = format_argument{0};
	arg1.add_attribute("%");

	cc::apply(arg1, 0.5, dst, buf);
	require(dst.str() == "50.000000%");
	dst.str("");
}

module("test string formatting")
{
	std::ostringstream dst{};
	std::ostringstream buf{};

	auto arg1 = format_argument{0};
	arg1.add_attribute("upper");

	auto arg2 = format_argument{0};
	arg2.add_attribute("lower");

	cc::apply(arg1, "aAaA", dst, buf);
	require(dst.str() == "AAAA");
	dst.str("");

	cc::apply(arg2, "aAaA", dst, buf);
	require(dst.str() == "aaaa");
	dst.str("");
}

suite("Tests the attribute list class in the format module.")
