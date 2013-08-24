/*
** File Name:	unit_test_test.cpp
** Author:	Aditya Ramesh
** Date:	07/15/2013
** Contact:	_@adityaramesh.com
*/

#include <ccbase/unit_test.hpp>

module("test 1", "This module always passes.")
{
	require(true);
}

module("test 2", "This module always fails.")
{
	require(false);
}

suite("This is an example test suite.")
