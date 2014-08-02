<!--
  ** File Name:	README.md
  ** Author:	Aditya Ramesh
  ** Date:	12/05/2012
  ** Contact:	_@adityaramesh.com
-->

# Introduction

CCBase is a header-only C++11 library intended to make day-to-day tasks more
pleasant. It's licensed under the BSD Three-Clause License.

Installation information, along with usage examples and documentation, can be
found [here](http://adityaramesh.com/ccbase).

# Components

- `ccbase.format`: Elegant syntax for printing and formatting strings.
- `ccbase.platform`: Compile-time access to platform-specific information.
- `ccbase.unit_test`: Convenient and lightweight unit testing framework.
- `ccbase.error`: Utilities for systematic error handling.
- `ccbase.dynamic`: Dynamic library loading and symbol visibility control.
- `ccbase.filesystem`: Fast and convenient directory iteration.

The entirety of the public API resides in the `cc` namespace.

# Dependencies

- Required dependencies:
  - Boost 1.55.
  - A C++11-conforming compiler. The library has been tested on recent versions
  of ICC, GCC, and Clang.

- Optional dependencies:
  - Rake, for running the tests.
  - Sphinx and the Sphinx RTD Theme, for building the documentation.

# TODO

- Adapt documentation to Sphinx.
- Refactor installation information.
- Document the `utility` module.

- Use `CC_ASSERT` instead of assert.
- Tuple arithmetic.
- `match_files` with recursive directory enumeration.

- Add attributes for formatting.
  - E.g. `cc::println("Object ID: ${hex, align(left, 20)}.");`
  - Allow use of numbers to refer to previously-formatted objects.
  - Allow support for user-defined attributes?
  - Supported attributes:
    - General attributes:
      - Adjustment/centering/fill characters
    - Integral type attributes:
      - binary
      - octal
      - hex
      - bool
    - Floating-point type attributes:
      - precision
      - fixed
      - scientific
    - String attributes:
      - quote
      - uppercase
      - lowercase

# Installation

Click the "Download ZIP" button on the right-hand side of the screen, and
extract the `ccbase_master` archive. At this point, you could then move the
`ccbase_master/ccbase/include` directory directly to your desired include path,
but I would suggest first building and running the unit tests, to ensure that
everything is working correctly on your system.

First, ensure that the `CXX` environment variable is set to your desired
C++11-conformant compiler, and that `BOOST_INCLUDE_PATH` is set appropriately.
The compilation flags set in the Rakefile should work for both `g++` and
`clang++` running on OS X or Linux. If you are using another compiler or think
that the compilation flags may need to be revised for your system, please review
and edit the Rakefile accordingly. Then, run the following commands:

	rake
	rake check

If `rake check` produces no output, then everything worked well, and you can
proceed to move the `ccbase_master/ccbase` directory to your include path.
Otherwise, some tests must have failed on your system. I apologize for this, and
would appreciate it if you file a bug report with the output of the unit tests
and your platform details (in particular, your OS and compiler, along with their
corresponding versions) either via Github or by email at `_@adityaramesh.com`.
Thanks!
