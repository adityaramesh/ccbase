.. _ccbase-error-module:
.. default-domain:: cpp

.. |optional| replace::
   :class:`boost::optional`

.. |exception| replace::
   :class:`std::exception`

.. |exception_ptr| replace::
   :class:`std::exception_ptr`

.. |bad_expected_type| replace::
   :class:`bad_expected_type`

.. |nested_exception| replace::
   :class:`nested_exception`

.. |expected| replace::
   :class:`expected\<T>`

.. |expected_ref| replace::
   :class:`expected\<T&>`

.. |expected_void| replace::
   :class:`expected\<void>`

The Error Module
================

To use this module, include ``ccbase/error.hpp``.

Overview
--------

The |expected| class is a polymorphic type that is either in a *valid* or an
*invalid* state. If an instance is in an invalid state, then it stores an
exception; if it is in a valid state, then it stores an instance of *T*. This
allows us to return arbitrarily-rich error codes from a given function, without
forcing the programmer to respond to any errors immediately.

Here's an example where the |expected| class is used to provide an error-checked
wrapper over a low-level POSIX function: ::

        std::system_error current_system_error() noexcept
        { return std::system_error{errno, std::system_category()}; }

        cc::expected<int>
        safe_open(const char* path, int flags)
        noexcept
        {
        	auto r = int{};
        	do r = ::open(path, flags, S_IRUSR | S_IWUSR);
        	while (r == -1 && errno == EINTR);
        
        	if (r == -1) return current_system_error();
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
        	if (r == 0) { return cc::no_error; }
        	if (errno != EINTR) { return current_system_error(); }
        
        	for (;;) {
        		r = ::close(fd);
        		if (errno == EBADF) { return cc::no_error; }
        		if (errno != EINTR) { current_system_error(); }
        	}
        }

This module's implementation of |expected| is based on the one Andrei
Alexandrescu discusses in his talk at C++ Next 2012, called "Systematic Error
Handling" [#]_. Further improvements were made based on the implementation found
in `MNMLSTC Core`__. CCBase's implementation differs in the following ways:

- It works for reference types.

- One can move the |exception_ptr| from an |expected| object without rethrowing the referred exception. Attempting to do this with current implementations of |expected| may cause the program to crash because of a double-free.

- If ``CC_DONT_EXPECTED_ENFORCE_DISMISSAL`` is not defined, the destructor of |expected| will throw if the state of the object is not read at least once prior to destruction. Otherwise, no code is generated to perform this bookkeeping.

- If the expected type *T* is copy assignable or move assignable, then the implementation will use these operations instead of redundantly destroying and copy or move constructing the expected object. This can potentially accelerate copy- or move-assignment of |expected|, when *T* has a non-trivial destructor.

- Accessors are overloaded for lvalue and rvalues to |expected|. Accessors overloaded for lvalues return lvalue references, while those overloaded for rvalues return rvalue references.

- Relational operators are not implemented. I am not convinced relational operators can be defined intuitively for algebraic data types like |optional| and |expected|.

