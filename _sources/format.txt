.. _ccbase-format-module:
.. default-domain:: cpp

The Format Module
=================

**Warning:** this documentation does not reflect the current state of the format
module. Please ignore this documentation for now.

To use this module, include ``ccbase/format.hpp``.

Overview
--------

This module provides clean syntax for printing and formatting strings. Since
this module is built on top of IOStreams, the function ``std::ostream&
operator<<(std::ostream&, T)`` must be defined for a given type *T* to be
printable.

Printing to Output Streams
~~~~~~~~~~~~~~~~~~~~~~~~~~

::

        cc::println("Hello, world!");
        // Prints "Hello, world!".

        cc::println("File name: $, size: $, version: $.", "test.txt", 1024, 1.0);
        // Prints "File name: test.txt, size: 1024, version: 1.0.".

        cc::println("Hello $, my name is $. Bye, $1.", "Gibble", "Gobble");
        // Prints "Hello Gibble, my name is Gobble. Bye, Gibble.".

In the third example, we used a number after the last ``$`` to refer to the
first argument. We could in fact number each ``$``, but most of the time, this
is uneccessary.

The function :func:`errln` can be used to write to ``stderr`` instead of
``stdout``, and :func:`writeln` can be used to write to an arbitrary
:class:`ostream`. Each function that ends in ``ln`` also has a variant that does
not end in ``ln``. Use the latter functions if you do not want newlines appended
to the output.

Formatting Objects
~~~~~~~~~~~~~~~~~~

TODO

Escaping Characters
~~~~~~~~~~~~~~~~~~~

TODO: Revise after changing interface.

To print the dollar sign character, escape the dollar sign like so: ``{$}``. To
escape a curly bracket, use another curly bracket of the same kind. For
instance, ``{{`` prints ``{``.

Reference
---------

TODO: Revise after changing interface.
