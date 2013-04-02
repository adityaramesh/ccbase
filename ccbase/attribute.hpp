/*
** File Name:	attribute.hpp
** Author:	Aditya Ramesh
** Date:	12/25/2012
** Contact:	_@adityaramesh.com
*/

#ifndef ZF27C7D32_9AB4_45CF_97E5_F4103C824B40
#define ZF27C7D32_9AB4_45CF_97E5_F4103C824B40

#if defined(__GNUG__) || defined(__clang__)
	#define CC_ALWAYS_INLINE __attribute__((always_inline))
	#define CC_NEVER_INLINE  __attribute__((noinline))
	#define CC_CONST         __attribute__((const))
	#define CC_PURE          __attribute__((pure))
	#define CC_UNUSED        __attribute__((unused))
	#define CC_RESTRICT      __restrict__
#elif defined(__INTEL_COMPILER)
	#define CC_ALWAYS_INLINE __attribute__((always_inline))
	#define CC_NEVER_INLINE  __attribute__((noinline))
	#define CC_CONST         __attribute__((const))
	#define CC_PURE          __attribute__((pure))
	#define CC_UNUSED        __attribute__((unused))
	#define CC_RESTRICT      restrict
#elif defined(_MSC_VER)
	#define CC_ALWAYS_INLINE __forceinline
	#define CC_NEVER_INLINE  __declspec(noinline)
	#define CC_CONST
	#define CC_PURE
	#define CC_UNUSED
	#define CC_RESTRICT      __restrict
#endif

#endif
