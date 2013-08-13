<!--
  ** File Name:	README.md
  ** Author:	Aditya Ramesh
  ** Date:	12/05/2012
  ** Contact:	_@adityaramesh.com
-->

# Introduction

This library is a collection of utilities that help to minimize the complexity
of code that needs to be written in order to accomplish some common tasks,
without compromising on efficiency or legibility. Examples of these common tasks
include printing and parsing data, loading dynamic libraries, or writing unit
tests. This library requires a C++11-conformant compiler.

## Planned updates

- Tuple arithmetic.
- Support for typesetting paragraphs with a given character width. 
- Generate HTML documentation from code.
- Structure the documentation so that each file has an associated tutorial page.
  The summary of each header given in this page should be taken from the summary
  provided in the tutorial page for the header.

# Installation

Click the "Download ZIP" button on the right-hand side of the screen, and
extract the `ccbase_master` archive. At this point, you could then move the
`ccbase_master/ccbase` directory directly to your desired include path, but I
would suggest first building and running the unit tests, to ensure that
everything is working correctly on your system.

First, ensure that the `CXX` environment variable is set to your desired
C++11-conformant compiler. The compilation flags set in the Rakefile should work
for both `g++` and `clang++` running on OS X or Linux. If you are using another
compiler or think that the compilation flags may need to be revised for your
system, please review and edit the Rakefile accordingly. Then, run the following
commands:

	rake
	rake tests

If `rake tests` produces no output, then everything worked well, and you can
proceed to move the `ccbase_master/ccbase` directory to your include path.
Otherwise, some tests must have failed on your system. I apologize for this, and
would appreciate it if you file a bug report with the output of the unit tests
and your platform details (in particular, your OS and compiler, along with their
corresponding versions) either via Github or by email at `_@adityaramesh.com`.
Thanks!

# Documentation

## `format.hpp`

This very small header (125 line) header implements C#'s nifty curly-brace
string formatting syntax. The functions in this header accept the format
arguments as variadic templates, and invoke `operator<<(std::ostream&, ...)` to
print out each argument specified in the format string. This means that you can
print out arbitrary types using this curly-brace syntax by defining
`operator<<(std::ostream&, ...)` for them. The convenient syntax makes it a good
replacement for many common stream operations, including `std::cout` statements.

	// Old way:
	std::ostringstream ss;
	ss << "Error parsing header: expected " << a << " at line " << line <<
	", column " << col << ", but got " << b << " instead." << std::endl;
	throw parse_error{ss.str()};

	// New way:
	throw parse_error(cc::format("Error parsing header: expected $0 at "
	"line $1, column $2, but got $3 instead.", a, line, col, b));

## `platform/dynamic.hpp`

This header allows you to load functions and data from dynamic libraries using
convenient C++11 syntax. Suppose that you have a library called `test.dll`,
which defines two symbols of interest: `msg`, a `const std::string` and `test`,
a function with the signature `std::string(std::string, std::string)`. Assuming
that both symbols have C linkage, then you could load them as follows:

	cc::image i{"test.dll", cc::lazy};
	using signature = std::string(std::string, std::string);
	auto f = cc::get_function<signature>("test", i).get();
	auto& s = cc::get_data<std::string>("msg", i).get();

Both methods return `expected` objects, which either contain the objects loaded
from the symbols, or the exceptions that prevented them from being loaded.
Notice that the `get_data` method returns a reference to the object at the
symbol's address, so mutating the reference will also change the data at the
symbol's address in memory.

Information about the symbols can be queried using the `get_info` method, which
returns an `expected<symbol_information>` structure. The `symbol_information`
structure defines the following methods:
	
	// Returns the path to the loaded image.
	const char* path();
	// Returns the base address of the image.
	const void* base_address();
	// Returns the name of the symbol.
	const char* name();
	// Returns the address of the symbol.
	const void* address();

With the variables `f` and `s` as defined in the previous code sample, the
`get_info` method is used as follows:

	auto fi = cc::get_info(f).get();
	auto si = cc::get_info(s).get();

## `platform/visibility.hpp`

This header defines macros that can be used to set symbol visibility when
compiling shared libraries in a cross-platform manner. To this end, the
following macros are defined:

	// Used for public symbols in a header for a shared library that is to
	// be implicitly linked into the final executable.
	IMPORT_SYMBOL
	// Used for public symbols in source code that is to be compiled into a
	// shared library.
	EXPORT_SYMBOL
	// Used to hide symbols in source code that is to be compiled into a
	// shared library.
	HIDDEN_SYMBOL

