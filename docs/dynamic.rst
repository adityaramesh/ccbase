.. _ccbase-dynamic-module:
.. default-domain:: cpp

.. |expected| replace::
   :type:`expected\<T>`

.. |load| replace::
   :func:`load\<T>`

.. |query| replace::
   :func:`query`

.. |function| replace::
   :class:`function <function\<Signature>>`

The Dynamic Module
==================

To use this module, include ``ccbase/dynamic.hpp``. Please note that this module
currently works on OS X and Linux only.

Overview
--------

This module does the following two things:

  - Provides clean, cross-platform syntax for loading functions and symbols from dynamic libraries.
  - Provides cross-platform macros to control symbol visibility.

Loading Dynamic Libraries
-------------------------

Suppose that you have a library called ``test.dll``, which defines two symbols
of interest: *msg*, a :type:`std::string` and :func:`test`, a function with the
signature ``int(const std::string&, const std::string&)``. Assuming that both
symbols have C linkage, then you could load them as follows: ::

	using sig = int(const std::string&, const std::string&);
	auto img  = cc::image{"test.dll", cc::binding_mode::lazy};
	auto test = cc::load<signature>("test", img).get();
	auto& msg = cc::load<std::string>("msg", img).get();

The function |load| returns an |expected| object, which contains either the
object loaded from the symbol, or the exception that prevented the object from
being loaded.  Invoking :func:`get` on the |expected| objects throws the stored
exception if the object is in an invalid state, and returns the stored value
otherwise.

Notice that when we loaded *msg* from the image, we accepted the return value by
reference rather than by value. This is because |load| returns a reference to
the object at the symbol's address, so mutating the reference will also change
the data at the symbol's address in memory.

One can also query information about the loaded objects, as in the following
example: ::

	using sig = std::string(std::string, std::string);
	auto img  = cc::image{"test.dll", cc::binding_mode::lazy};
	auto test = cc::load<signature>("test", img).get();

        auto test_info = cc::query(test).get();
        cc::println(test_info.name());
        // Prints "test".
        cc::println(test_info.address());
        // Prints the address of `test`.

Reference
~~~~~~~~~

.. namespace:: cc

.. class:: binding_mode: int

   Specifies the way in which the symbols in the library are loaded. A valid
   :class:`binding_mode` consists of either :member:`lazy` or :member:`now` OR'd
   with zero or more of the other enum values.

   .. member:: binding_mode lazy

      Equivalent in function to the POSIX macro ``RTLD_LAZY``.

   .. member:: binding_mode now

      Equivalent in function to the POSIX macro ``RTLD_NOW``.

   .. member:: binding_mode global

      Equivalent in function to the POSIX macro ``RTLD_GLOBAL``.

   .. member:: binding_mode local

      Equivalent in function to the POSIX macro ``RTLD_LOCAL``.

   .. member:: binding_mode nodelete

      Defined only if the Linux-specific macro ``RTLD_NODELETE`` is defined.

   .. member:: binding_mode noload

      Defined only if the Linux-specific macro ``RTLD_NOLOAD`` is defined.

   .. member:: binding_mode deepbind

      Defined only if the Linux-specific macro ``RTLD_DEEPBIND`` is defined.
      
.. class:: image

   This class provides a wrapper over the platform-specific handle to a loaded
   dynamic library.

   .. function:: explicit image (const boost::string_ref path, binding_mode mode)

      Retrieves a handle to the dynamic library at the given path, using the
      specified mode. 

      :throws: :class:`std::runtime_exception` If the dynamic library could not be accessed.

   .. function:: ~image()

      Closes the handle to the dynamic library, if the handle is valid.

   .. function:: void* handle() const noexcept

      Returns the internal handle to the dynamic library.

   .. function:: void close()

      Closes the handle to the dynamic library, if the handle is valid.

.. class:: function<Signature>

   This class is used to represent a function loaded from a dynamic library.

   .. function:: ReturnType operator()(Args&& args) const

      Invokes the function by forwarding the given arguments.

      :noexcept: True iff the function has the ``noexcept`` property when called with the fowarded arguments.

   .. function: const void* address() const noexcept

      Returns the address of the function.

.. class:: symbol_info

   This class is used to store the information obtained after querying a symbol
   loaded from a dynamic library.

   .. function:: const boost::string_ref path() const noexcept

      Returns the path to the dynamic library file.

   .. function:: const boost::string_ref name() const noexcept

      Returns the name of the symbol.

   .. function:: const void* base_address() const noexcept
      
      Returns the base address of the dynamic library.

.. function:: expected<symbol_info> query(const T& t) noexcept

   Returns the symbol information associated with the given object.

.. function:: expected<symbol_info> query(const function<Signature>& f) noexcept

   Returns the symbol information associated with the given function.

.. function:: expected<T&> load<T>(const boost::string_ref name, const image& img) noexcept

   Loads the object symbol with the given name from the image file.

.. function:: expected<function<Signature>> load<Signature>(const boost::string_ref name, const image& img) noexcept

   Loads the function symbol with the given name from the image file.

Controlling Symbol Visibility
-----------------------------

The following macros can be used to set symbol visibility when compiling shared
libraries. ::

	// Used for public symbols in a header for a shared library that is to
	// be implicitly linked into the final executable.
	IMPORT_SYMBOL

	// Used for public symbols in source code that is to be compiled into a
	// shared library.
	EXPORT_SYMBOL

	// Used to hide symbols in source code that is to be compiled into a
	// shared library.
	HIDDEN_SYMBOL

Often times, it is the case that the same header file is used both by the source
code that is compiled into the shared library, and by the source code that links
to the shared library. In the first case, public symbols should be prefixed by
``EXPORT_SYMBOL``; in the second case, public symbols should be prefixed by
``IMPORT_SYMBOL``. In both cases, private symbols that are not included in the
shared library should be prefixed by ``HIDDEN_SYMBOL``. The following macros are
provided to make this task easier: ::

	PUBLIC_SYMBOL
	PRIVATE_SYMBOL

``PUBLIC_SYMBOL`` expands to ``IMPORT_SYMBOL`` if ``CCBASE_IMPORT_SYMBOLS`` is
defined, or ``EXPORT_SYMBOL`` if ``CCBASE_EXPORT_SYMBOLS`` is defined. If neither of
the two macros is defined, then ``PUBLIC_SYMBOL`` expands to nothing.
``PRIVATE_SYMBOL`` expands to ``HIDDEN_SYMBOL`` if either of the two macros is
defined, and nothing otherwise.
