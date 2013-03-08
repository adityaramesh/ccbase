/*
** File Name:	unit_test_test.cpp
** Author:	Aditya Ramesh
** Date:	12/18/2012
** Contact:	_@adityaramesh.com
*/

#include <ccbase/unit_test.hpp>

XU_BEGIN_MODULE(test1)
	XU_ASSERT(1);
XU_END_MODULE(test1)

XU_BEGIN_MODULE(test2)
	XU_ASSERT(0);
XU_END_MODULE(test2)

XU_BEGIN_SUITE(example)
	test1();
	test2();
XU_END_SUITE(example)
