.. _ccbase-error-module:
.. default-domain:: cpp

.. |expected| replace::
   :class:`expected\<T>`

.. |expected_void| replace::
   :class:`expected\<void>`

.. |optional| replace::
   :class:`boost::optional\<T>`

The Error Module
================

To use this module, include ``ccbase/error.hpp``.

Overview
--------

The |expected| class is a polymorphic type that is either in a *valid* or an
*invalid* state. If an instance is in an invalid state, then it stores an
exception; if it is in a valid state, then it stores an instance of *T*. This
allows us to return arbitrarily-rich error codes from a given function, without
forcing the programmer to respond to the exception immediately.

Here's an example where the |expected| class is used to provide an error-checked
wrapper over a low-level POSIX function: ::

        std::system_error current_system_error() noexcept
        { return std::system_error{errno, std::system_category()}; }

        cc::expected<int>
        safe_open(const char* path, int flags)
        noexcept
        {
        	auto r = int{};
        	do {
        		r = ::open(path, flags, S_IRUSR | S_IWUSR);
        	}
        	while (r == -1 && errno == EINTR);
        
        	if (r == -1) { return current_system_error(); } }
        	return r;
        }

        int main()
        {
                try {
                        // Deferences the returned `expected` object, which
                        // returns the stored value or throws the stored
                        // exception.
                        auto fd = *safe_open("test.txt", O_RDONLY);
                catch (const std::system_error& e) {
                        // Respond to the exception here.
                }
                
                // This time, we defer responding to the exception.
                auto exp = safe_open("test.txt", O_RDONLY);

                // Do other stuff.

                if (!exp) {
                        // Respond to the error.
                }
        }

Sometimes it makes sense to return an |expected| object from a function, even if
function does not really return anything. Consider the following example: ::

        cc::expected<void>
        safe_close(int fd)
        {
        	auto r = ::close(fd);
        	if (r == 0) { return true; }
        	if (errno != EINTR) { return current_system_error(); }
        
        	for (;;) {
        		r = ::close(fd);
        		if (errno == EBADF) { return true; }
        		if (errno != EINTR) { current_system_error(); }
        	}
        }

This module's implementation of |expected| is based on the one Andrei
Alexandrescu discusses in his talk at C++ Next 2012 called "Systematic Error
Handling" [#]_. The implementation in CCBase is extended in the following ways:

- Several useful member functions and overloaded operators have been added.
- It works for ``void`` and reference types [#]_.
- If ``NEO_NO_DEBUG`` is not defined, an assertion is performed to ensure that the state of the |expected| object is read at least once prior to destruction.

.. [#] http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C 
.. [#] http://anto-nonco.blogspot.com/2013/03/extending-expected-to-deal-with.html

Reference
---------

.. namespace:: cc

.. class:: expected<T>

   Note that this class has a distinct specialization for :type:`void`, with
   slightly different semantics.

   .. function:: expected(const T& rhs) noexcept

      Constructs an |expected| object in a valid state by copying the given
      object.

   .. function:: expected(T&& rhs) noexcept

      Constructs an |expected| object in a valid state by moving the given
      object.

   .. function:: expected() noexcept

      Constructs an |expected| object in an invalid state from the exception
      that is currently in flight (i.e. from :func:`std::current_exception()`).

   .. function:: expected(std::exception_ptr p) noexcept

      Constructs an |expected| object in an invalid state from the given
      :type:`std::exception_ptr` object.

   .. function:: expected(const Exception& e) noexcept

      :requires: *Exception* to be derived from ``std::exception``.

      Constructs an |expected| object in an invalid state from the given exception.

   .. function:: expected(const expected& rhs) noexcept

   .. function:: expected(expected&& rhs) noexcept

   .. function:: bool valid() const noexcept

      Returns whether this |expected| object is in a valid state.

   .. function:: operator bool() const noexcept

      Equivalent to :func:`valid`.

   .. function:: reference get()
   .. function:: const reference get() const

      If the |expected| object is in a valid state, returns a reference to the
      stored object. Otherwise, throws the stored exception.

   .. function:: reference operator*()
   .. function:: const reference operator*() const
      
      Equivalent to :func:`get`. This function was included to better resemble
      the interface of |optional|.

   .. function:: T&& move()

      This function is not defined if *T* is a ``const`` reference. If the
      |expected| object is in a valid state, returns an rvalue reference to the
      stored object. Otherwise, throws the stored exception.

   .. void swap(expected& rhs) noexcept

      Swaps the contents of this |expected| object with those of another.

   .. bool has_exception<Exception>()

      Checks whether this |expected| object is invalid, and contains an
      exception of type *Exception*. Caution: this function is slow, because it
      involves throwing and catching the stored exception in order to detect its
      type. Avoid using this function in performance-critical contexts.

.. class:: expected<void>

   This is the specialization of |expected| for :type:`void`.

   .. function:: expected() noexcept

      Constructs an |expected_void| object in an invalid state from the
      exception that is currently in flight (i.e. from
      :func:`std::current_exception()`).

   .. function:: expected(std::exception_ptr p) noexcept

      Constructs an |expected_void| object in an invalid state from the given
      :type:`std::exception_ptr` object.

   .. function:: expected(const Exception& e) noexcept

      :requires: *Exception* to be derived from ``std::exception``.

      Constructs an |expected_void| object in an invalid state from the given
      exception.

   .. function:: expected(const expected& rhs) noexcept

   .. function:: expected(expected&& rhs) noexcept

   .. function:: bool valid() const noexcept

      Returns whether this |expected_void| object is in a valid state.

   .. function:: operator bool() const noexcept

      Equivalent to :func:`valid`.

   .. function:: void get() const

      If the |expected_void| object is in a valid state, returns :type:`void`.
      Otherwise, throws the stored exception.

   .. function:: void operator*() const
      
      Equivalent to :func:`get`. This function was included to better resemble
      the interface of |optional|.

   .. void swap(expected& rhs) noexcept

      Swaps the contents of this |expected_void| object with those of another.

   .. bool has_exception<Exception>()

      Checks whether this |expected_void| object is invalid, and contains an
      exception of type *Exception*. Caution: this function is slow, because it
      involves throwing and catching the stored exception in order to detect its
      type. Avoid using this function in performance-critical contexts.
