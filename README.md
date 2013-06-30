<!--
  ** File Name:	README.md
  ** Author:	Aditya Ramesh
  ** Date:	12/05/2012
  ** Contact:	_@adityaramesh.com
-->

# Introduction

This library is a collection of utilties that help to minimize the complexity of
code that needs to be written in order to accomplish some common tasks, without
compromising on efficiency or legibility. Examples of these common tasks include
printing and parsing data, or writing unit tests. This library requires a
C++11-conformant compiler.

# Planned updates

- Add support for references to `expected.hpp`.

# Documentation

## `format.hpp`

This very small header (125 line) header implements C#'s nify curly-brace string
formatting syntax. The functions in this header accept the format arguments as
variadic templates, and invoke `operator<<(ostream&, ...)` to print out each
argument specified in the format string. This means that you can print out
arbitrary types using this curly-brace syntax by defining `operator<<(ostream&,
...)` for them. The convenient syntax makes it a good replacement for many
common stream operations, including `std::cout` statements.

	// Old way:
	std::ostringstream ss;
	ss << "Error parsing header: expected " << a << " at line " << line <<
	", column " << col << ", but got " << b << " instead." << std::endl;
	throw parse_error{ss.str()};

	// New way:
	throw parse_error(cc::format("Error parsing header: expected {0} at "
	"line {1}, column {2}, but got {3} instead.", a, line, col, b));

## `platform.hpp`

This header allows you to identify various features of the host platform.
Because preprocessor macros are used to perform the detection, the header is not
guaranteed to successfully define all of the features in the list below.
However, the GNU/Linux, Mac OS, and Windows operating systems are supported,
along with the major C++ compilers and widely-used CPU architectures.

The header attempts to identify the following features of the host platform.
- The compiler.
- The processor architecture.
- The processor ABI.
- The operating system.
- The kernel.
- The integer byte order (the floating-point byte order can potentially be
  different from the integer byte order, but the header makes no attempt to
  identify the latter).

The header defines various feature macros, as well as the following structure:

	struct platform
	{
		static constexpr auto compiler = // ...
		static constexpr auto arch = // ...
		static constexpr auto abi = // ...
		static constexpr auto os = // ...
		static constexpr auto kernel = // ...
		static constexpr auto integer_byte_order = // ...
	};

Here is some example usage:

	// Use of enums, which is encouraged where possible.
	switch (cc::platform::os) {
	case cc::linux_distribution: // ...
	case cc::macos: // ...
	case cc::windows: // ...
	default: // Either none of the above or the identification failed.
	}

	/*
	** Identification failure can be checked for explicitly by checking
	** whether `cc::platform::os == cc::unknown`.
	*/

	// Where necessary, macros can be used.
	#if PLATFORM_OS == PLATFORM_OS_LINUX_DISTRIBUTION
		// ...
	#elif PLATFORM_OS == PLATFORM_OS_MACOS
		// ...
	#elif PLATFORM_OS == PLATFORM_OS_WINDOWS
		// ...
	#else
		// Either none of the above or the identification failed.
	#endif

	/*
	** Identification failure can be checked for explicitly by checking
	** whether `PLATFORM_OS` is defined. Comparisons involving `PLATFORM_OS`
	** will work even if `PLATFORM_OS` is not defined, because the standard
	** dictates that undefined macros evaluate to zero in such cases.
	*/

Enum values and macros are defined analogously for the other platform features
in the list above.

## `expected.hpp`

This is an implementation of `expected<T>` based on Alexandrescu's, with some
modifications. As stated by Alexandrescu, `expected<T>` is either `T`, or the
exception that prevented the creation of `T`. In a sense, expected types allow
you to use arbitrarily-rich error codes. If a method returns an expected type,
you can postpone the error-handling until you reach a place in your program
where it is convenient to do so. You can learn more about `expected<T>` by
watching [Alexandresu's
talk](http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C)
on systematic error handling.

This implementation of `expected<T>` defines a specialization for `void`. In the
future, specializations for `T&` and `const T&` will also be added. The
specializations for references are necessary, because unrestricted unions cannot
contain references as members. See [this blog
post](http://anto-nonco.blogspot.com/2013/03/extending-expected-to-deal-with.html)
for more information.

## `unit_test.hpp`

This header provides some utilities for very basic unit testing. Tests are
implemented as modules, and a set of related modules is gathered in a suite.
Each suite is tied to a particular file; there can only be one suite per file.
Here is an example of a file called `test.cpp` which uses the unit testing
functionality.

	#include <ccbase/unit_test.hpp>

	CC_BEGIN_MODULE(test1)
		CC_ASSERT(1);
	CC_END_MODULE(test1)

	CC_BEGIN_MODULE(test2)
		CC_ASSERT(0);
	CC_END_MODULE(test2)

	CC_BEGIN_SUITE(suite_name)
		test1();
		test2();
	CC_END_SUITE(suite_name)

By default, compiling `test.cpp` and running the resulting executable will
output the following.

	Failure in file "test.cpp", module "test2", at line 15: 0.

If `CC_UNIT_TEST_VERBOSE` is defined, then the output will be more descriptive.

	Entering suite example.
	Entering module test1.
	Success in file "test.cpp", module "test1", at line 11: 1.
	Exiting module "test1"; 1 of 1 assertions passed.
	Entering module test2.
	Failure in file "test.cpp", module "test2", at line 15: 0.
	Exiting module "test2"; 0 of 1 assertions passed.
	Exiting suite example.
