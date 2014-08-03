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

- Adapt documentation to Sphinx.
- Refactor installation information.
- Document the `utility` module.

- Use `CC_ASSERT` instead of assert.
- Tuple arithmetic.
- `match_files` with recursive directory enumeration.

- Add attributes for formatting.
  - E.g. `cc::println("Object ID: ${hex, align(L, 20)}.");`
  - Accept `boost::string_ref` as parameter.
  - Allow use of numbers to refer to previously-formatted objects.
  - Allow support for user-defined attributes?
  - Supported attributes:
    - General attributes:
      - Adjustment/centering/fill characters `align(L|R|C, padding, fill)`
    - Integral type attributes:
      - binary `bin`
      - decimal `dec`
      - octal `oct`
      - hex `hex`
      - bool `bool`
      - character `char`
      - number `num`
      - To add prefix for binary, octal, and hex: `prefix`
      - Locale-dependent digit separator: `sep`
      - Money: `money`
    - Floating-point type attributes:
      - precision `prec(N)`
      - fixed `fixed`
      - scientific `sci`
      - percent `%`
      - sign `sign(always|space)`
    - String attributes:
      - quote `quote`
      - uppercase `upper`
      - lowercase `lower`
