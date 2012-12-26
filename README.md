<!--
  ** File Name:	README.md
  ** Author:	Aditya Ramesh
  ** Date:	12/05/2012
  ** Contact:	_@adityaramesh.com
-->

# Introduction

This library is a collection of utilties (distinct from the standard `utility`
library) which provides a collection of useful header files that make life
easier. A description of each header file is provieded below.

# `format.hpp`

This very small header (125 line) header implements FastFormat's nifty
formatting syntax, without the monolithic frameworks that come with FastFormat,
and its dependency, STLSoft. The functions in this header accept the format
arguments as variadic templates, and invoke `operator<<(ostream&, ...)` to print
out each argument specified in the format string. This header requires a
C++11-conformant compiler.

# `unit_test.hpp`

This header provides some utilties for very basic unit testing. Tests are
implemented as modules, and a set of related modules is gathered in a suite.
Each suite is tied to a particular file; there can only be one suite per file.
