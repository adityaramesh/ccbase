<!--
  ** File Name:	README.md
  ** Author:	Aditya Ramesh
  ** Date:	12/05/2012
  ** Contact:	_@adityaramesh.com
-->

# Overview

CCBase is a header-only C++11 library intended to make day-to-day tasks more
pleasant. It's licensed under the BSD Three-Clause License.

Installation information, along with usage examples and documentation, can be
found [here](http://adityaramesh.com/ccbase).

## Components

- `ccbase.format`: Elegant syntax for printing and formatting strings.
- `ccbase.platform`: Compile-time access to platform-specific information.
- `ccbase.unit_test`: Convenient and lightweight unit testing framework.
- `ccbase.error`: Utilities for systematic error handling.
- `ccbase.dynamic`: Dynamic library loading and symbol visibility control.
- `ccbase.filesystem`: Fast and convenient directory iteration.

The entirety of the public API resides in the `cc` namespace.

## Dependencies

- Required dependencies:
  - Boost 1.55.
  - A C++11-conforming compiler. The library has been tested on recent versions
  of ICC, GCC, and Clang.

- Optional dependencies:
  - Rake, for running the tests.
  - Sphinx and the Sphinx RTD Theme, for building the documentation.

## TODO

- Add argument to `match_files` and `list_files` that filters all but a set of
file types. To do this, make `file_type` a bitmask enum.
- Use `CC_ASSERT` instead of assert.
- Add support for standard library detection (e.g. libc++ vs libstdc++) to the
platform module.
- Document the utility module after sufficient usage.
- `match_files` with recursive directory enumeration.
- Tuple arithmetic.
