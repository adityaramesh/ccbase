/*
** File Name:	expected_test.cpp
** Author:	Aditya Ramesh
** Date:	03/08/2013
** Contact:	_@adityaramesh.com
*/

#include <exception>
#include <ccbase/error.hpp>
#include <ccbase/unit_test.hpp>

struct copyable
{
	copyable() {}
	copyable(const copyable&)            = default;
	copyable(copyable&&)                 = default;
	copyable& operator=(const copyable&) = default;
	copyable& operator=(copyable&&)      = default;
};

struct not_assignable
{
	not_assignable() {}
	not_assignable(const not_assignable&)            = default;
	not_assignable(not_assignable&&)                 = default;
	not_assignable& operator=(const not_assignable&) = delete;
	not_assignable& operator=(not_assignable&&)      = delete;
};

struct not_copyable
{
	not_copyable() {}
	not_copyable(const not_copyable&)            = delete;
	not_copyable(not_copyable&&)                 = delete;
	not_copyable& operator=(const not_copyable&) = delete;
	not_copyable& operator=(not_copyable&&)      = delete;
};

module("test default construction")
{
	{
		cc::expected<copyable> e1{};
		cc::expected<const copyable> e2{};
		cc::expected<copyable*> e3{};
		cc::expected<const copyable*> e4{};

		e1.dismiss();
		e2.dismiss();
		e3.dismiss();
		e4.dismiss();
	}

	{
		cc::expected<not_assignable> e1{};
		cc::expected<const not_assignable> e2{};
		cc::expected<not_assignable*> e3{};
		cc::expected<const not_assignable*> e4{};

		e1.dismiss();
		e2.dismiss();
		e3.dismiss();
		e4.dismiss();
	}

	{
		cc::expected<void> e1{};
		e1.dismiss();
	}
}

module("test copy construction from value")
{
	{
		copyable c{};
		cc::expected<copyable> e1{c};
		cc::expected<const copyable> e2{c};
		cc::expected<copyable&> e3{c};
		cc::expected<const copyable&> e4{c};
		cc::expected<copyable*> e5{&c};
		cc::expected<const copyable*> e6{&c};

		e1.dismiss();
		e2.dismiss();
		e3.dismiss();
		e4.dismiss();
		e5.dismiss();
		e6.dismiss();
	}

	{
		not_assignable c{};
		cc::expected<not_assignable> e1{c};
		cc::expected<const not_assignable> e2{c};
		cc::expected<not_assignable&> e3{c};
		cc::expected<const not_assignable&> e4{c};
		cc::expected<not_assignable*> e5{&c};
		cc::expected<const not_assignable*> e6{&c};

		e1.dismiss();
		e2.dismiss();
		e3.dismiss();
		e4.dismiss();
		e5.dismiss();
		e6.dismiss();
	}

	{
		not_copyable c{};
		cc::expected<not_copyable&> e1{c};
		cc::expected<const not_copyable&> e2{c};
		cc::expected<not_copyable*> e3{&c};
		cc::expected<const not_copyable*> e4{&c};

		e1.dismiss();
		e2.dismiss();
		e3.dismiss();
		e4.dismiss();
	}
}

module("test copy construction from valid expected")
{
	{
		cc::expected<not_assignable> e1{};
		auto e2 = e1;
		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<const not_assignable> e1{};
		auto e2 = e1;
		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<not_assignable*> e1{};
		auto e2 = e1;
		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<const not_assignable*> e1{};
		auto e2 = e1;
		e1.dismiss();
		e2.dismiss();
	}
	{
		not_assignable x{};
		cc::expected<not_assignable&> e1{x};
		auto e2 = e1;
		e1.dismiss();
		e2.dismiss();
	}
	{
		not_assignable x{};
		cc::expected<const not_assignable&> e1{x};
		auto e2 = e1;
		e1.dismiss();
		e2.dismiss();
	}

	{
		cc::expected<void> e1{};
		auto e2 = e1;
		e1.dismiss();
		e2.dismiss();
	}
}

