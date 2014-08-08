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
	cc::formatter<1> fmt1{"$"};
	cc::formatter<2> fmt2{"$ $"};
	cc::formatter<1> fmt3{"${}"};
	cc::formatter<1> fmt4{"${ }"};
	cc::formatter<2> fmt5{"${}$"};
	cc::formatter<2> fmt6{"${}${}"};
	cc::formatter<1> fmt7{"$$${}"};
	cc::formatter<1> fmt8{"${{"};
	cc::formatter<1> fmt9{"$}"};
	cc::formatter<1> fmt10{"$1"};
	cc::formatter<1> fmt11{"$1{}"};
	cc::formatter<1> fmt12{"$1{{"};
	cc::formatter<1> fmt13{"$1}"};
}

module("test attribute parsing")
{
	cc::formatter<1> fmt1{"${hex}"};
	cc::formatter<1> fmt2{"${hex, base}"};
	cc::formatter<1> fmt3{"${hex, base(upper)}"};
	cc::formatter<1> fmt4{"${hex, base(upper), align(R,20,'}')}"};
	cc::formatter<1> fmt5{"${hex,base}"};
	cc::formatter<1> fmt6{"${hex,base(upper)}"};
	cc::formatter<1> fmt7{"${hex,base(upper),align(R,20,'}')}"};
}

module("test formatting")
{
	std::ostringstream os{};

	/*
	** `argument_test.hpp` already tests the correctness of the formatting,
	** so we will just make sure that a complex attribute gets parsed
	** correctly.
	*/
	cc::formatter<1> fmt1{"${hex, base(upper), align(R, 20), quote}"};
	apply(fmt1, os, 1);
	require(os.str() == "               \"0X1\"");
	os.str("");

	cc::formatter<0> fmt2{"$${{$${{"};
	apply(fmt2, os);
	require(os.str() == "${{${{");
	os.str("");

	cc::formatter<1> fmt3{"${{"};
	apply(fmt3, os, "");
	require(os.str() == "{");
	os.str("");
}

suite("Tests the formatter class in the format module.")
