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

## Planned updates

- Generate HTML documentation from code.
- Add support for compiler version detection.
- Add support for kernel version detection.
- Test `platform.hpp` on Cygwin.
- Add example code for `expected.hpp`.

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

This class is based on Andrei Alexandrescu's implementation of `expected<T>`,
which he discussed in a talk at C++ Next 2012 called "Systematic Error
Handling". The video and slides of the talk (which contain his code) are
available [here][error_handling]. Support was later added for `expected<void>`,
so that methods that return void can still take advantage of the this idiom.
Finally, support for references was added, so that objects of type
`expected<T&>` and `expected<const T&>` can now be created. The fact that
generalized unions cannot contain references was alluded to in [this blog
post][extending_expected], and the approach taken to rectify the problem is
adapted from the one given in the blog post.

[error_handling]: http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C "Alexandrescu's Talk on Systematic Error Handling"
[extending_expected] : http://anto-nonco.blogspot.com/2013/03/extending-expected-to-deal-with.html "Extending `expected<T>` to Deal with References"

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
