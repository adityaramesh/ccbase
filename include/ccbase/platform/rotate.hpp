/*
** File Name: rotate.hpp
** Author:    Aditya Ramesh
** Date:      03/20/2015
** Contact:   _@adityaramesh.com
**
** XXX: Clang seems to be buggy in compiling the inline assembly below in
** certain situations.
*/

#ifndef ZC5D2A64A_2B75_4209_B5EE_48410B26BFAE
#define ZC5D2A64A_2B75_4209_B5EE_48410B26BFAE

#include <type_traits>
#include <ccbase/platform/attributes.hpp>
#include <ccbase/platform/identification.hpp>

#if !(PLATFORM_ARCH == PLATFORM_ARCH_X86 &&           \
     (PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
      PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
      PLATFORM_COMPILER == PLATFORM_COMPILER_ICC))
	#warning "Unsupported platform for cc::rotl and cc::rotr."
	#warning "The operation will not use intrinsics."
#endif

namespace cc {

#if  (PLATFORM_ARCH == PLATFORM_ARCH_X86 &&           \
     (PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG || \
      PLATFORM_COMPILER == PLATFORM_COMPILER_GCC   || \
      PLATFORM_COMPILER == PLATFORM_COMPILER_ICC))

template <
	class Integer,
	typename std::enable_if<
		std::is_unsigned<Integer>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE
uint8_t rotl(uint8_t x, Integer shift)
noexcept
{
	auto res = uint8_t{};
	asm("rolb %%cl, %0"
		: "=r" (res)
		: "c" (shift), "0" (x)
	);
	return res;
}

template <
	class Integer,
	typename std::enable_if<
		std::is_unsigned<Integer>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE
uint16_t rotl(uint16_t x, Integer shift)
noexcept
{
	auto res = uint16_t{};
	asm("rolw %%cl, %0"
		: "=r" (res)
		: "c" (shift), "0" (x)
	);
	return res;
}

template <
	class Integer,
	typename std::enable_if<
		std::is_unsigned<Integer>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE
uint32_t rotl(uint32_t x, Integer shift)
noexcept
{
	auto res = uint32_t{};
	asm("roll %%cl, %0"
		: "=r" (res)
		: "c" (shift), "0" (x)
	);
	return res;
}

template <
	class Integer,
	typename std::enable_if<
		std::is_unsigned<Integer>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE
uint64_t rotl(uint64_t x, Integer shift)
noexcept
{
	auto res = uint64_t{};
	asm("rolq %%cl, %0"
		: "=r" (res)
		: "c" (shift), "0" (x)
	);
	return res;
}

template <
	class Integer,
	typename std::enable_if<
		std::is_unsigned<Integer>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE
uint8_t rotr(uint8_t x, Integer shift)
noexcept
{
	auto res = uint8_t{};
	asm("rorb %%cl, %0"
		: "=r" (res)
		: "c" (shift), "0" (x)
	);
	return res;
}

template <
	class Integer,
	typename std::enable_if<
		std::is_unsigned<Integer>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE
uint16_t rotr(uint16_t x, Integer shift)
noexcept
{
	auto res = uint16_t{};
	asm("rorw %%cl, %0"
		: "=r" (res)
		: "c" (shift), "0" (x)
	);
	return res;
}

template <
	class Integer,
	typename std::enable_if<
		std::is_unsigned<Integer>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE
uint32_t rotr(uint32_t x, Integer shift)
noexcept
{
	auto res = uint32_t{};
	asm("rorl %%cl, %0"
		: "=r" (res)
		: "c" (shift), "0" (x)
	);
	return res;
}

template <
	class Integer,
	typename std::enable_if<
		std::is_unsigned<Integer>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE
uint64_t rotr(uint64_t x, Integer shift)
noexcept
{
	auto res = uint64_t{};
	asm("rorq %%cl, %0"
		: "=r" (res)
		: "c" (shift), "0" (x)
	);
	return res;
}

#else

template <
	class Integer1,
	class Integer2,
	typename std::enable_if<
		std::is_unsigned<Integer1>::value &&
		std::is_unsigned<Integer2>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE constexpr
Integer1 unsafe_rotl(Integer1 x, Integer2 shift)
noexcept
{
	return (x << shift) | (x >> (8 * sizeof(Integer1) - shift));
}

template <
	class Integer1,
	class Integer2,
	typename std::enable_if<
		std::is_unsigned<Integer1>::value &&
		std::is_unsigned<Integer2>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE constexpr
Integer1 unsafe_rotr(Integer1 x, Integer2 shift)
noexcept
{
	return (x >> shift) | (x << (8 * sizeof(Integer1) - shift));
}

template <
	class Integer1,
	class Integer2,
	typename std::enable_if<
		std::is_unsigned<Integer1>::value &&
		std::is_unsigned<Integer2>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE constexpr
Integer1 rotl(Integer1 x, Integer2 shift)
noexcept
{
	return unsafe_rotl(x, shift % (sizeof(Integer1) - 1));
}

template <
	class Integer1,
	class Integer2,
	typename std::enable_if<
		std::is_unsigned<Integer1>::value &&
		std::is_unsigned<Integer2>::value, int
	>::type = 0
>
CC_ALWAYS_INLINE constexpr
Integer1 rotr(Integer1 x, Integer2 shift)
noexcept
{
	return unsafe_rotr(x, shift % (sizeof(Integer1) - 1));
}

#endif

}

#endif
