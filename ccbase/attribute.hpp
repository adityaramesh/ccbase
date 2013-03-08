/*
** File Name:	attribute.hpp
** Author:	Aditya Ramesh
** Date:	12/25/2012
** Contact:	_@adityaramesh.com
*/

#ifndef ZF27C7D32_9AB4_45CF_97E5_F4103C824B40
#define ZF27C7D32_9AB4_45CF_97E5_F4103C824B40

#if defined(__GNUG__) || defined(__clang__)
	#define XU_ALWAYS_INLINE __attribute__((always_inline))
	#define XU_NEVER_INLINE  __attribute__((noinline))
	#define XU_CONST         __attribute__((const))
	#define XU_PURE          __attribute__((pure))
	#define XU_UNUSED        __attribute__((unused))
	#define XU_RESTRICT      __restrict__
#elif defined(__INTEL_COMPILER)
	#define XU_ALWAYS_INLINE __attribute__((always_inline))
	#define XU_NEVER_INLINE  __attribute__((noinline))
	#define XU_CONST         __attribute__((const))
	#define XU_PURE          __attribute__((pure))
	#define XU_UNUSED        __attribute__((unused))
	#define XU_RESTRICT      restrict
#elif defined(_MSC_VER)
	#define XU_ALWAYS_INLINE __forceinline
	#define XU_NEVER_INLINE  __declspec(noinline)
	#define XU_CONST
	#define XU_PURE
	#define XU_UNUSED
	#define XU_RESTRICT      __restrict
#endif

#endif
