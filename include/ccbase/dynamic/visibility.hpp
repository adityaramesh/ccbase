/*
** File Name:	visibility.hpp
** Author:	Aditya Ramesh
** Date:	06/30/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZBA05AAB6_3F9E_4C1F_8FEB_2F4304CD2335
#define ZBA05AAB6_3F9E_4C1F_8FEB_2F4304CD2335

#include <ccbase/platform.hpp>

/*
** This part defines the following utility macros:
**
** - `IMPORT_SYMBOL`
** - `EXPORT_SYMBOL`
** - `HIDDEN_SYMBOL`
*/

#if PLATFORM_KERNEL == PLATFORM_KERNEL_WINDOWS_NT
	#if PLATFORM_COMPILER == PLATFORM_COMPILER_COMEAU || \
	    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC    || \
            PLATFORM_COMPILER == PLATFORM_COMPILER_MINGW  || \
            PLATFORM_COMPILER == PLATFORM_COMPILER_MSVC   || \
            PLATFORM_COMPILER == PLATFORM_COMPILER_PGI
		#define IMPORT_SYMBOL __declspec(dllimport)
		#define EXPORT_SYMBOL __declspec(dllexport)
		#define HIDDEN_SYMBOL
	#elif PLATFORM_COMPILER == PLATFORM_COMPILER_GCC || \
	      PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG
		#define IMPORT_SYMBOL __attribute__((visibility("default")))
		#define EXPORT_SYMBOL __attribute__((visibility("default")))
		#define HIDDEN_SYMBOL __attribute__((visibility("hidden")))
	#else
		#error "Cannot determine symbol visibility syntax."
	#endif
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX || \
      PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG  || \
	    PLATFORM_COMPILER == PLATFORM_COMPILER_COMEAU || \
	    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC    || \
	    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC    || \
            PLATFORM_COMPILER == PLATFORM_COMPILER_PGI
		#define IMPORT_SYMBOL __attribute__((visibility("default")))
		#define EXPORT_SYMBOL __attribute__((visibility("default")))
		#define HIDDEN_SYMBOL __attribute__((visibility("hidden")))
	#else
		#error "Cannot determine symbol visibility syntax."
	#endif
#else
	#error "Cannot determine symbol visibility syntax."
#endif

/*
** This part defines the following macros:
**
** - `PUBLIC_SYMBOL`
** - `PRIVATE_SYMBOL`
**
** `PUBLIC_SYMBOL` expands to `IMPORT_SYMBOL` if `CCBASE_IMPORT_SYMBOLS` is
** defined, or `EXPORT_SYMBOL` if `CCBASE_EXPORT_SYMBOLS` is defined. If neither
** of the two macros is defined, then `PUBLIC_SYMBOL` expands to nothing.
** `PRIVATE_SYMBOL` expands to `HIDDEN_SYMBOL` if either of the two macros is
** defined, and nothing otherwise.
*/

#if defined CCBASE_IMPORT_SYMBOLS && defined CCBASE_EXPORT_SYMBOLS
	#error "Both CCBASE_IMPORT_SYMBOLS and CCBASE_EXPORT_SYMBOLS are defined."
#endif

#if defined CCBASE_IMPORT_SYMBOLS
	#define PUBLIC_SYMBOL IMPORT_SYMBOL
	#define PRIVATE_SYMBOL HIDDEN_SYMBOL
#elif defined CCBASE_EXPORT_SYMBOLS
	#define PUBLIC_SYMBOL EXPORT_SYMBOL
	#define PRIVATE_SYMBOL HIDDEN_SYMBOL
#else
	#define PUBLIC_SYMBOL
	#define PRIVATE_SYMBOL
#endif

#endif
