/*
** File Name:	platform_test.cpp
** Author:	Aditya Ramesh
** Date:	07/03/2013
** Contact:	_@adityaramesh.com
*/

#include <ccbase/platform.hpp>
#include <ccbase/unit_test.hpp>

#if defined(PLATFORM_COMPILER)
	#define platform_compiler 1
#else
	#define platform_compiler 0
#endif

#if defined(PLATFORM_ARCH)
	#define platform_arch 1
#else
	#define platform_arch 0
#endif

#if defined(PLATFORM_OS)
	#define platform_os 1
#else
	#define platform_os 0
#endif

#if defined(PLATFORM_KERNEL)
	#define platform_kernel 1
#else
	#define platform_kernel 0
#endif

#if defined(PLATFORM_INTEGER_BYTE_ORDER)
	#define platform_integer_byte_order 1
#else
	#define platform_integer_byte_order 0
#endif

#if defined(PLATFORM_NEWLINE)
	#define platform_newline 1
#else
	#define platform_newline 0
#endif

#if defined(PLATFORM_MAX_FILENAME_LENGTH)
	#define platform_max_filename_length 1
#else
	#define platform_max_filename_length 0
#endif

#if defined(PLATFORM_MAX_PATHNAME_LENGTH)
	#define platform_max_pathname_length 1
#else
	#define platform_max_pathname_length 0
#endif

module("test_support")
{
	require(platform_compiler);
	require(platform_arch);
	require(platform_os);
	require(platform_kernel);
	require(platform_integer_byte_order);
	require(platform_newline);
	require(platform_max_filename_length);
	require(platform_max_pathname_length);
}

suite("Tests whether the platform identification features work on this platform.")
