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

# `format.hpp`

This very small header (125 line) header implements C#'s nify curly-brace string
formatting syntax. The functions in this header accept the format arguments as
variadic templates, and invoke `operator<<(ostream&, ...)` to print out each
argument specified in the format string. This means that you can print out
arbitrary types using this curly-brace syntax by defining `operator<<(ostream&,
...)` for them. The convenient syntax makes it a good replacement for many
common stream operations, including `std::cout` statements.

## Example

	// Old way:
	std::ostringstream ss;
	ss << "Error parsing header: expected " << a << " at line " << line <<
	", column " << col << ", but got " << b << " instead." << std::endl;
	throw parse_error{ss.str()};

	// New way:
	throw parse_error(cc::format("Error parsing header: expected {0} at "
	"line {1}, column {2}, but got {3} instead.", a, line, col, b));

# `order.hpp`

This header enables cross-platform (currently OS X and GNU/Linux only)
endian-detection. If you include the header on an unsupported platform, a
compile-time error is raised.

## Example

	switch (cc::order) {
	case cc::byte_order::little_endian:
		/* Little-endian code. */
		break;
	case cc::byte_order::pdp_endian:
		/* PDP-endian code. */
		break;
	case cc::byte_order::big_endian:
		/* Big-endian code. */
		break;
	}

# `expected.hpp`

This is an implementation of `expected<T>` based on Alexandrescu's, with some
modifications. As stated by Alexanderscu, `expected<T>` is either `T`, or the
exception that prevented the creation of `T`. In a sense, expected types allow
you to use arbitrarily-rich error codes. If a method returns an expected type,
you can postpone the error-handling until you reach a place in your program
where it is convenient to do so. You can learn more about `expected<T>` by
watching [Alexandresu's
talk](http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C)
on systematic error handling.

# `unit_test.hpp`

This header provides some utilties for very basic unit testing. Tests are
implemented as modules, and a set of related modules is gathered in a suite.
Each suite is tied to a particular file; there can only be one suite per file.
