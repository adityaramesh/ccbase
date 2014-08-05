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

- Document the utility module after sufficient usage.
- Use `CC_ASSERT` instead of assert.
- Tuple arithmetic.
- `match_files` with recursive directory enumeration.

## Attribute TODO

- TODO: Since the manipulator syntax works for all types, and not just
arithmetic types, we can also use it on tuples. Show this in the documentation.

- Make the printing functions return the formatter that was used in the process
of printing the output.

- Implementations of integer -> integer attributes (do this at the next highest
level).
- Parsing attribute arguments.

  - Use `copyfmt` to save and restore the stream state before and after each
  format argument with attributes that add manipulators. (This saves the locale,
  as well.)
  - http://stackoverflow.com/questions/4217704/roll-back-or-undo-any-manipulators-applied-to-a-stream-without-knowing-what-th

  - To apply a type to string attribute to the stringstream instead of a string
  argument, do the following:
    - Save the contents of the stringstream using `.str()`.
    - Clear the contents of the stringstream using `.str("")`.
    - Pass the saved contents of the stringstream to the `apply_type_to_string`
    function.
