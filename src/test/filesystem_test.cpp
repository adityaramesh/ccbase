/*
** File Name:	filesystem_test.cpp
** Author:	Aditya Ramesh
** Date:	08/27/2013
** Contact:	_@adityaramesh.com
*/

#include <ccbase/filesystem/directory_iterator.hpp>
#include <ccbase/format.hpp>
#include <ccbase/unit_test.hpp>

module("Test directory iteration.")
{
	cc::directory_iterator f{"/Users/aditya"};
	cc::directory_iterator l;

	while (f != l) {
		cc::println("File name: \"$0\". Is regular file: $1.",
			f->path(), f->type() == cc::file_type::regular);
		++f;
	}
}

suite("Tests the filesystem module.")
