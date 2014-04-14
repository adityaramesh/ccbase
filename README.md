<!--
  ** File Name:	README.md
  ** Author:	Aditya Ramesh
  ** Date:	12/05/2012
  ** Contact:	_@adityaramesh.com
-->

# Introduction

`ccbase` is a header-only collection of lightweight modules that augment the
standard library or provide abstractions over platform-specific functionality
for Linux and OS X.

The `ccbase` library consists of the following components:

- `ccbase.format`: Elegant syntax for printing and formatting strings.
- `ccbase.platform`: Compile-time access to platform-specific information.
- `ccbase.unit_test`: Convenient and lightweight unit testing framework.
- `ccbase.error`: Utilities for systematic error handling.
- `ccbase.dynamic`: Dynamic library loading and symbol visibility control.
- `ccbase.filesystem`: Fast and convenient directory iteration.

The following additional components are currently under development:

- `ccbase.tuple`: Printing and operators for `std::tuple`.

You can read the examples and documentation [here](documentation.md).

# Upcoming Features

- `match_files` with recursive directory enumeration.
- Tuple arithmetic.

# License

This work is licensed under the [BSD Three-Clause License](LICENSE.md).
Basically, you can use this library for both free and commercial applications
without any attribution, provided that:
  - Redistributions of the source must contain the [license file](LICENSE.md).
  - You do not use my name to promote products derived from this one without
  prior written permission.

# Prerequisites

`ccbase` depends on Boost (namely, Boost.Range and Boost.Iterator). You should
have Boost installed on your system before attempting to install `ccbase`.

# Installation

Click the "Download ZIP" button on the right-hand side of the screen, and
extract the `ccbase_master` archive. At this point, you could then move the
`ccbase_master/ccbase` directory directly to your desired include path, but I
would suggest first building and running the unit tests, to ensure that
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

# Development Notes

- The include files are placed within the `inc` directory to guard against
  executables that have the same name as standard header files. (Thanks to
  guepier from Reddit for the suggestion.)
- Each module in `ccbase` has its own directory, along with a top-level header
  file that includes all of the header files in the module.
- The `src/ref` directory contains platform-specific reference programs that are
  written to help understand how various functions work before they are
  abstracted away behind an interface. These were especially useful when
  developing the `dynamic` and `filesystem` modules.
- Lesson: avoid using constexpr structures alongside macros. Although the syntax
  may be cleaner in certain cases, it is not worth the development nightmare to
  maintain both variants simultaneously.
