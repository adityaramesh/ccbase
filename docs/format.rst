.. _ccbase-format-module:
.. default-domain:: cpp

.. |string| replace::
   :class:`std::string`

.. |string_ref| replace:
   :class:`boost::string_ref`

The Format Module
=================

To use this module, include ``ccbase/format.hpp``.

Overview
--------

This module provides clean syntax for printing and formatting strings. Since
this module is built on top of IOStreams, the function ``std::ostream&
operator<<(std::ostream&, T)`` must be defined for a given type *T* to be
printable.

Examples
--------

::

        cc::println("Hello, world!");
        // Prints "Hello, world!" to stdout.

        cc::println("File name: ${quote}, size: ${data}, version: $.",
                "test.txt", 1024, 1);
        // Prints "File name: "test.txt", size: 1 KiB, version: 1." to stdout.

        cc::writeln(log, "Ten-fold CV error: ${%, prec(2)}.", 0.12345);
        // Write "Ten-fold CV error: 12.35%." to the log.

        cc::println("${money, loc(en_US)} == ${money, loc(ja_JP)}.",
                10000, 10210.15);
        // Prints "$100.00 == ¥10,210." to stdout.

        cc::println("${money(intl), loc(en_US)} == ${money(intl), loc(ja_JP)}.",
                10000, 10210.15);
        // Prints "USD 100.00 == JPY 10,210." to stdout.

        cc::errln("${align(C, 50, '*'), upper}", "System rebooting now!");
        // Prints "**************SYSTEM REBOOTING NOW!***************" to
        // stderr.

        auto msg = cc::format("{Name: ${quote}, ID: ${hex, base}}",
                "test", 256);
        // Creates a string whose contents are "{Name: "test", ID: 0x100}".

Syntax
------

Each function in this module takes a *format string* as an argument. This format
string can either be a string literal, a |string| or a |string_ref|. The format
string can contain zero or more *arguments;* each argument can contain zero or
more *attributes;* and each *attribute* can itself consist of zero or more
*attribute arguments.*

Arguments are indicated by the ``$`` character. If an argument accepts
attributes, then the attributes must be provided in a brace-enclosed
comma-separated list that occurs immediately after the ``$``. For example, the
format string ``"${hex, base}"`` contains a single argument, and this argument
contains two attributes.

Some attributes have optional or required arguments. Attribute arguments must be
provided in a parenthesis-enclosed comma-separated list that occurs after the
attribute name, similar to the C syntax for function invocation. For example,
the format string ``${align(C, 50, '*')}`` has a single argument with a single
attribute. This attribute contains three attribute arguments.

Attributes
----------

Not all attributes can be used with all types. In general, an attribute performs
exactly one of the following functions:

1. Adds manipulators to the destination stream [*]_.
2. Converts a numeric type to another numeric type.
3. Converts a numeric type to a string [*]_.
4. Converts any type to a string.
5. Converts a string to another string.

.. [*] The format state of the destination output stream is saved and restored
   before and after the application of each argument that modifies the stream's
   format state.

.. [*] Strings in this context are taken to be character literals,
   :class:`std::string`s, or :class:`boost::string_ref`s.

With a few exceptions, the order in which an attribute is applied relative to
other attributes is determined by the attribute's function. The priorities of
attribute functions are given by the list above, with a priority of one being
the highest.

Attributes with functions (2) or (3) cannot be applied to non-arithmetic types.
There are a few more restrictions that pertain to specific attributes: these are
given in the table below.

TODO create the table

Escaping Characters
-------------------

TODO explain when characters need to be escaped.

The Formatter Class
-------------------

TODO explain

Reference
---------

TODO create the reference.
