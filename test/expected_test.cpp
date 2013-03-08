/*
** File Name:	expected_test.cpp
** Author:	Aditya Ramesh
** Date:	03/08/2013
** Contact:	_@adityaramesh.com
*/

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <ccbase/expected.hpp>

static int foo()
{
	throw std::invalid_argument{"poo"};
}

static cc::expected<int> bar(int a)
{
	if (a) return 1;
	return std::invalid_argument{"bar"};
}

int main()
{
	//auto r = cc::attempt([] { return foo(); });
	//r.get();
	bar(0).get();
	return EXIT_SUCCESS;
}
