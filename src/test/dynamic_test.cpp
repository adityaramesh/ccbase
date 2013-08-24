/*
** File Name:	dynamic_test.cpp
** Author:	Aditya Ramesh
** Date:	07/02/2013
** Contact:	_@adityaramesh.com
*/

#include <cstring>
#include <string>
#include <iostream>
#include <ccbase/dynamic.hpp>
#include <ccbase/unit_test.hpp>

module("test_retrieval", "Tests whether getting data works.")
{
	using signature = std::string(std::string, std::string);
	cc::image i{"./out/lib/test.lib", cc::lazy};
	auto f = cc::get_function<signature>("test", i).get();
	require(f("foo", "bar") == "foobar");
	auto& s = cc::get_data<std::string>("msg", i).get();
	require(s == "Original contents.");
}

module("test_mutation", "Tests whether module data is mutable.")
{
	cc::image i{"./out/lib/test.lib", cc::lazy};
	auto& s1 = cc::get_data<std::string>("msg", i).get();
	require(s1 == "Original contents.");
	s1 = "New contents.";

	auto& s2 = cc::get_data<std::string>("msg", i).get();
	require(s2 == "New contents.");
}

module("test_info", "Tests whether symbol address lookup works.")
{
	using signature = std::string(std::string, std::string);
	cc::image i{"./out/lib/test.lib", cc::lazy};
	auto f = cc::get_function<signature>("test", i).get();
	require(f("foo", "bar") == "foobar");
	auto& s = cc::get_data<std::string>("msg", i).get();
	require(s == "Original contents.");

	auto fi = cc::get_info(f).get();
	auto si = cc::get_info(s).get();
	require(std::strcmp(fi.name(), "test") == 0);
	require(std::strcmp(si.name(), "msg") == 0);
}

suite("Tests dynamic library loading.")
