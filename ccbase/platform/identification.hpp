/*
** File Name:	identification.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZCED3A582_E931_4EB0_BF05_4DED7F731208
#define ZCED3A582_E931_4EB0_BF05_4DED7F731208

#include <boost/preprocessor/slot/counter.hpp>
#include <ccbase/platform/definitions.hpp>
#include <ccbase/platform/variadic_size.hpp>

/*
** List of variable macros:
**
** PLATFORM_ARCH
** PLATFORM_COMPILER
** PLATFORM_COMPILER_VERSION
** PLATFORM_COMPILER_MAJOR_VERSION
** PLATFORM_COMPILER_MINOR_VERSION
** PLATFORM_COMPILER_PATCH_LEVEL
** PLATFORM_INTEGER_BYTE_ORDER
** PLATFORM_KERNEL
** PLATOFRM_OS
** PLATFORM_WORD_SIZE
** PLATFORM_NEWLINE
** PLATFORM_NEWLINE_LENGTH
** PLATFORM_DIRECTORY_SEPARATOR
** PLATFORM_MAX_FILENAME_LENGTH
** PLATFORM_MAX_PATHNAME_LENGTH
*/

/*
** Determine compiler.
*/

#undef BOOST_PP_COUNTER
#define BOOST_PP_COUNTER 0

#if defined __clang__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_COMPILER PLATFORM_COMPILER_CLANG
#endif

#if defined __COMO__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_COMPILER PLATFORM_COMPILER_COMEAU
#endif

#if defined __GNUC__ && !defined __clang__ && !defined __INTEL_COMPILER
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_COMPILER PLATFORM_COMPILER_GCC
#endif

#if defined __INTEL_COMPILER || defined __ICL
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_COMPILER PLATFORM_COMPILER_ICC
#endif

#if defined _MSC_VER
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_COMPILER PLATFORM_COMPILER_MSVC
#endif

#if BOOST_PP_COUNTER == 0
	#define PLATFORM_COMPILER PLATFORM_COMPILER_UNKNOWN
#elif BOOST_PP_COUNTER > 1
	#error "Conflicting compiler macros defined."
#endif

/*
** Determine compiler version.
*/

#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG
	#define PLATFORM_COMPILER_MAJOR_VERSION __clang_major__
	#define PLATFORM_COMPILER_MINOR_VERSION __clang_minor__
	#define PLATFORM_COMPILER_PATCH_LEVEL   __clang_patchlevel__
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_COMEAU
	#define PLATFORM_COMPILER_MAJOR_VERSION __COMO_VERSION__ / 100
	#define PLATFORM_COMPILER_MINOR_VERSION __COMO_VERSION__ % 100
	#define PLATFORM_COMPILER_PATCH_LEVEL 0
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_GCC
	#define PLATFORM_COMPILER_MAJOR_VERSION __GNUC__
	#define PLATFORM_COMPILER_MINOR_VERSION __GNUC_MINOR__
	#define PLATFORM_COMPILER_PATCH_LEVEL   __GNUC_PATCHLEVEL__
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	#define PLATFORM_COMPILER_MAJOR_VERSION __INTEL_COMPILER / 100
	#define PLATFORM_COMPILER_MINOR_VERSION __INTEL_COMPILER % 100 / 10
	#define PLATFORM_COMPILER_PATCH_LEVEL   __INTEL_COMPILER % 10
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_MSVC
	// This only works after Visual C++ 8.0 (2005).
	#define PLATFORM_COMPILER_MAJOR_VERSION _MSC_FULL_VER / 10000000
	#define PLATFORM_COMPILER_MINOR_VERSION _MSC_FULL_VER % 10000000 / 100000
	#define PLATFORM_COMPILER_PATCH_LEVEL   _MSC_FULL_VER % 100000
#else
	#define PLATFORM_COMPILER_MAJOR_VERSION \
		PLATFORM_COMPILER_MAJOR_VERSION_UNKNOWN
	#define PLATFORM_COMPILER_MINOR_VERSION \
		PLATFORM_COMPILER_MINOR_VERSION_UNKNOWN
	#define PLATFORM_COMPILER_PATCH_LEVEL_VERSION \
		PLATFORM_COMPILER_PATCH_LEVEL_VERSION_UNKNOWN
#endif

#define CC_COMPILER_VERSION(v, r, p) (((v) << 24) + ((r) << 16) + (p))

#define PLATFORM_COMPILER_VERSION                \
	CC_COMPILER_VERSION(                     \
		PLATFORM_COMPILER_MAJOR_VERSION, \
		PLATFORM_COMPILER_MINOR_VERSION, \
		PLATFORM_COMPILER_PATCH_LEVEL    \
	)

/*
** Determine architecture.
*/

#undef BOOST_PP_COUNTER
#define BOOST_PP_COUNTER 0

#if defined __arm__ || defined __thumb__ || defined _TARGET_ARCH_ARM || \
    defined __TARGET_ARCH_THUMB || defined _ARM || defined _M_ARM || \
    defined _M_ARMT || defined __aarch64__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_ARCH PLATFORM_ARCH_ARM
#endif

#if defined __ia64__ || defined _IA64 || defined __IA64__ || defined __ia64 || \
    defined _M_IA64 || defined __itanium__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_ARCH PLATFORM_ARCH_ITANIUM
#endif

#if defined i386 || defined __i386 || defined __i386__ || defined __i486__ || \
    defined __i586__ || defined __i686__ || defined __IA32__ || \
    defined _M_I86 || defined _M_IX86 || defined __X86__ || defined _X86_ || \
    defined __THW_INTEL__ || defined __I86__ || defined __INTEL__ || \
    defined __amd64__ || defined __amd64 || defined __x86_64__ || \
    defined __x86_64 || defined _M_X64 || defined _M_AMD64
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_ARCH PLATFORM_ARCH_X86
#endif

