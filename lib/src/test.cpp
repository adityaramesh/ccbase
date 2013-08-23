/*
** File Name:	test.cpp
** Author:	Aditya Ramesh
** Date:	07/02/2013
** Contact:	_@adityaramesh.com
**
** This file is used to generate a dynamic library that is itself used in
** various unit tests.
*/

#include <string>
#include <ccbase/dynamic.hpp>

extern "C" EXPORT_SYMBOL
const std::string msg{"Original contents."};

extern "C" EXPORT_SYMBOL
std::string test(std::string a, std::string b)
{
	return a + b;
}
