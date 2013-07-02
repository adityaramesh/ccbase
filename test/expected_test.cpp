/*
** File Name:	expected_test.cpp
** Author:	Aditya Ramesh
** Date:	03/08/2013
** Contact:	_@adityaramesh.com
*/

#include <exception>
#include <ccbase/expected.hpp>
#include <ccbase/unit_test.hpp>

CC_BEGIN_MODULE(test_valid_constructors)
	int a{1};
	cc::expected<int> e1{a};
	cc::expected<int> e2{std::move(a)};
	CC_ASSERT(e1.valid());
	CC_ASSERT(e2.valid());

	int b{1};
	cc::expected<int&> e3{b};
	CC_ASSERT(e3.valid());
	CC_ASSERT(e3.get() == 1);

	e3.get() = 2;
	CC_ASSERT(e3.valid());
	CC_ASSERT(e3.get() == 2);
CC_END_MODULE(test_valid_constructors)

CC_BEGIN_MODULE(test_invalid_constructors)
	std::exception e;
	std::exception_ptr ep{std::move(std::make_exception_ptr(e))};

	cc::expected<int> e1{};
	cc::expected<int> e2{e};
	cc::expected<int> e3{ep};

	CC_ASSERT(!e1.valid());
	CC_ASSERT(!e2.valid());
	CC_ASSERT(!e3.valid());
CC_END_MODULE(test_invalid_constructors)

CC_BEGIN_MODULE(test_swap)
	int a{1};
	int b{2};
	cc::expected<int> e1{a};
	cc::expected<int> e2{b};
	CC_ASSERT(e1.valid());
	CC_ASSERT(e2.valid());
	CC_ASSERT(e1.get() == 1);
	CC_ASSERT(e2.get() == 2);

	e1.swap(e2);
	CC_ASSERT(e1.valid());
	CC_ASSERT(e2.valid());
	CC_ASSERT(e1.get() == 2);
	CC_ASSERT(e2.get() == 1);

	cc::expected<int> e3{std::exception{}};
	cc::expected<int> e4{a};
	CC_ASSERT(!e3.valid());
	CC_ASSERT(e4.valid());
	CC_ASSERT(e4.get() == 1);

	e3.swap(e4);
	CC_ASSERT(e3.valid());
	CC_ASSERT(!e4.valid());
	CC_ASSERT(e3.get() == 1);

	int c{1};
	int d{2};
	cc::expected<int&> e5{c};
	cc::expected<int&> e6{d};
	CC_ASSERT(e5.valid());
	CC_ASSERT(e6.valid());
	CC_ASSERT(e5.get() == 1);
	CC_ASSERT(e6.get() == 2);

	e5.swap(e6);
	CC_ASSERT(e5.valid());
	CC_ASSERT(e6.valid());
	CC_ASSERT(e5.get() == 2);
	CC_ASSERT(e6.get() == 1);

	cc::expected<int&> e7{std::exception{}};
	cc::expected<int&> e8{c};
	CC_ASSERT(!e7.valid());
	CC_ASSERT(e8.valid());
	CC_ASSERT(e8.get() == 1);

	e7.swap(e8);
	CC_ASSERT(!e8.valid());
	CC_ASSERT(e7.valid());
	CC_ASSERT(e7.get() == 1);
CC_END_MODULE(test_get)

CC_BEGIN_SUITE(expected_test)
	test_valid_constructors();
	test_invalid_constructors();
	test_swap();
CC_END_SUITE(expected_test)