#if BOOST_PP_COUNTER == 0
	#define PLATFORM_ARCH PLATFORM_ARCH_UNKNOWN
#elif BOOST_PP_COUNTER > 1
	#error "Conflicting compiler macros defined."
#endif

/*
** Determine word size.
*/

#undef BOOST_PP_COUNTER
#define BOOST_PP_COUNTER 0

#if defined _ILP32 || defined __ILP32__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_WORD_SIZE 32
#endif

#if defined _LP64 || defined __LP64__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_WORD_SIZE 64
#endif

#if BOOST_PP_COUNTER == 0
	#define PLATFORM_WORD_SIZE PLATFORM_WORD_SIZE_UNKNOWN
#elif BOOST_PP_COUNTER > 1
	#error "Conflicting word size macros defined."
#endif

/*
** Determine operating system and kernel.
*/

#undef BOOST_PP_COUNTER
#define BOOST_PP_COUNTER 0

#if defined __linux__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_OS                  PLATFORM_OS_LINUX_DISTRIBUTION
	#define PLATFORM_KERNEL              PLATFORM_KERNEL_LINUX
	#define PLATFORM_NEWLINE             "\n"
	#define PLATFORM_NEWLINE_LENGTH      1
	#define PLATFORM_DIRECTORY_SEPARATOR '/'

	#include <linux/limits.h>

	#ifdef NAME_MAX
		#define PLATFORM_MAX_FILENAME_LENGTH NAME_MAX
	#elif
		#define PLATFORM_MAX_FILENAME_LENGTH \
			PLATFORM_MAX_FILENAME_LENGTH_UNKNOWN
	#endif

	#ifdef PATH_MAX
		#define PLATFORM_MAX_PATHNAME_LENGTH PATH_MAX
	#elif
		#define PLATFORM_MAX_PATHNAME_LENGTH \
			PLATFORM_MAX_PATHNAME_LENGTH_UNKNOWN
	#endif
#endif

#if defined macintosh || defined Macintosh || defined __APPLE__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_OS                  PLATFORM_OS_OS_X
	#define PLATFORM_KERNEL              PLATFORM_KERNEL_XNU
	#define PLATFORM_NEWLINE             "\n"
	#define PLATFORM_NEWLINE_LENGTH      1
	#define PLATFORM_DIRECTORY_SEPARATOR '/'

	#include <sys/syslimits.h>

	#ifdef NAME_MAX
		#define PLATFORM_MAX_FILENAME_LENGTH NAME_MAX
	#elif
		#define PLATFORM_MAX_FILENAME_LENGTH \
			PLATFORM_MAX_FILENAME_LENGTH_UNKNOWN
	#endif

	#ifdef PATH_MAX
		#define PLATFORM_MAX_PATHNAME_LENGTH PATH_MAX
	#elif
		#define PLATFORM_MAX_PATHNAME_LENGTH \
			PLATFORM_MAX_PATHNAME_LENGTH_UNKNOWN
	#endif
#endif

#if defined _WIN16 || defined _WIN32 || defined _WIN64 || defined __WIN32__ || \
    defined __TOS_WIN__ || defined __WINDOWS__
	#include BOOST_PP_UPDATE_COUNTER()
	#define PLATFORM_OS                  PLATFORM_OS_WINDOWS
	#define PLATFORM_KERNEL              PLATFORM_KERNEL_WINDOWS_NT
	#define PLATFORM_NEWLINE             "\r\n"
	#define PLATFORM_NEWLINE_LENGTH      2
	#define PLATFORM_DIRECTORY_SEPARATOR '\\'
	#define PLATFORM_MAX_FILENAME_LENGTH PLATFORM_MAX_FILENAME_LENGTH_UNKNOWN
	#define PLATFORM_MAX_PATHNAME_LENGTH PLATFORM_MAX_PATHNAME_LENGTH_UNKNOWN
#endif

#if BOOST_PP_COUNTER == 0
	#define PLATFORM_OS             PLATFORM_OS_UNKNOWN
	#define PLATFORM_KERNEL         PLATFORM_KERNEL_UNKNOWN
	#define PLATFORM_NEWLINE_LENGTH PLATFORM_NEWLINE_LENGTH_UNKNOWN
#elif BOOST_PP_COUNTER > 1
	#error "Conflicting word size macros defined."
#endif

/*
** Determine byte order.
*/

#undef BOOST_PP_COUNTER
#define BOOST_PP_COUNTER 0

/*
** TODO: Make this work for Windows.
*/

#if PLATFORM_COMPILER == PLATFORM_COMPILER_GCC || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG
	#ifdef __BYTE_ORDER__
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE
		#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_BIG
		#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE_WORD
		#endif
	#endif
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	#include <sys/param.h>

	#ifdef __BYTE_ORDER
		#if __BYTE_ORDER == __LITTLE_ENDIAN
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE
		#elif __BYTE_ORDER == __BIG_ENDIAN
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_BIG
		#elif __BYTE_ORDER == __PDP_ENDIAN
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE_WORD
		#endif
	#endif
#elif PLATFORM_OS == PLATFORM_OS_MACOS
	#include <machine/endian.h>

	#ifdef BYTE_ORDER
		#if BYTE_ORDER == LITTLE_ENDIAN
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE
		#elif BYTE_ORDER == BIG_ENDIAN
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_BIG
		#elif BYTE_ORDER == PDP_ENDIAN
			#include BOOST_PP_UPDATE_COUNTER()
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE_WORD
		#endif
	#endif
#endif

#if BOOST_PP_COUNTER == 0
	#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_UNKNOWN
#elif BOOST_PP_COUNTER > 1
	#error "Conflicting byte order macros defined."
#endif

#endif
