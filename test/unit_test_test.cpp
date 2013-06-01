/*
** File Name:	unit_test_test.cpp
** Author:	Aditya Ramesh
** Date:	12/18/2012
** Contact:	_@adityaramesh.com
*/

#include <ccbase/unit_test.hpp>

CC_BEGIN_MODULE(test1)
	CC_ASSERT(1);
CC_END_MODULE(test1)

CC_BEGIN_MODULE(test2)
	CC_ASSERT(0);
CC_END_MODULE(test2)

CC_BEGIN_SUITE(example)
	test1();
	test2();
CC_END_SUITE(example)