.. [#] http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C 
.. _MNMLSTC: http://mnmlstc.github.io/core/optional.html#expected-type
.. [#] http://anto-nonco.blogspot.com/2013/03/extending-expected-to-deal-with.html

__ MNMLSTC_

Reference
---------

.. namespace:: cc

.. class:: in_place_t

   This class is used as a tag to disambiguate overloaded member functions that
   use variadic templates to construct values in-place.

   An instance of this class is available in the :ns`cc` namespace by the name
   ``in_place``.

.. class:: bad_expected_type

   :inherits: :class:`std::logic_error`

   Thrown when an operation that requires an |expected| object to be in a valid
   state is performed on an |expected| object in an invalid state, or vice
   versa.

.. class:: expected<T>

   An |expected| object is either in a *valid* or an *invalid* state. If
   ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is not defined, then the |expected|
   object is also associated with a binary *dismissal* state. The |expected|
   object is put into the dismissed state when a member function is invoked that
   reveals whether the object is in a valid or invalid state.
   
   The |expected| object can also be put into the dismissed state manually using
   the :func:`dismiss` member function. If the |expected| object is not in the
   dismissed state when its destructor is called, then an exception is thrown.
   This feature is intended to help enforce that all potential errors produced
   by functions returning |expected| are checked.

   Note that this class has distinct specializations for references and
   :type:`void`. The specialization to references has slightly different
   semantics, and the :type:`void` specialization lacks the member functions
   that have only to do with the expected type.

   .. type:: value_type

      This is the type managed by an |expected| object that is in a valid state.

      .. warning:: The :type:`value_type` must satify the following
         requirements. These requirements are enforced using static assertions
         within the class definition.
         
         - Its decayed type must not be |exception_ptr|. [1]_
         - Its decayed type must not be derived from |exception|. [1]_
         - It must be either an object or an lvalue reference. [2]_
         - It must be copy constructible. [2]_ [3]_
         - It must be nothrow destructible. [4]_
         
         .. [1] This would ambiguate calls to certain member functions.
         .. [2] This would make the definition of |expected| ill-formed.
         .. [3] Note that copy constructibility implies move constructibility.
         .. [4] This would violate exception safety.

   .. function:: expected()

      :noexcept: If *T* is nothrow default constructible.

      Disabled if *T* is not default constructible. Default-constructs an
      |expected| object in a valid state.

   .. function:: expected(const T& rhs)

      :noexcept: If *T* is nothrow copy constructible.

      Constructs an |expected| object in a valid state by copying *rhs*.

   .. function:: expected(T&& rhs)

      :noexcept: If *T* is nothrow move constructible.

      Constructs an |expected| object in a valid state by moving *rhs*.

   .. function:: expected(const in_place_t&, Args)

      :noexcept: If *T* is nothrow constructible from *Args*.

      Constructs an |expected| object in a valid state by initializing the
      expected type in-place using *Args*.

   .. function:: expected(const expected& rhs)

      Constructs an |expected| object in the same state as *rhs*, and copies
      either the value stored by *rhs* or its |exception_ptr|.

      :noexcept: If *T* is nothrow copy constructible.

   .. function:: expected(expected&& rhs)

      Constructs an |expected| object in the same state as *rhs*, and moves
      either the value stored by *rhs* or its |exception_ptr|.

      :noexcept: If *T* is nothrow move constructible.

   .. function:: expected(const std::exception_ptr& ptr) noexcept

      Constructs an |expected| object in an invalid state by copying *ptr*.

   .. function:: expected(exception_ptr&& ptr) noexcept

      Constructs an |expected| object in an invalid state by moving *ptr*.

   .. function:: expected(const Exception& e)

      :requires: *Exception* to be derived from ``std::exception``.
      :noexcept: If ``CC_NO_DEBUG`` is defined.

      Constructs an |expected| object in an invalid state from *e*.  If
      ``CC_NO_DEBUG`` is not defined, then this function throws if ``typeid(e)
      != typeid(Exception)``. If this happens, then slicing has occurred.

   .. function:: expected& operator=(const expected& rhs)

      :noexcept: If *T* is copy assignable, then the function is noexcept if *T* is nothrow copy assignable. Otherwise, the function is noexcept if *T* is nothrow copy constructible. In addition, ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` must be defined.

      Assigns this |expected| object to the same state as *rhs*, by copying
      either the value stored by *rhs* or its |exception_ptr|. If
      ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is not defined, then an exception
      is thrown if the object's state was not read prior to assignment.

   .. function:: expected& operator=(expected&& rhs)

      :noexcept: If *T* is move assignable, then the function is noexcept if *T* is nothrow move assignable. Otherwise, the function is noexcept if *T* is nothrow move constructible. In addition, ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` must be defined.

      Assigns this |expected| object to the same state as *rhs*, by moving
      either the value stored by *rhs* or its |exception_ptr|. If
      ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is not defined, then an exception
      is thrown if the object's state was not read prior to assignment.

   .. function:: expected& operator=(const T& rhs)

      :noexcept: If *T* is copy assignable, then the function is noexcept if *T* is nothrow copy assignable. Otherwise, the function is noexcept if *T* is nothrow copy constructible. In addition, ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` must be defined.

      Assigns this |expected| object to a valid state, and copies the value
      stored by *rhs*. If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is not defined,
      then an exception is thrown if the object's state was not read prior to
      assignment.

   .. function:: expected& operator=(T&& rhs)

      :noexcept: If *T* is move assignable, then the function is noexcept if *T* is nothrow move assignable. Otherwise, the function is noexcept if *T* is nothrow move constructible. In addition, ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` must be defined.

      Assigns this |expected| object to a valid state, and moves the value
      stored by *rhs*. If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is not defined,
      then an exception is thrown if the object's state was not read prior to
      assignment.

   .. function:: expected& operator=(const std::exception_ptr& ptr)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

      Assigns this |expected| object to an invalid state by copying *ptr*. If
      ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is not defined, then an exception
      is thrown if the object's state was not read prior to assignment.

   .. function:: expected& operator=(std::exception_ptr&& ptr)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

      Assigns this |expected| object to an invalid state by moving *ptr*. If
      ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is not defined, then an exception
      is thrown if the object's state was not read prior to assignment.

   .. function:: ~expected()

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

      Destroys this |expected| object by calling either the destructor of the
      expected type, or the destructor of the |exception_ptr|. If
      ``CC_DONT_EXPECTED_ENFORCE_DISMISSAL`` is not defined, an exception is
      thrown *after destroying the managed object* if the |expected| object is
      not in the dismissed state.

   .. function:: void raise() const

      :noexcept: ``false``
      :attributes: ``[[noreturn]]``

      If the |expected| object is invalid, throws the exception referred to by
      the managed |exception_ptr|. Otherwise, throws |bad_expected_type|. If
      ``CC_DONT_EXPECTED_ENFORCE_DISMISSAL`` is not defined, this function also
      puts the |expected| object in the dismissed state.

   .. function:: expected& dismiss() noexcept
                 const expected& dismiss() const noexcept

      If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined, puts the |expected|
      object in the dismissed state. Otherwise, this function is a no-op.

   .. function:: operator bool() const noexcept

      Returns whether this |expected| object is valid. If
      ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined, puts the |expected|
      object in the dismissed state.

   .. function:: T& value()
                 T&& value()
                 const T& value() const
                 T& operator*()
                 T&& operator*()
                 const T& operator*() const

      The functions returning lvalue references are overloaded for lvalues to
      |expected|, while those returning rvalue references are overloaded for
      rvalues to |expected|.
      
      If this |expected| object is valid, returns a reference to the managed
      value. Otherwise, throws |bad_expected_type|. If
      ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined, puts the |expected|
      object in the dismissed state.

   .. function:: T* operator->()
                  const T* operator->() const

      These functions are overloaded for lvalues to |expected|. If the
      |expected| object is valid, returns a pointer to the managed value.
      Otherwise, throws |bad_expected_type|. If
      ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined, puts the |expected|
      object in the dismissed state.

   .. function:: const std::exception_ptr& exception() const
                 std::exception_ptr&& exception()

      This first function is overloaded for lvalues to |expected|, while the
      second is overloaded for rvalues to |expected|. If the |expected| object
      is valid, returns an reference to the managed |exception_ptr|. Otherwise,
      throws |bad_expected_type|.

      .. warning:: If transferring ownership of the |exception_ptr| to another
         |expected| object, then the rvalue overload of :func:`exception`
         **must** be used. Otherwise, the program may crash due to double-free
         issues.
         
   .. function:: void swap(expected& rhs)

      :noexcept: If *T* is nothrow move constructible.

      Exchanges the state and contents of this |expected| object with those of
      *rhs*. If ``CC_DONT_EXPECTED_ENFORCE_DISMISSAL`` is defined, then the
      dismissal states of both |expected| objects are also exchanged.

   .. function:: expected& emplace(Args)

      :noexcept: If *T* is nothrow constructible from *Args* and ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined. 

      Assigns this |expected| object to a valid state by first destroying the
      managed object (either :type:`value_type` or |exception_ptr|), and then
      constructing :type:`value_type` in-place from *Args*.

   .. function:: Exception expect() const

      Returns an exception of type *Exception* by rethrowing the |exception_ptr|
      managed by this |expected| object. If the |expected| object is valid,
      |bad_expected_type| is thrown. If the managed |exception_ptr| does not
      refer to an exception of type *Exception*, then a |nested_exception| is
      thrown. This |nested_exception| is used to nest the exception referred to
      by the |exception_ptr| within an instance of |bad_expected_type|.

Functions
---------

.. function:: void swap(expected& lhs, expected& rhs)

   This global version of swap is defined for ADL.

.. function:: expected<ReturnValue> attempt(const NullaryFunction& f)

   Invokes *f* and returns the resulting value (if not :type:`void`) or thrown
   exception wrapped in an |expected| object.

Specializations
---------------

.. class:: expected<T&>

   This is the specialization of |expected| to reference types. Consult the
   class reference for |expected| to read the complete descriptions.

   .. function:: expected() noexcept

   .. function:: expected(T& rhs) noexcept

   .. function:: expected(const expected& rhs) noexcept

   .. function:: expected(expected&& rhs) noexcept

   .. function:: expected(const std::exception_ptr& ptr) noexcept

   .. function:: expected(exception_ptr&& ptr) noexcept

   .. function:: expected(const Exception& e)

      :requires: *Exception* to be derived from ``std::exception``.
      :noexcept: If ``CC_NO_DEBUG`` is defined.

   .. function:: expected& operator=(const expected& rhs)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: expected& operator=(expected&& rhs)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: expected& operator=(T& rhs)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: expected& operator=(const std::exception_ptr& ptr)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: expected& operator=(std::exception_ptr&& ptr)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: ~expected()

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: void raise() const

      :noexcept: ``false``
      :attributes: ``[[noreturn]]``

   .. function:: expected& dismiss() noexcept
                 const expected& dismiss() const noexcept

   .. function:: operator bool() const noexcept

   .. function:: T& value()
                 T&& value()
                 const T& value() const
                 T& operator*()
                 T&& operator*()
                 const T& operator*() const

   .. function:: T* operator->()
                 const T* operator->() const

   .. function:: const std::exception_ptr& exception() const
                 std::exception_ptr&& exception()

   .. function:: void swap(expected& rhs) noexcept

   .. function:: Exception expect() const

.. class:: expected<void>

   This is the specialization of |expected| to :type:`void`. Consult the
   class reference for |expected| to read the complete descriptions.

   .. function:: expected() noexcept

   .. function:: expected(const std::exception_ptr& ptr) noexcept

   .. function:: expected(exception_ptr&& ptr) noexcept

   .. function:: expected(const Exception& e)

      :requires: *Exception* to be derived from ``std::exception``.
      :noexcept: If ``CC_NO_DEBUG`` is defined.

   .. function:: expected& operator=(const expected& rhs)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: expected& operator=(expected&& rhs)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: expected& operator=(const std::exception_ptr& ptr)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: expected& operator=(std::exception_ptr&& ptr)

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: ~expected()

      :noexcept: If ``CC_EXPECTED_DONT_ENFORCE_DISMISSAL`` is defined.

   .. function:: void raise() const

      :noexcept: ``false``
      :attributes: ``[[noreturn]]``

   .. function:: expected& dismiss() noexcept
                 const expected& dismiss() const noexcept

   .. function:: operator bool() const noexcept

   .. function:: const std::exception_ptr& exception() const
                 std::exception_ptr&& exception()

   .. function:: void swap(expected& rhs) noexcept

   .. function:: Exception expect() const

.. namespace:: std

.. class:: hash<expected<T>>

   This is a specialization of :type:`std::hash\<U>` to |expected|.

   .. type:: result_type

      Aliased to ``typename hash<T>::result_type``.

   .. function:: result_type operator()(const expected& val) const noexcept

      If *val* is valid, returns the hash value of the managed value type.
      Otherwise, returns a default-constructed :type:`result_type`.
