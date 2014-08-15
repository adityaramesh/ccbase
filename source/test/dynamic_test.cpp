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

module("test_retrieval", "Tests whether loading data works.")
{
	using signature = int(const std::string&, const std::string&);
	auto img = cc::image{"./out/libraries/test.lib", cc::binding_mode::lazy};

	auto f = *cc::load<signature>("test", img);
	auto& s = *cc::load<std::string>("msg", img);
	require(f("1", "00") == 100);
	require(s == "Original contents.");
}

module("test_mutation", "Tests whether module data is mutable.")
{
	auto img = cc::image{"./out/libraries/test.lib", cc::binding_mode::lazy};

	auto& s1 = *cc::load<std::string>("msg", img);
	require(s1 == "Original contents.");
	s1 = "New contents.";

	auto& s2 = *cc::load<std::string>("msg", img);
	require(s2 == "New contents.");
}

module("test_info", "Tests whether symbol address lookup works.")
{
	using signature = int(const std::string&, const std::string&);
	auto img = cc::image{"./out/libraries/test.lib", cc::binding_mode::lazy};

	auto f = *cc::load<signature>("test", img);
	auto& s = *cc::load<std::string>("msg", img);
	require(f("1", "00") == 100);
	require(s == "Original contents.");

	auto fi = *cc::query(f);
	auto si = *cc::query(s);
	require(fi.name() == "test");
	require(si.name() == "msg");
}

suite("Tests dynamic library loading.")
