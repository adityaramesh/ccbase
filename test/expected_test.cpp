/*
** File Name:	expected_test.cpp
** Author:	Aditya Ramesh
** Date:	03/08/2013
** Contact:	_@adityaramesh.com
*/

#include <exception>
#include <ccbase/expected.hpp>
#include <ccbase/unit_test.hpp>

module("test_valid_constructors")
{
	int a{1};
	cc::expected<int> e1{a};
	cc::expected<int> e2{std::move(a)};
	require(e1.valid());
	require(e2.valid());

	int b{1};
	cc::expected<int&> e3{b};
	require(e3.valid());
	require(e3.get() == 1);

	e3.get() = 2;
	require(e3.valid());
	require(e3.get() == 2);
}

module("test_invalid_constructors")
{
	std::exception e;
	std::exception_ptr ep{std::move(std::make_exception_ptr(e))};

	cc::expected<int> e1{};
	cc::expected<int> e2{e};
	cc::expected<int> e3{ep};

	require(!e1.valid());
	require(!e2.valid());
	require(!e3.valid());
}

module("test_swap")
{
	int a{1};
	int b{2};
	cc::expected<int> e1{a};
	cc::expected<int> e2{b};
	require(e1.valid());
	require(e2.valid());
	require(e1.get() == 1);
	require(e2.get() == 2);

	e1.swap(e2);
	require(e1.valid());
	require(e2.valid());
	require(e1.get() == 2);
	require(e2.get() == 1);

	cc::expected<int> e3{std::exception{}};
	cc::expected<int> e4{a};
	require(!e3.valid());
	require(e4.valid());
	require(e4.get() == 1);

	e3.swap(e4);
	require(e3.valid());
	require(!e4.valid());
	require(e3.get() == 1);

	int c{1};
	int d{2};
	cc::expected<int&> e5{c};
	cc::expected<int&> e6{d};
	require(e5.valid());
	require(e6.valid());
	require(e5.get() == 1);
	require(e6.get() == 2);

	e5.swap(e6);
	require(e5.valid());
	require(e6.valid());
	require(e5.get() == 2);
	require(e6.get() == 1);

	cc::expected<int&> e7{std::exception{}};
	cc::expected<int&> e8{c};
	require(!e7.valid());
	require(e8.valid());
	require(e8.get() == 1);

	e7.swap(e8);
	require(!e8.valid());
	require(e7.valid());
	require(e7.get() == 1);
}

suite("Tests expected header.")
