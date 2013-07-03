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

CC_BEGIN_MODULE(test_support)
	CC_ASSERT(platform_compiler);
	CC_ASSERT(platform_arch);
	CC_ASSERT(platform_os);
	CC_ASSERT(platform_kernel);
	CC_ASSERT(platform_integer_byte_order);
	CC_ASSERT(platform_newline);
CC_END_MODULE(test_support)

CC_BEGIN_SUITE(platform_test)
	test_support();
CC_END_SUITE(platform_test)
