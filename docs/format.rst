.. _ccbase-format-module:
.. default-domain:: cpp

.. |tuple| replace::
   :class:`std::tuple`

.. |optional| replace::
   :class:`boost::optional<T>`

.. |string| replace::
   :class:`std::string`

.. |basic_string| replace::
   :class:`std::basic_string\<Char, Traits>`

.. |string_ref| replace::
   :class:`boost::string_ref`

.. |basic_string_ref| replace::
   :class:`boost::basic_string_ref\<Char, Traits>`

.. |formatter| replace::
   :class:`cc::formatter\<Args>`

.. |basic_formatter| replace::
   :class:`cc::basic_formatter\<Char, Traits>`

.. |runtime_error| replace::
   :class:`std::runtime_error`

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

        cc::println("Employee name: $.", "Gibble McGobblefart");
        // Prints "Employee name: Gibble McGobblefart." to stdout.

        cc::println("$ $! $1{upper} $2{upper}!", "Ding", "dong");
        // Prints "Ding dong! DING DONG!" to stdout.

        cc::println("File name: ${quote}, size: ${data}, version: $.",
                "test.txt", 1024, 1);
        // Prints "File name: "test.txt", size: 1 KiB, version: 1." to stdout.

        cc::writeln(log, "Ten-fold CV error: ${%, prec(2)}.", 0.12345);
        // Writes "Ten-fold CV error: 12.35%." to the log stream.

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

Special Printable Types
-----------------------

The :func:`operator<<` has been defined for two special types: |tuple| and
|optional| [*]_. The effects of printing these types are shown by the following
examples: ::

	cc::println(std::make_tuple(1, 2, 3));
        // Prints "(1, 2, 3)" to stdout.

	cc::println(boost::make_optional(0));
        // Prints "0" to stdout.

	cc::println(boost::optional<int>{});
        // Prints "none" to stdout.

	cc::println(boost::none);
        // Prints "none" to stdout.

.. [*] The |optional| type is actually printable by default, but only because it
   is implicitly convertible to :type:`bool`. So the output is generally not
   going to be very useful.

Syntax
------

Each function in this module takes a *format string* as an argument. This format
string can either be a string literal, a |string| or a |string_ref|. The format
string can contain zero or more *format arguments;* each format argument can
contain zero or more *attributes;* and each *attribute* can itself contain of
zero or more *attribute arguments.*

Format arguments are indicated by the ``$`` character. If a format argument
accepts attributes, then the attributes must be provided in a brace-enclosed
comma-separated list that occurs immediately after the ``$``. For example, the
format string ``"${hex, base}"`` contains a single argument, and this argument
contains two attributes.

Some attributes have optional or required arguments. Attribute arguments must be
provided in a parenthesis-enclosed comma-separated list that occurs after the
attribute name, similar to the C syntax for function invocation. For example,
the format string ``${align(C, 50, '*')}`` has a single format argument with a
single attribute. This attribute contains three attribute arguments.

Each format argument is associated with a one-based index that refers to a
user-supplied argument. This index can be provided explicitly immediately after
the ``$`` symbol. If the index of the first format argument is not provided,
then it is set to one. Otherwise, the default index of a format argument is one
more than the largest index of any preceding format argument. For example, the
format arguments in the format string ``$ $ $1 $`` have indices one, two, one,
and three, from left to right.

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
   :class:`std::string` s, or :class:`boost::string_ref` s.

With a few exceptions, the order in which an attribute is applied relative to
other attributes is determined by the attribute's function. The priorities of
attribute functions are given by the list above, with the priority one being the
highest.

Attributes with functions (2) or (3) cannot be applied to non-arithmetic types.
Additional restrictions can apply to certain attributes: these are described in
the table below.

============== ==========================================
Attribute Name Description
============== ==========================================
loc            Changes locale.
base           Adds manipulator :type:`std::showbase`.
oct            Adds manipulator :type:`std::oct`.
dec            Adds manipulator :type:`std::dec`.
hex            Adds manipulator :type:`std::hex`.
prec           Adds manipulator :type:`std::prec`.
fixed          Adds manipulator :type:`std::fixed`.
sci            Adds manipulator :type:`std::sci`.
char           Prints integral type as :type:`char`.
num            Promotes arithmetic type before printing.
bool           Prints arithmetic type as :type:`bool`.
data           Prints data size in human-readable format.
money          Prints currency according to locale.
sign           Controls sign for arithmetic types.
bin            Prints arithmetic type as binary.
%              Prints floating-point type as percentage.
upper          Converts string to upper case.
lower          Converts string to lower case.
quote          Quotes the argument.
align          Aligns the argument in fixed-width field.
============== ==========================================

