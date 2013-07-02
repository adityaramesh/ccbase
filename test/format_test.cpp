/*
** File Name:	format_test.cpp
** Author:	Aditya Ramesh
** Date:	12/05/2012
** Contact:	_@adityaramesh.com
*/

#include <ccbase/format.hpp>
#include <ccbase/unit_test.hpp>

CC_BEGIN_MODULE(test_repeated_arguments)
	auto s = cc::format("{0} {1} {0}", "A", 1);
	CC_ASSERT(s == "A 1 A");
CC_END_MODULE(test_repeated_arguments)

CC_BEGIN_MODULE(test_escape)
	auto s = cc::format("{{}}{{{{}}}}");
	CC_ASSERT(s == "{}{{}}");
CC_END_MODULE(test_escape)

CC_BEGIN_SUITE(format_test)
	test_repeated_arguments();
	test_escape();
CC_END_SUITE(format_test)