module("test move construction from valid expected")
{
	{
		cc::expected<not_assignable> e1{};
		auto e2 = std::move(e1);
		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<const not_assignable> e1{};
		auto e2 = std::move(e1);
		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<not_assignable*> e1{};
		auto e2 = std::move(e1);
		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<const not_assignable*> e1{};
		auto e2 = std::move(e1);
		e1.dismiss();
		e2.dismiss();
	}
	{
		not_assignable x{};
		cc::expected<not_assignable&> e1{x};
		auto e2 = std::move(e1);
		e1.dismiss();
		e2.dismiss();
	}
	{
		not_assignable x{};
		cc::expected<const not_assignable&> e1{x};
		auto e2 = std::move(e1);
		e1.dismiss();
		e2.dismiss();
	}

	{
		cc::expected<void> e1{};
		auto e2 = std::move(e1);
		e1.dismiss();
		e2.dismiss();
	}
}

module("test construction in invalid state")
{
	{
		auto e = std::runtime_error{"error"};
		auto ep = std::make_exception_ptr(e);
		cc::expected<int> e1{e};
		cc::expected<int> e2{ep};
		cc::expected<int> e3{std::move(ep)};

		e1.dismiss();
		e2.dismiss();
		e3.dismiss();
	}
}

module("test copy assignment to valid expected")
{
	{
		cc::expected<not_assignable> e1{};
		cc::expected<not_assignable> e2{};
		e1.dismiss();
		e1 = e2;

		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<const not_assignable> e1{};
		cc::expected<const not_assignable> e2{};
		e1.dismiss();
		e1 = e2;

		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<not_assignable*> e1{};
		cc::expected<not_assignable*> e2{};
		e1.dismiss();
		e1 = e2;

		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<const not_assignable*> e1{};
		cc::expected<const not_assignable*> e2{};
		e1.dismiss();
		e1 = e2;

		e1.dismiss();
		e2.dismiss();
	}
	{
		not_assignable x{};
		cc::expected<not_assignable&> e1{x};
		cc::expected<not_assignable&> e2{x};
		e1.dismiss();
		e1 = e2;

		e1.dismiss();
		e2.dismiss();
	}
	{
		not_assignable x{};
		cc::expected<const not_assignable&> e1{x};
		cc::expected<const not_assignable&> e2{x};
		e1.dismiss();
		e1 = e2;

		e1.dismiss();
		e2.dismiss();
	}
}

module("test move assignment to valid expected")
{
	{
		cc::expected<not_assignable> e1{};
		cc::expected<not_assignable> e2{};
		e1.dismiss();
		e1 = std::move(e2);

		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<const not_assignable> e1{};
		cc::expected<const not_assignable> e2{};
		e1.dismiss();
		e1 = std::move(e2);

		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<not_assignable*> e1{};
		cc::expected<not_assignable*> e2{};
		e1.dismiss();
		e1 = std::move(e2);

		e1.dismiss();
		e2.dismiss();
	}
	{
		cc::expected<const not_assignable*> e1{};
		cc::expected<const not_assignable*> e2{};
		e1.dismiss();
		e1 = std::move(e2);

		e1.dismiss();
		e2.dismiss();
	}
	{
		not_assignable x{};
		cc::expected<not_assignable&> e1{x};
		cc::expected<not_assignable&> e2{x};
		e1.dismiss();
		e1 = std::move(e2);

		e1.dismiss();
		e2.dismiss();
	}
	{
		not_assignable x{};
		cc::expected<const not_assignable&> e1{x};
		cc::expected<const not_assignable&> e2{x};
		e1.dismiss();
		e1 = std::move(e2);

		e1.dismiss();
		e2.dismiss();
	}
}

module("test assignment to reference")
{
	{
		not_copyable x{};
		cc::expected<not_copyable&> e1{x};
		e1.dismiss();
		e1 = x;
	}
	{
		not_copyable x{};
		cc::expected<const not_copyable&> e1{x};
		e1.dismiss();
		e1 = x;
	}
}

module("test assignment to invalid state")
{
	{
		auto e = std::runtime_error{"error"};
		auto ep = std::make_exception_ptr(e);
		cc::expected<int> e1{};
		e1.dismiss();

		e1 = ep;
		e1.dismiss();
		e1 = std::move(ep);
		e1.dismiss();
	}
}

module("test getters")
{
	{
		cc::expected<int> e1{1};
		e1.dismiss();
		e1.value();
		std::move(e1).value();
	}
	{
		auto i = 0;
		cc::expected<int&> e1{i};
		e1.dismiss();
		e1.value();
		std::move(e1).value();
	}
	{
		cc::expected<int> e1{std::runtime_error{"test"}};
		e1.dismiss();
		e1.exception();
		std::move(e1).exception();
	}
}

suite("Tests expected header.")
