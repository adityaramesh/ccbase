/*
** File Name: formatter_test.cpp
** Author:    Aditya Ramesh
** Date:      08/06/2014
** Contact:   _@adityaramesh.com
*/

#include <ccbase/format/formatter.hpp>
#include <ccbase/unit_test.hpp>

module("test argument parsing")
{
	auto fmt1 = cc::formatter<1>("$");
	auto fmt2 = cc::formatter<2>("$ $");
	auto fmt3 = cc::formatter<1>("${}");
	auto fmt4 = cc::formatter<1>("${ }");
	auto fmt5 = cc::formatter<2>("${}$");
	auto fmt6 = cc::formatter<2>("${}${}");
	auto fmt7 = cc::formatter<1>("$$${}");
	auto fmt8 = cc::formatter<1>("${{");
	auto fmt9 = cc::formatter<1>("$}");
	auto fmt10 = cc::formatter<1>("$1");
	auto fmt11 = cc::formatter<1>("$1{}");
	auto fmt12 = cc::formatter<1>("$1{{");
	auto fmt13 = cc::formatter<1>("$1}");
}

module("test attribute parsing")
{
	auto fmt1 = cc::formatter<1>("${hex}");
	auto fmt2 = cc::formatter<1>("${hex, base}");
	auto fmt3 = cc::formatter<1>("${hex, base(upper)}");
	auto fmt4 = cc::formatter<1>("${hex, base(upper), align(R,20,'}')}");
	auto fmt5 = cc::formatter<1>("${hex,base}");
	auto fmt6 = cc::formatter<1>("${hex,base(upper)}");
	auto fmt7 = cc::formatter<1>("${hex,base(upper),align(R,20,'}')}");
}

module("test formatting")
{
	std::ostringstream os{};

	/*
	** `argument_test.hpp` already tests the correctness of the formatting,
	** so we will just make sure that a complex attribute gets parsed
	** correctly.
	*/
	auto fmt1 = cc::formatter<1>("${hex, base(upper), align(R, 20), quote}");
	fmt1.apply(os, 1);
	require(os.str() == "               \"0X1\"");
}

suite("Tests the formatter class in the format module.")