The following table gives the function, priority, and minimum and maximum
parameter counts for each attribute.

==============  ==========================  ========  ==============  ==============
Attribute Name  Function                    Priority  Min Parameters  Max Parameters
==============  ==========================  ========  ==============  ==============
loc             Adds manipulators.          1         1               1
base            Adds manipulators.          1         0               1
oct             Adds manipulators.          1         0               0
dec             Adds manipulators.          1         0               0
hex             Adds manipulators.          1         0               0
prec            Adds manipulators.          1         1               1
fixed           Adds manipulators.          1         0               0
sci             Adds manipulators.          1         0               0
char            Converts number to number.  1         0               0
num             Converts number to number.  1         0               0
bool            Converts number to string.  2         0               0
data            Converts number to string.  2         0               1
money           Converts number to string.  2         0               1
sign            Converts number to string.  2         1               1
bin             Converts number to string.  2         0               0
%               Converts number to string.  2         0               0
upper           Converts string to string.  3         0               0
lower           Converts string to string.  3         0               0
quote           Converts type to string.    4         0               0
align           Converts string to string.  5         2               3
==============  ==========================  ========  ==============  ==============

We now describe the roles of the parameters for the attributes that take one
or more parameters.

``loc(name)``
  This attribute has a required parameter: the string describing the locale.
  Example: ``en_US``. Note that the locale name is **not** quoted.

``base(style = lower)``
  This attribute has an optional parameter. By default, various special
  characters (e.g. number bases and letters used for printing hexadecimal
  characters) are printed in lower case. If the argument ``upper`` is given,
  these characters are printed in upper case instead.

``prec(n)``
  This attribute has a required parameter: the desired precision. Example:
  ``6``.

``data(base = bin)``
  This attribute has an optional parameter. By default, the data is printed in
  binary SI units. If the argument ``dec`` is given, decimal SI units are used
  instead.

``money(cur = local)``
  This attribute has an optional parameter. By default, currency is printed
  using the local currency symbol (e.g. the symbol ``$`` is used instead of
  ``USD``). If the argument ``intl`` is given, currency is printed in
  international units instead.

``sign(style)``
  This attribute has a required parameter. If ``style`` is ``always``, then the
  sign is always printed, even for nonnegative numbers. If ``style`` is
  ``space``, the sign is printed for negative numbers, and a space is inserted
  before nonnegative numbers.

``align(dir, width, fill = ' ')``
  This attribute has two required parameters, and an optional third parameter.
  The ``dir`` parameter, which must be either ``'L'``, ``'C'``, or ``'R'``,
  controls the direction of alignment in the fixed-width field. The ``width``
  parameter is an integer that controls the width of the field (e.g.  ``80``).
  The ``fill`` parameter, which is set to ``' '`` by default, specifies the
  character used to fill any remaining space within the fixed-width field. Note
  that this parameter **must** be a character literal of length three. Escape
  sequences are currently unsupported.

Escaping Characters
-------------------

Regular characters in format strings need to be escaped in two situations:

