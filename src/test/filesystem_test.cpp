/*
** File Name:	filesystem_test.cpp
** Author:	Aditya Ramesh
** Date:	08/27/2013
** Contact:	_@adityaramesh.com
*/

#include <cstring>
#include <ccbase/filesystem/directory_iterator.hpp>
#include <ccbase/format.hpp>
#include <ccbase/unit_test.hpp>

module("Test directory iteration.")
{
	cc::directory_iterator f{"dat/listing"};
	cc::directory_iterator l;

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

suite("Tests the filesystem module.")
