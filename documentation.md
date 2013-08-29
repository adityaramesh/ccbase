<!--
  ** File Name:	documentation.md
  ** Author:	Aditya Ramesh
  ** Date:	08/24/2013
  ** Contact:	_@adityaramesh.com
-->

# Documentation

## `ccbase.format`

Suppose that you wish to throw an exception in an IO parsing routine, and that
the message reported by the exception should contain some useful diagnostic
information. Using the Standard Library, your implementation would likely look
something like this:

	std::ostringstream ss;
	ss << "Error parsing header: expected " << a << " at line " << line <<
	", column " << col << ", but got " << b << " instead." << std::endl;
	throw parse_error{ss.str()};

Using `ccbase/format.hpp`, it would look like this:

	throw parse_error(cc::format("Error parsing header: expected $0 at "
	"line $1, column $2, but got $3 instead.", a, line, col, b));

The formatting functions provided by `ccbase.format` are listed in the table
below. Each of them is a lightweight wrapper that forwards each variadic
template argument to the destination output stream using `operator<<`.

<table>
	<tr>
		<th>Purpose</th>
		<th>Function</th>
		<th>Example</th>
	</tr>
	<tr>
		<td>Print to std::cout.</td>
		<td>cc::print[ln](const T*, const Us&...)</td>
		<td>cc::println("Hello, $0.", name);</td>
	</tr>
	<tr>
		<td>Print to std::cerr.</td>
		<td>cc::err[ln](const T*, const Us&...)</td>
		<td>cc::errln("Hello, $0.", name);</td>
	</tr>
	<tr>
		<td>Format arguments into std::string.</td>
		<td>cc::format[ln](const T*, const Us&...)</td>
		<td>See motivating example above.</td>
	</tr>
	<tr>
		<td>Print to std::cout and exit with success code.</td>
		<td>cc::finish(const T*, const Us&...)</td>
		<td>cc::finish("Done.");</td>
	</tr>
	<tr>
		<td>Print to std::cerr and exit with failure code.</td>
		<td>cc::fail(const T*, const Us&...)</td>
		<td>cc::fail("Could not open file $0.", fn);</td>
	</tr>
</table>

## `ccbase.platform`

This module allows you to identify various features of the host platform.
Because preprocessor macros are used to perform the detection, the header is not
guaranteed to successfully define all of the features listed below.  However,
the GNU/Linux, Mac OS, and Windows operating systems are supported, along with
the major C++ compilers and several CPU architectures.

This module attempts to identify the following features of the host platform.
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
- The platform directory separator.
- The maximum permissible file and path name lengths.

### Usage

The macros defined by the preprocessor are listed in the table below. Where `*`
is used to indicate the value of a macro, the name of the macro is to be
substituted.

<table>
	<tr>
		<th>Macro</th>
		<th>Description</th>
		<th>Possible Values</th>
	</tr>
	<tr>
		<td>PLATFORM_ARCH</td>
		<td>Platform CPU architecture.</td>
		<td>*_ARM, *_ITANIUM, *_X86, *_UNKNOWN</td>
	</tr>
	<tr>
		<td>PLATFORM_COMPILER</td>
		<td>Platform compiler.</td>
		<td>
			*_CLANG, *_COMEAU, *_GCC, *_ICC, *_MSVC,
			*_UNKNOWN
		</td>
	</tr>
	<tr>
		<td>PLATFORM_COMPILER_VERSION</td>
		<td>Platform compiler version.</td>
		<td>Compare using CC_COMPILER_VERSION(v, r, p).</td>
	</tr>
	<tr>
		<td>PLATFORM_COMPILER_MAJOR_VERSION</td>
		<td>Platform compiler major version.</td>
		<td>Integer.</td>
	</tr>
	<tr>
		<td>PLATFORM_COMPILER_MINOR_VERSION</td>
		<td>Platform compiler minor version.</td>
		<td>Integer.</td>
	</tr>
	<tr>
		<td>PLATFORM_COMPILER_PATCH_LEVEL</td>
		<td>Platform compiler patch level.</td>
		<td>Integer.</td>
	</tr>
	<tr>
		<td>PLATFORM_INTEGER_BYTE_ORDER</td>
		<td>Platform byte order.</td>
		<td>
			(* = PLATFORM_BYTE_ORDER) *_LITTLE, *_BIG,
			*_LITTLE_WORD, *_UNKNOWN
		</td>
	</tr>
	<tr>
		<td>PLATFORM_KERNEL</td>
		<td>Platform byte order.</td>
		<td>*_LINUX, *_WINDOWS_NT, *_XNU, *_UNKNOWN</td>
	</tr>
	<tr>
		<td>PLATFORM_OS</td>
		<td>Platform operating system.</td>
		<td>*_LINUX, *_WINDOWS, *_OS_X, *_UNKNOWN</td>
	</tr>
	<tr>
		<td>PLATFORM_WORD_SIZE</td>
		<td>Platform word size.</td>
		<td>32, 64, *_UNKNOWN</td>
	</tr>
	<tr>
		<td>PLATFORM_NEWLINE</td>
		<td>Platform newline.</td>
		<td>"\n", "\r\n"</td>
	</tr>
	<tr>
		<td>PLATFORM_NEWLINE_LENGTH</td>
		<td>Platform newline.</td>
		<td>Integer.</td>
	</tr>
	<tr>
		<td>PLATFORM_DIRECTORY_SEPARATOR</td>
		<td>Platform directory separator.</td>
		<td>Character literal.</td>
	</tr>
	<tr>
		<td>PLATFORM_MAX_FILENAME_LENGTH</td>
		<td>Maximum permissible file name length.</td>
		<td>Integer.</td>
	</tr>
	<tr>
		<td>PLATFORM_MAX_PATHNAME_LENGTH</td>
		<td>Maximum permissible path name length.</td>
		<td>Integer.</td>
	</tr>
</table>

## `ccbase.dynamic`

### Loading Dynamic Libraries

Suppose that you have a library called `test.dll`, which defines two symbols of
interest: `msg`, a `const std::string` and `test`, a function with the signature
`std::string(std::string, std::string)`. Assuming that both symbols have C
linkage, then you could load them as follows:

	using signature = std::string(std::string, std::string);
	auto i  = cc::image{"test.dll", cc::lazy};
	auto f  = cc::get_function<signature>("test", i).get();
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

### Controlling Symbol Visibility

The following macros can be used to set symbol visibility when compiling shared
libraries.

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

## `ccbase.error`

Currently, this module contains an implementation of `expected<T>` based on the
one Andrei Alexandrescu discusses in his talk at C++ Next 2012 called
"Systematic Error Handling". The video and slides of the talk (which contain his
code) are available [here][error_handling]. This implementation in `ccbase` is
extended so that it also works for `void` and reference types.

The fact that generalized unions cannot contain references was alluded to in
[this blog post][extending_expected], and the approach taken to rectify the
problem is adapted from the one given in the blog post.

[error_handling]:
http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C
"Alexandrescu's Talk on Systematic Error Handling"

[extending_expected]:
http://anto-nonco.blogspot.com/2013/03/extending-expected-to-deal-with.html
"Extending `expected<T>` to Deal with References"

## `ccbase.unit_test`

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