1. Printing dollar signs.
2. Printing ``{`` immediately after a plain ``$`` argument.

In case (1), just double the dollar sign. For example, to print ``$``, the
format string should be ``"$$"``. In case (2), double the ``{`` symbol. For
example, the format string ``"${{"`` causes a ``{`` to be printed immediately
after the argument.

Using the Formatter
-------------------

The |formatter| class performs the actual work involving in parsing the format
string and storing the arguments and attributes. Each time one of the formatting
functions like :func:`cc::println` is called, a |formatter| object is created,
used to format the arguments, and subsequently returned. In the event that the
same format string is used several times, it is more efficient to reuse the
|formatter| object returned by the formatting function than to invoke the
function repeatedly. Here is an example that shows how this is done: ::

        auto fmt = cc::writeln(log, "Ten-fold CV error: ${%, prec(2)}.", 0.12345);
        // Writes "Ten-fold CV error: 12.35%." to the log stream.
        fmt(log, 0.10111);
        // Writes "Ten-fold CV error: 10.11%." to the log stream.

The |formatter| object can also be created independently of the formatting
functions, as shown in the following example. ::

        auto fmt = cc::formatter{"Ten-fold CV error: ${%, prec(2)}."};
        fmt(log, 0.12345);
        // Writes "Ten-fold CV error: 12.35%." to the log stream.

Reference
---------

**Note:** libstdc++ still does not implement move constructors for standard
streams. Since the |basic_formatter| class contains a standard stream as a
member, it cannot be moved when compiled with GCC. Therefore, any function below
that is documented to return |basic_formatter| actually returns :type:`void`
when compiled with GCC.

.. namespace:: cc

.. class:: basic_formatter<Char, Traits>

   This class is associated with the following aliases:

   - :type:`formatter` (with ``Char = char``, ``Traits = std::char_traits<char>``)
   - :type:`wformatter` (with ``Char = wchar_t``, ``Traits = std::char_traits<wchar_t>``)
   - :type:`u16formatter` (with ``Char = char16_t``, ``Traits = std::char_traits<char16_t>``)
   - :type:`u32formatter` (with ``Char = char32_t``, ``Traits = std::char_traits<char32_t>``)

   .. function:: basic_formatter(const boost::string_ref<Char, Traits>& fmt_str)

      Creates a |basic_formatter| object from the format string *fmt_str*.

      :throws: |runtime_error| if an error occurs while parsing *fmt_str*.

   .. function:: void operator()(std::basic_ostream& dst, Args)

      Applies the |basic_formatter| object to the parameter pack *Args*, and
      writes the result to *dst*.

      :throws: |runtime_error| if an error occurs while applying *fmt* to *Args*.

.. function:: basic_formatter write(std::basic_ostream& os, const boost::basic_string_ref& fmt, Args)
              basic_formatter print(const boost::basic_string_ref& fmt, Args)
              basic_formatter err(const boost::basic_string_ref& fmt, Args)

    Interprets *fmt* as a format string, and applies it to the parameter pack
    *Args*. The result is written to the destination output stream, and the
    |basic_formatter| object that is created in the process is returned.

    - For :func:`write`, the destination output stream is *os*.
    - For :func:`print`, the destination output stream is :type:`std::cout`.
    - For :func:`err`, the destination output stream is :type:`std::cerr`.

    :throws: |runtime_error| if an error occurs while parsing *fmt* or applying *fmt* to *Args*.

.. function:: basic_formatter writeln(std::basic_ostream& os, const boost::basic_string_ref& fmt, Args)
              basic_formatter println(const boost::basic_string_ref& fmt, Args)
              basic_formatter errln(const boost::basic_string_ref& fmt, Args)

    These functions are similar to their counterparts that do not end in ``ln``,
    but these functions append newlines to their destination output streams
    after performing the formatting operations.

    :throws: |runtime_error| if an error occurs while parsing *fmt* or applying *fmt* to *Args*.

.. function:: void write(basic_ostream& os, Arg&& arg)
              void writeln(basic_ostream& os, Arg&& arg)
              void print(basic_ostream& os, Arg&& arg)
              void println(basic_ostream& os, Arg&& arg)
              void err(basic_ostream& os, Arg&& arg)
              void errln(basic_ostream& os, Arg&& arg)

    Whereas the functions mentioned previously accept format string parameters,
    these do not. These functions are intended to be used when only a single
    argument needs to be printed, in which case the use of a format string
    containing a single ``$`` would be redundant.

.. function:: std::basic_string format(const boost::basic_string_ref& fmt, Args)
              std::basic_string format(const std::basic_string& fmt, Args)
              std::basic_string format(const CharT* fmt, Args)


    Interprets *fmt* as a format string, and applies it to the parameter pack
    *Args*. The result is returned as a |basic_string|.

    :throws: |runtime_error| if an error occurs while parsing *fmt* or applying *fmt* to *Args*.

.. function:: std::basic_string formatln(const boost::basic_string_ref& fmt, Args)
              std::basic_string formatln(const std::basic_string& fmt, Args)
              std::basic_string formatln(const CharT* fmt, Args)

    These functions are similar to their counterparts that do not end in ``ln``,
    but these functions append newlines to the output strings after performing
    the formatting operations.

    :throws: |runtime_error| if an error occurs while parsing *fmt* or applying *fmt* to *Args*.
