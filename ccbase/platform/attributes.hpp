/*
** File Name:	attributes.hpp
** Author:	Aditya Ramesh
** Date:	12/25/2012
** Contact:	_@adityaramesh.com
*/

#ifndef ZF27C7D32_9AB4_45CF_97E5_F4103C824B40
#define ZF27C7D32_9AB4_45CF_97E5_F4103C824B40

#include <ccbase/platform/identification.hpp>

#if PLATFORM_COMPILER == PLATFORM_COMPILER_GCC
	#define CC_ALWAYS_INLINE __attribute__((always_inline)) inline
	#define CC_NEVER_INLINE  __attribute__((noinline))
	#define CC_CONST         __attribute__((const))
	#define CC_PURE          __attribute__((pure))
	#define CC_UNUSED        __attribute__((unused))
	#define CC_RESTRICT      __restrict__
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG
	#define CC_ALWAYS_INLINE __attribute__((always_inline))
	#define CC_NEVER_INLINE  __attribute__((noinline))
	#define CC_CONST         __attribute__((const))
	#define CC_PURE          __attribute__((pure))
	#define CC_UNUSED        __attribute__((unused))
	#define CC_RESTRICT      __restrict__
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_ICC
	#define CC_ALWAYS_INLINE __attribute__((always_inline))
	#define CC_NEVER_INLINE  __attribute__((noinline))
	#define CC_CONST         __attribute__((const))
	#define CC_PURE          __attribute__((pure))
	#define CC_UNUSED        __attribute__((unused))
	#define CC_RESTRICT      restrict
#elif PLATFORM_COMPILER == PLATFORM_COMPILER_MSVC
	#define CC_ALWAYS_INLINE __forceinline
	#define CC_NEVER_INLINE  __declspec(noinline)
	#define CC_CONST
	#define CC_PURE
	#define CC_UNUSED
	#define CC_RESTRICT      __restrict
#else
	#define CC_ALWAYS_INLINE
	#define CC_NEVER_INLINE
	#define CC_CONST
	#define CC_PURE
	#define CC_UNUSED
	#define CC_RESTRICT
#endif

#endif
