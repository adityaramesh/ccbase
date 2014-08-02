.. _ccbase-usage:

Using CCBase
============

Installation
------------

The sources can be downloaded here_. The library is header-only, so you can
start using it right away by adding the ``include`` directory to your include
path. However, it is recommended that you compile and run the unit tests to make
sure that things are working as intended.

.. _here: https://github.com/adityaramesh/ccbase/archive/master.zip

Compiling the Unit Tests
~~~~~~~~~~~~~~~~~~~~~~~~

To compile the unit tests, you will need to have Rake installed on your system.
Then, configure the following environment variables:

- Set ``CXX`` to a C++11-conforming compiler. The library has been tested on GCC (versions 4.7, 4.8, and 4.9), Clang (versions 3.3 and 3.4), and ICC (versions 13.0 and 14.0).

- Set ``BOOST_INCLUDE_PATH`` to your Boost installation directory. CCBase requires Boost version 1.55 or above.

Finally, run the following commands: ::

    rake
    rake check

If ``rake check`` produced no output, then all of the units tests passed.
Otherwise, please `file an issue`__ with the output of the unit tests and your
platform details (your OS and compiler versions, along with any other relevant
information).

.. _issue: https://github.com/adityaramesh/ccbase/issues
__ issue_

Library Structure
-----------------

For each module in CCBase, there is a header file in the ``ccbase`` directory
that brings the public API into the ``cc`` namespace. For example, to use the
format module, include ``ccbase/format.hpp``. Each module is also associated
with a subdirectory in ``ccbase``. Each subdirectory contains the header files
that comprise the associated module.
