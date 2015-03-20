/*
** File Name:	yield_execution.hpp
** Author:	Aditya Ramesh
** Date:	06/27/2014
** Contact:	_@adityaramesh.com
*/

#ifndef Z425AA799_443A_40AD_B54F_913A3DF4F33D
#define Z425AA799_443A_40AD_B54F_913A3DF4F33D

#include <cstdint>
#include <type_traits>
#include <ccbase/platform/attributes.hpp>

#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	#include <immintrin.h>
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_MSVC
	#include <windows.h>
#else
	#warning "Unsupported compiler for cc::yield_execution."
	#warning "The function will be a no-op."
#endif

namespace cc {

CC_ALWAYS_INLINE
void yield_execution() noexcept
{
#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	_mm_pause();
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_MSVC
	::YieldProcessor();
#endif
}

}

#endif
