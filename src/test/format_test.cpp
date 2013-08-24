/*
** File Name:	format_test.cpp
** Author:	Aditya Ramesh
** Date:	12/05/2012
** Contact:	_@adityaramesh.com
*/

#include <iostream>
#include <ccbase/format.hpp>
#include <ccbase/unit_test.hpp>

module("test_repeated_arguments")
{
	auto s = cc::format("$0 $1 $0", "A", 1);
	require(s == "A 1 A");
}

module("test_escape")
{
	auto s = cc::format("$$$$ $$$$ $$ $$");
	require(s == "$$ $$ $ $");
}

suite("Tests the format header.")
