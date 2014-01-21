/*
** File Name:	filesystem_test.cpp
** Author:	Aditya Ramesh
** Date:	08/27/2013
** Contact:	_@adityaramesh.com
*/

#include <cstring>
#include <unordered_set>
#include <ccbase/filesystem/range.hpp>
#include <ccbase/format.hpp>
#include <ccbase/unit_test.hpp>

module("Test directory iteration.")
{
	auto f = cc::directory_iterator{"dat/listing_1"};
	auto l = cc::directory_iterator{};

	while (f != l) {
		if (std::strcmp(f->name(), "a") == 0) {
			require(f->type() == cc::file_type::regular);
		}
		else if (std::strcmp(f->name(), "b") == 0) {
			require(f->type() == cc::file_type::symbolic_link);
		}
		else if (std::strcmp(f->name(), "c") == 0) {
			require(f->type() == cc::file_type::directory);
		}
		++f;
	}
}

module("Test glob matching.")
{
	auto f = cc::directory_iterator{"dat/listing_2"};
	auto l = cc::directory_iterator{};

	auto m1 = cc::glob_matcher{"abc123"};
	auto m2 = cc::glob_matcher{"abc123*"};
	auto m3 = cc::glob_matcher{"*a*1*a*"};
	auto m4 = cc::glob_matcher{"abc123???"};
	auto m5 = cc::glob_matcher{"ab[c1]23"};
	auto m6 = cc::glob_matcher{"*\\?*\\?*"};
	auto m7 = cc::glob_matcher{"*[\\[a]*[\\]a]*"};
	
	// Testing without special characters
	auto v1 = std::unordered_set<std::string>{};
	// Testing single wildcard
	auto v2 = std::unordered_set<std::string>{};
	// Testing multiple wildcards
	auto v3 = std::unordered_set<std::string>{};
	// Testing question mark
	auto v4 = std::unordered_set<std::string>{};
	// Testing grouping
	auto v5 = std::unordered_set<std::string>{};
	// Testing wildcard with escaping
	auto v6 = std::unordered_set<std::string>{};
	// Testing wildcard with grouping
	auto v7 = std::unordered_set<std::string>{};

	while (f != l) {
		if (m1(*f)) {
			v1.emplace(f->name());
		}
		if (m2(*f)) {
			v2.emplace(f->name());
		}
		if (m3(*f)) {
			v3.emplace(f->name());
		}
		if (m4(*f)) {
			v4.emplace(f->name());
		}
		if (m5(*f)) {
			v5.emplace(f->name());
		}
		if (m6(*f)) {
			v6.emplace(f->name());
		}
		if (m7(*f)) {
			v7.emplace(f->name());
		}
		++f;
	}

	require(v1.size() == 1 && v1.count("abc123"));
	require(v2.size() == 3 && v2.count("abc123") && v2.count("abc123123") && v2.count("abc123abc"));
	require(v3.size() == 1 && v3.count("abc123abc"));
	require(v4.size() == 2 && v4.count("abc123123") && v4.count("abc123abc"));
	require(v5.size() == 2 && v5.count("ab123") && v5.count("abc23"));
	require(v6.size() == 1 && v6.count("[?]*[?]"));
	require(v7.size() == 2 && v7.count("[?]*[?]") && v7.count("abc123abc"));
}

module("Test range functionality.")
{
	auto i = 0u;
	for (const auto& e : cc::list_files("dat/listing_2")) { ++i; }
	require(i == 8);

	i = 0u;
	for (const auto& e : cc::match_files("dat/listing_2/*")) { ++i; }
	require(i == 4);
}

suite("Tests the filesystem module.")