Often times, it is the case that the same header file is used both by the source
code that is compiled into the shared library, and by the source code that links
to the shared library. In the first case, public symbols should be prefixed by
`EXPORT_SYMBOL`; in the second case, public symbols should be prefixed by
`IMPORT_SYMBOL`. In both cases, private symbols that are not included in the
shared library should be prefixed by `HIDDEN_SYMBOL`. The following macros are
provided to make this task easier:

	PUBLIC_SYMBOL
	PRIVATE_SYMBOL

`PUBLIC_SYMBOL` expands to `IMPORT_SYMBOL` if `CCBASE_IMPORT_SYMBOLS` is
defined, or `EXPORT_SYMBOL` if `CCBASE_EXPORT_SYMBOLS` is defined. If neither of
the two macros is defined, then `PUBLIC_SYMBOL` expands to nothing.
`PRIVATE_SYMBOL` expands to `HIDDEN_SYMBOL` if either of the two macros is
defined, and nothing otherwise.

## `platform.hpp`

This header allows you to identify various features of the host platform.
Because preprocessor macros are used to perform the detection, the header is not
guaranteed to successfully define all of the features in the list below.
However, the GNU/Linux, Mac OS, and Windows operating systems are supported,
along with the major C++ compilers and several CPU architectures.

The header attempts to identify the following features of the host platform.
- The compiler.
- The compiler version.
- The processor architecture.
- The processor ABI.
- The operating system.
- The kernel.
- The integer byte order (the floating-point byte order can potentially be
  different from the integer byte order, but the header makes no attempt to
  identify the latter).
- The platform newline character.

The header defines various feature macros, as well as the following structure
which provides the same information as the macros in a more organized fashion.
If you do not need to use the preprocessor, then it is recommend that you use
the `platform` struct instead of the macros.

	struct platform
	{
		static constexpr auto arch = // See `platform/architecture.hpp`.
		static constexpr auto cc = // See `platform/compiler.hpp`.
		static constexpr auto os = // See `platform/operating_system.hpp.`
	};

Here is some example usage:

	// Use of enums, which is encouraged where possible.

	if (cc::platform::os == cc::operating_system::linux_distribution) {
		// ...
	}
	else if (cc::platform::os == cc::operating_system::os_x) {
		// ...
	}
	else if (cc::platform::os == cc::operating_system::windows) {
		// ...
	}
	else {
		// ...
	}

	/*
	** Identification failure can be checked for explicitly by checking
	** whether `cc::platform::os == cc::operating_system::unknown`.
	*/

	// Where necessary, macros can be used.
	#if PLATFORM_OS == PLATFORM_OS_LINUX_DISTRIBUTION
		// ...
	#elif PLATFORM_OS == PLATFORM_OS_OS_X
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

Macros are defined analogously for the other platform features in the list
above.

## `utility/expected.hpp`

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
[extending_expected]: http://anto-nonco.blogspot.com/2013/03/extending-expected-to-deal-with.html "Extending `expected<T>` to Deal with References"

## `unit_test.hpp`

This header provides some utilities for basic unit testing. Tests are
implemented as modules, and a set of related modules is gathered in a suite.
Here is an example of a file called `test.cpp` which uses the unit testing
functionality.

	#include <ccbase/unit_test.hpp>

	module("test_1", "This module always passes.")
	{
		require(1);
	}

	module("test_2", "This module always fails.")
	{
		require(0);
	}

	// This declaration is required, and should appear at the end of the
	// test file.
	suite("This is an example test suite.")

By default, compiling `test.cpp` and running the resulting executable will
output the following.

	Summary for module "test_1": 1 of 1 assertions passed.
	Summary for module "test_2": 0 of 1 assertions passed.
	Summary for suite "test": 1 of 2 assertions passed.

If you wish to see more information about the assertions in the modules, then
you can control the level of the verbosity using the `-v` flag. For example,
running the executable with the option `-v medium` displays the following.

	Summary for module "test_1": 1 of 1 assertions passed.
	Failure in module "test_2", line 17: "require(false)".
	Summary for module "test_2": 0 of 1 assertions passed.
	Summary for suite "test": 1 of 2 assertions passed.

Medium-level logging causes the line number and source code for failed
assertions within each module to be printed along with the summary statistics.
For more options, run the executable with the `--help` flag.
