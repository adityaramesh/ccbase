/*
** File Name:	dynamic_test.cpp
** Author:	Aditya Ramesh
** Date:	07/02/2013
** Contact:	_@adityaramesh.com
*/

#include <cstring>
#include <string>
#include <ccbase/dynamic.hpp>
#include <ccbase/unit_test.hpp>

CC_BEGIN_MODULE(test_retrieval)
	using signature = std::string(std::string, std::string);
	cc::image i{"./lib/out/test.dll", cc::lazy};
	auto f = cc::get_function<signature>("test", i).get();
	CC_ASSERT(f("foo", "bar") == "foobar");
	auto& s = cc::get_data<std::string>("msg", i).get();
	CC_ASSERT(s == "Original contents.");
CC_END_MODULE(test_retrieval)

CC_BEGIN_MODULE(test_mutation)
	cc::image i{"./lib/out/test.dll", cc::lazy};
	auto& s1 = cc::get_data<std::string>("msg", i).get();
	CC_ASSERT(s1 == "Original contents.");
	s1 = "New contents.";

	auto& s2 = cc::get_data<std::string>("msg", i).get();
	CC_ASSERT(s2 == "New contents.");
CC_END_MODULE(test_mutation)

CC_BEGIN_MODULE(test_info)
	using signature = std::string(std::string, std::string);
	cc::image i{"./lib/out/test.dll", cc::lazy};
	auto f = cc::get_function<signature>("test", i).get();
	CC_ASSERT(f("foo", "bar") == "foobar");
	auto& s = cc::get_data<std::string>("msg", i).get();
	CC_ASSERT(s == "Original contents.");

	auto fi = cc::get_info(f).get();
	auto si = cc::get_info(s).get();
	CC_ASSERT(std::strcmp(fi.name(), "test") == 0);
	CC_ASSERT(std::strcmp(si.name(), "msg") == 0);
CC_END_MODULE(test_info)

CC_BEGIN_SUITE(dynamic_test)
	test_retrieval();
	test_mutation();
	test_info();
CC_END_SUITE(dynamic_test)
