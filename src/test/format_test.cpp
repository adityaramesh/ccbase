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
	auto s1 = cc::format("$ $ $", "A", 1, "A");
	auto s2 = cc::format("$$$", "A", 1, "A");
	require(s1 == "A 1 A");
	require(s2 == "A1A");
}

module("test_escape")
{
	auto s1 = cc::format("{$}{$} {$}{$} {$} {$}");
	auto s2 = cc::format("{{{{$}}}} {{}}", 0);
	require(s1 == "$$ $$ $ $");
	require(s2 == "{{0}} {}");
}

suite("Tests the format header.")
