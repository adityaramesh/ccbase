/*
** File Name:	bswap.hpp
** Author:	Aditya Ramesh
** Date:	04/14/2014
** Contact:	_@adityaramesh.com
*/

#ifndef Z2C1D91E3_6CC1_415A_A95D_65604B557F77
#define Z2C1D91E3_6CC1_415A_A95D_65604B557F77

#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <ccbase/platform/attributes.hpp>
#include <ccbase/platform/identification.hpp>

#if !(PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
      PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
      PLATFORM_COMPILER == PLATFORM_COMPILER_ICC)
	#warning "Unsupported compiler for cc::bswap."
	#warning "The operation will not use intrinsics."
#endif

namespace cc {

CC_ALWAYS_INLINE int8_t bswap(int8_t x) noexcept { return x; }

CC_ALWAYS_INLINE int16_t
bswap(int16_t x) noexcept
{
#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	return __builtin_bswap16(x);
#else
	return ((x & 0xFF) << 8) | ((x & 0xFF00) >> 8);
#endif
}

CC_ALWAYS_INLINE
int32_t bswap(int32_t x) noexcept
{
#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	return __builtin_bswap32(x);
#else
	return ((x & 0xFF) << 24) |
	       ((x & 0xFF00) << 8) |
	       ((x & 0xFF0000) >> 8) | 
	       ((x & 0xFF0000000) >> 24);
#endif
}

CC_ALWAYS_INLINE
int64_t bswap(int64_t x) noexcept
{
#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	return __builtin_bswap64(x);
#else
	return ((x & 0xFF) << 56) |
	       ((x & 0xFF00) << 40) |
	       ((x & 0xFF0000) << 24) |
	       ((x & 0xFF000000) << 8) |
	       ((x & 0xFF00000000) >> 8) |
	       ((x & 0xFF0000000000) >> 24) |
	       ((x & 0xFF000000000000) >> 40) |
	       ((x & 0xFF00000000000000) >> 56);
#endif
}

CC_ALWAYS_INLINE uint8_t bswap(uint8_t x) noexcept { return x; }

CC_ALWAYS_INLINE uint16_t
bswap(uint16_t x) noexcept
{
#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	return __builtin_bswap16(x);
#else
	return ((x & 0xFF) << 8) | ((x & 0xFF00) >> 8);
#endif
}

CC_ALWAYS_INLINE
uint32_t bswap(uint32_t x) noexcept
{
#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	return __builtin_bswap32(x);
#else
	return ((x & 0xFF) << 24) |
	       ((x & 0xFF00) << 8) |
	       ((x & 0xFF0000) >> 8) | 
	       ((x & 0xFF0000000) >> 24);
#endif
}

CC_ALWAYS_INLINE
uint64_t bswap(uint64_t x) noexcept
{
#if PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	return __builtin_bswap64(x);
#else
	return ((x & 0xFF) << 56) |
	       ((x & 0xFF00) << 40) |
	       ((x & 0xFF0000) << 24) |
	       ((x & 0xFF000000) << 8) |
	       ((x & 0xFF00000000) >> 8) |
	       ((x & 0xFF0000000000) >> 24) |
	       ((x & 0xFF000000000000) >> 40) |
	       ((x & 0xFF00000000000000) >> 56);
#endif
}

CC_ALWAYS_INLINE
auto bswap(float x) noexcept ->
std::enable_if<sizeof(float) == 4, float>::type
{
	auto buf = uint32_t{};
	std::copy_n((char*)&x, sizeof(float), (char*)&buf);
	return bswap(buf);
}

CC_ALWAYS_INLINE
auto bswap(double x) noexcept ->
std::enable_if<sizeof(double) == 8, double>::type
{
	auto buf = uint64_t{};
	std::copy_n((char*)&x, sizeof(double), (char*)&buf);
	return bswap(buf);
}

}

#endif
