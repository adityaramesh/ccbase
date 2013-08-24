<!--
  ** File Name:	README.md
  ** Author:	Aditya Ramesh
  ** Date:	12/05/2012
  ** Contact:	_@adityaramesh.com
-->

# Introduction

`ccbase` is a header-only collection of lightweight modules that augment the
standard library or provide abstractions over platform-specific functionality.

The `ccbase` library consists of the following components:

- `ccbase.format`: Elegant syntax for printing and formatting strings.
- `ccbase.platform`: Compile-time access to platform-specific information.
- `ccbase.unit_test`: Convenient and lightweight unit testing framework.
- `ccbase.error`: Utilities for systematic error handling.
- `ccbase.dynamic`: Dynamic library loading and symbol visibility control.

The following additional components are currently under development:

- `ccbase.tuple`: Printing and operators for `std::tuple`.

## Planned updates

- Consolidate `str_const.hpp` and `variadic_size.hpp` into the directories of
  the respective projects, and remove the `preprocessor` and `mpl` directories.
- Tuple arithmetic.
- Support for typesetting paragraphs with a given character width. 

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
	rake check

If `rake check` produces no output, then everything worked well, and you can
proceed to move the `ccbase_master/ccbase` directory to your include path.
Otherwise, some tests must have failed on your system. I apologize for this, and
would appreciate it if you file a bug report with the output of the unit tests
and your platform details (in particular, your OS and compiler, along with their
corresponding versions) either via Github or by email at `_@adityaramesh.com`.
Thanks!

# Documentation
