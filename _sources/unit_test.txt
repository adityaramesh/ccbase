.. _ccbase-unit-test-module:
.. default-domain:: cpp

The Unit Test Module
====================

To use this module, include ``ccbase/unit_test.hpp``.

Overview
--------

This header provides utilities for very basic unit testing. Tests are
implemented as modules, and a set of related modules is gathered in a suite.
Here is an example of a file called ``test.cpp`` which uses the unit testing
functionality. ::

	#include <ccbase/unit_test.hpp>

	module("Test 1", "This module always passes.")
	{
		require(1);
	}

	module("Test 2", "This module always fails.")
	{
		require(0);
	}

        // The description is optional.
	module("Test 3")
	{
		require(1);
	}

        // This declaration is required, and should appear at the end of the
        // test file.
	suite("This is an example test suite.")

By default, compiling ``test.cpp`` and running the resulting executable will
output the following. ::

	Summary for module "Test 1": 1 of 1 assertions passed.
	Summary for module "Test 2": 0 of 1 assertions passed.
	Summary for module "Test 3": 1 of 1 assertions passed.
	Summary for suite "test": 2 of 3 assertions passed.

If you wish to see more information about the assertions in the modules, then
you can control the level of the verbosity using the ``-v`` flag. For example,
running the executable with the option ``-v medium`` displays the following. ::

	Summary for module "Test 1": 1 of 1 assertions passed.
	Failure in module "Test 2", line 17: "require(false)".
	Summary for module "Test 2": 0 of 1 assertions passed.
	Summary for module "Test 2": 1 of 1 assertions passed.
	Summary for suite "test": 2 of 3 assertions passed.

Medium verbosity causes the line number and source code for failed assertions
within each module to be printed along with the summary statistics. High
verbosity prints this information for all assertions, regardless of success or
failure.

Reference
---------

The following is a summary of the options available when running an executable
file compiled with the unit test module.

============ ===========================================
Option       Flags
============ ===========================================
Help         ``-h``, ``--help``
List modules ``-l``, ``--list-modules``
Verbosity    ``-v``, ``--verbosity [low, medium, high]``
============ ===========================================
