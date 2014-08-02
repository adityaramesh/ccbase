.. _ccbase-platform-module:
.. default-domain:: cpp

The Platform Module
===================

To use this module, include ``ccbase/platform.hpp``.

Overview
--------

This module does the following three things:

- Provides macros to identify various features describing the host platform.
- Provides macros to invoke compiler attributes in a cross-platform way.
- Provides clean, cross-platform syntax to access compiler intrinsics.

Platform Identification
-----------------------

This module attempts to identify the following features of the host platform:

- The compiler.
- The compiler version.
- The processor architecture.
- The processor ABI.
- The operating system.
- The kernel.
- The integer byte order. (Note that the floating-point byte order can potentially be different from the integer byte order, but the header makes no attempt to identify the latter.)
- The platform newline character.
- The platform directory separator.
- The maximum permissible file and path name lengths.

Here are some examples of what this module lets you do: ::

        // Safely include platform-specific header files.
        #if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX || \
            PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
                #include <unistd.h>
        #else
                #error Unsupported platform.
        #endif

        // Safely include compiler-specific header files.
        #if PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
            PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
            PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
                #include <cpuid.h>
        #else
                #error Unsupported compiler.
        #endif

        // Parse a big-endian value.
        auto val = get_big_endian_value();
        #if PLATFORM_INTEGER_BYTE_ORDER == PLATFORM_BYTE_ORDER_BIG
                // Do nothing.
        #elif PLATFORM_INTEGER_BYTE_ORDER == PLATFORM_BYTE_ORDER_LITTLE
                val = cc::bswap(val);
        #else
                #error Unsupported platform byte order.
        #endif

        // Deploy workarounds for buggy compilers.
        #if PLATFORM_COMPILER_VERSION < CC_COMPILER_VERSION(3, 2, 1)
                // Use workaround.
        #else
                // Use normal method.
        #endif

Since this module relies on knowledge of predefined preprocessor macros, not all
of the features tabulated below may be succesfully identified. In the case that
a particular feature (say, ``XXX``) is not successfully identified, the
corresponding macro ``PLATFORM_XXX`` is usually set to the value
``PLATFORM_XXX_UNKNOWN``. However, this is not always the case. Consult the
table below for details.

Reference
~~~~~~~~~

The macros defined by the preprocessor are listed in the table below. Where
``*`` is used to indicate the value of a macro, the name of the macro is to be
substituted.

=================================== ===================================== =======================================================================
Macro                               Description                           Possible Values                                                      
=================================== ===================================== =======================================================================
``PLATFORM_ARCH``                   Platform CPU architecture.            ``*_ARM, *_ITANIUM, *_X86, *_UNKNOWN``
``PLATFORM_COMPILER``               Platform compiler.                    ``*_CLANG, *_COMEAU, *_GCC, *_ICC, *_MSVC, *_UNKNOWN``
``PLATFORM_COMPILER_VERSION``       Platform compiler version.            Integer value or ``*_UNKNOWN``; compare to ``CC_COMPILER_VERSION(version, revision, patch)``.
``PLATFORM_COMPILER_MAJOR_VERSION`` Platform compiler major version.      Integer value or ``*_UNKNOWN``.
``PLATFORM_COMPILER_MINOR_VERSION`` Platform compiler minor version.      Integer value or ``*_UNKNOWN``.
``PLATFORM_COMPILER_PATCH_LEVEL``   Platform compiler patch level.        Integer value or ``*_UNKNOWN``.
``PLATFORM_INTEGER_BYTE_ORDER``     Platform byte order.                  ``(* = PLATFORM_BYTE_ORDER) *_LITTLE, *_BIG, *_LITTLE_WORD, *_UNKNOWN``
``PLATFORM_KERNEL``                 Platform kernel.                      ``*_LINUX, *_WINDOWS_NT, *_XNU, *_UNKNOWN``
``PLATFORM_OS``                     Platform operating system.            ``*_LINUX, *_WINDOWS, *_OS_X, *_UNKNOWN``
``PLATFORM_WORD_SIZE``              Platform word size.                   ``32, 64, *_UNKNOWN``
``PLATFORM_NEWLINE``                Platform newline.                     ``"\n"``, ``"\r\n"``, or undefined.
``PLATFORM_NEWLINE_LENGTH``         Platform newline length.              Integer value or ``*_UNKNOWN``.
``PLATFORM_DIRECTORY_SEPARATOR``    Platform directory separator.         Character literal or undefined.
``PLATFORM_MAX_FILENAME_LENGTH``    Maximum permissible file name length. Integer value or undefined.
``PLATFORM_MAX_PATHNAME_LENGTH``    Maximum permissible path name length. Integer value or undefined.
=================================== ===================================== =======================================================================

Compiler Attributes
-------------------

This following macros provide access to nonstandard attributes that are commonly
implemented by compilers. If the host compiler does not implement the attribute
corresponding to a given macro, then the macro expands to nothing.

==================== ==================================================================================
Macro                Description
==================== ==================================================================================
``CC_ALWAYS_INLINE`` Forces the compiler to inline the designated function.
``CC_NEVER_INLINE``  Instructs the compiler not to inline the designated function.
``CC_CONST``         Tells the compiler that the designated function does not access global memory.    
``CC_PURE``          Tells the compiler that the designated function does not modify any global memory.
``CC_RESTRICT``      Expands to the compiler's equivalent of the C99 ``restrict`` keyword.
``CC_ALIGN(n)``      Used to align addresses of static arrays to multiples of ``n``.
==================== ==================================================================================

Compiler Intrinsics
-------------------

The following functions provide access to intrinsics commonly defined by
compilers.

.. namespace:: cc

.. function:: T bswap(T value) noexcept

   This function is defined for each arithmetic type *T*. It returns a copy of
   the variable *value* with the order of the bytes reversed. If the compiler
   defines an intrinsic to perform this operation, then the intrinsic is used.
   Otherwise, the library resorts to a default implementation.

.. function:: void yield_processor() noexcept

   Evaluates to the compiler intrinsic that emits the ``pause`` instruction for
   x86_64 CPUs, if such an intrinsic is available. Otherwise, this function does
   nothing. Using the ``pause`` instruction in spinlocks is beneficial for the
   following three reasons [#]_:

   - Improves performance by decreasing memory contention within the processor.
   - Decreases power consumption.
   - Improves performance in the context of hyperthreading, because it avoids saturating use of the ALU.

.. [#] http://www.1024cores.net/home/lock-free-algorithms/tricks/spinning
