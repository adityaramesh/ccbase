/*
** File Name:	platform.hpp
** Author:	Aditya Ramesh
** Date:	06/30/2013
** Contact:	_@adityaramesh.com
**
** This header defines a static class called `platform` with various constants
** defined based on the information available from the preprocessor.  The
** information used to create this header was taken from [this
** website](http://sourceforge.net/p/predef/wiki/).
*/

#ifndef Z559D8FFC_E3C4_459B_BFFD_063900DAAF55
#define Z559D8FFC_E3C4_459B_BFFD_063900DAAF55

namespace cc
{

#define PLATFORM_COMPILER_CLANG   1
#define PLATFORM_COMPILER_COMEAU  2
#define PLATFORM_COMPILER_GCC     3
#define PLATFORM_COMPILER_ICC     4
#define PLATFORM_COMPILER_MINGW   5
#define PLATFORM_COMPILER_MSVC    6
#define PLATFORM_COMPILER_PGI     7

#define PLATFORM_ARCH_ARM       1
#define PLATFORM_ARCH_BLACKFIN  2
#define PLATFORM_ARCH_ITANIUM   3
#define PLATFORM_ARCH_MOTOROLA  4
#define PLATFORM_ARCH_MIPS      5
#define PLATFORM_ARCH_POWER_PC  6
#define PLATFORM_ARCH_SPARC     7
#define PLATFORM_ARCH_SYSTEM_Z  8
#define PLATFORM_ARCH_X86       9

#define PLATFORM_OS_LINUX_DISTRIBUTION 1
#define PLATFORM_OS_MACOS              2
#define PLATFORM_OS_WINDOWS            3

#define PLATFORM_KERNEL_LINUX      1
#define PLATFORM_KERNEL_MACH       2
#define PLATFORM_KERNEL_WINDOWS_NT 3

#define PLATFORM_BYTE_ORDER_LITTLE      1
#define PLATFORM_BYTE_ORDER_BIG         2
#define PLATFORM_BYTE_ORDER_LITTLE_WORD 3

enum system
{
	// Compiler
	clang,
	comeau,
	gcc,
	icc,
	mingw,
	msvc,
	pgi,

	// Architecture
	arm,
	blackfin,
	itanium,
	motorola,
	mips,
	power_pc,
	sparc,
	system_z,
	x86,

	// ABI
	bits_32,
	bits_64,
	
	// OS
	linux_distribution,
	macos,
	windows,

	// Kernel
	linux,
	mach,
	windows_nt,

	// Byte order
	little,
	big,
	little_word,
	
	// Common
	unknown
};

#define count(...) \
	count_impl(__VA_ARGS__, \
		20, 19, 18, 17, 16, 15, 14, 13, 12, \
		11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 \
	)

#define count_impl( \
	_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, \
	_12, _13, _14, _15, _16, _17, _18, _19, _20, \
	n, ... \
) n

#define sum(...) sum_impl_1(count(__VA_ARGS__), __VA_ARGS__)
#define sum_impl_1(count, ...) sum_impl_2(count, __VA_ARGS__)
#define sum_impl_2(count, ...) sum_ ## count(__VA_ARGS__)

#define sum_20(arg, ...) arg + sum_19(__VA_ARGS__)
#define sum_19(arg, ...) arg + sum_18(__VA_ARGS__)
#define sum_18(arg, ...) arg + sum_17(__VA_ARGS__)
#define sum_17(arg, ...) arg + sum_16(__VA_ARGS__)
#define sum_16(arg, ...) arg + sum_15(__VA_ARGS__)
#define sum_15(arg, ...) arg + sum_14(__VA_ARGS__)
#define sum_14(arg, ...) arg + sum_13(__VA_ARGS__)
#define sum_13(arg, ...) arg + sum_12(__VA_ARGS__)
#define sum_12(arg, ...) arg + sum_11(__VA_ARGS__)
#define sum_11(arg, ...) arg + sum_10(__VA_ARGS__)
#define sum_10(arg, ...) arg + sum_9(__VA_ARGS__)
#define sum_9(arg, ...)  arg + sum_8(__VA_ARGS__)
#define sum_8(arg, ...)  arg + sum_7(__VA_ARGS__)
#define sum_7(arg, ...)  arg + sum_6(__VA_ARGS__)
#define sum_6(arg, ...)  arg + sum_5(__VA_ARGS__)
#define sum_5(arg, ...)  arg + sum_4(__VA_ARGS__)
#define sum_4(arg, ...)  arg + sum_3(__VA_ARGS__)
#define sum_3(arg, ...)  arg + sum_2(__VA_ARGS__)
#define sum_2(arg, ...)  arg + sum_1(__VA_ARGS__)
#define sum_1(arg)       arg

struct platform
{

/*
** Determine compiler.
*/

#if defined __clang__
	#define compiler_value    clang
	#define compiler_clang    1
	#define PLATFORM_COMPILER PLATFORM_COMPILER_CLANG
#endif

#if defined __COMO__
	#define compiler_value    comeau
	#define compiler_comeau   1
	#define PLATFORM_COMPILER PLATFORM_COMPILER_COMEAU
#endif

#if defined __GNUC__ && !defined __clang__
	#define compiler_value    gcc
	#define compiler_gcc      1
	#define PLATFORM_COMPILER PLATFORM_COMPILER_GCC
#endif

#if defined __INTEL_COMPILER || defined __ICL
	#define compiler_value    icc
	#define compiler_icc      1
	#define PLATFORM_COMPILER PLATFORM_COMPILER_ICC
#endif

#if defined __MINGW32__ || defined __MINGW64__
	#define compiler_value    mingw
	#define compiler_mingw    1
	#define PLATFORM_COMPILER PLATFORM_COMPILER_MINGW
#endif

#if defined _MSC_VER
	#define compiler_value    msvc
	#define compiler_msvc     1
	#define PLATFORM_COMPILER PLATFORM_COMPILER_MSVC
#endif

#if defined __PGI
	#define compiler_value    pgi
	#define compiler_pgi      1
	#define PLATFORM_COMPILER PLATFORM_COMPILER_PGI
#endif

#define compiler_list \
	compiler_clang, compiler_comeau, compiler_gcc, compiler_icc, \
	compiler_mingw, compiler_msvc, compiler_pgi

#if sum(compiler_list) > 1
	#error "Conflicting compiler macros defined."
#elif sum(compiler_list) == 1
	static constexpr auto compiler = compiler_value;
#else
	static constexpr auto compiler = unknown;
#endif

#undef compiler_value
#undef compiler_list
#undef compiler_clang
#undef compiler_comeau
#undef compiler_gcc
#undef compiler_icc
#undef compiler_mingw
#undef compiler_msvc
#undef compiler_pgi

/*
** Determine architecture.
*/

#if defined __arm__ || defined __thumb__ || defined _TARGET_ARCH_ARM || \
    defined __TARGET_ARCH_THUMB || defined _ARM || defined _M_ARM || \
    defined _M_ARMT || defined __aarch64__
	#define arch_value    arm
	#define	arch_arm      1
	#define PLATFORM_ARCH PLATFORM_ARCH_ARM
#endif

#if defined _bfin || defined __BFIN__
	#define arch_value    blackfin
	#define	arch_blackfin 1
	#define PLATFORM_ARCH PLATFORM_ARCH_BLACKFIN
#endif

#if defined __ia64__ || defined _IA64 || defined __IA64__ || defined __ia64 || \
    defined _M_IA64 || defined __itanium__
	#define arch_value    itanium
	#define arch_itanium  1
	#define PLATFORM_ARCH PLATFORM_ARCH_ITANIUM
#endif

#if defined __m68k__ || defined M68000 || defined __MC68k__
	#define arch_value    motorola
	#define	arch_motorola 1
	#define PLATFORM_ARCH PLATFORM_ARCH_MOTOROLA
#endif

#if defined __mips__ || defined mips || defined _MIPS_ISA || defined __mips || \
    defined __MIPS__
	#define arch_value    mips
	#define	arch_mips     1
	#define PLATFORM_ARCH PLATFORM_ARCH_MIPS
#endif

#if defined __powerpc || defined __powerpc__ || defined __powerpc64__ || \
    defined __POWERPC__ || defined __ppc__ || defined __ppc64__ || \
    defined _M_PPC || defined _ARCH_PPC || defined __PPCGECKO__ || \
    defined __PPCBROADWAY__ || defined _XENON
	#define arch_value    powerpc
	#define	arch_power_pc 1
	#define PLATFORM_ARCH PLATFORM_ARCH_POWERPC
#endif

#if defined __sparc__ || defined __sparc || defined __sparcv8 || \
    defined __sparcv9
	#define arch_value    sparc
	#define	arch_sparc    1
	#define PLATFORM_ARCH PLATFORM_ARCH_SPARC
#endif

#if defined __370__ || defined __THW_370__ || defined __s390__ || \
    defined __s390x__ || defined __zarch__ || defined __SYSC_ZARCH__
	#define arch_value    system_z
	#define	arch_system_z 1
	#define PLATFORM_ARCH PLATFORM_ARCH_SYSTEM_Z
#endif

#if defined i386 || defined __i386 || defined __i386__ || defined __i486__ || \
    defined __i586__ || defined __i686__ || defined __IA32__ || \
    defined _M_I86 || defined _M_IX86 || defined __X86__ || defined _X86_ || \
    defined __THW_INTEL__ || defined __I86__ || defined __INTEL__ || \
    defined __amd64__ || defined __amd64 || defined __x86_64__ || \
    defined __x86_64 || defined _M_X64 || defined _M_AMD64
	#define arch_value    x86
	#define	arch_x86      1
	#define PLATFORM_ARCH PLATFORM_ARCH_X86
#endif

#define arch_list \
	arch_arm, arch_blackfin, arch_itanium, arch_motorola, arch_mips, \
	arch_power_pc, arch_sparc, arch_system_z, arch_x86

#if sum(arch_list) > 1
	#error "Conflicting host architecture macros are defined."
#elif sum(arch_list) == 1
	static constexpr auto arch = arch_value;
#else
	static constexpr auto arch = unknown;
#endif

#undef arch_value
#undef arch_list
#undef arch_arm
#undef arch_blackfin
#undef arch_itanium
#undef arch_motorola
#undef arch_mips
#undef arch_power_pc
#undef arch_sparc
#undef arch_system_z
#undef arch_x86

/*
** Determine ABI.
*/

#if defined _ILP32 || defined __ILP32__
	#define abi_value    bits_32
	#define abi_32       1
	#define PLATFORM_ABI 32
#endif

#if defined _LP64 || defined __LP64__
	#define abi_value    bits_64
	#define abi_64       1
	#define PLATFORM_ABI 64
#endif

#if sum(abi_32, abi_64) > 1
	#error "Conflicting ABI macros are defined."
#elif sum(abi_32, abi_64) == 1
	static constexpr auto abi = abi_value;
#else
	static constexpr auto abi = unknown;
#endif

#undef abi_value
#undef abi_32
#undef abi_64

/*
** Determine operating system and kernel.
*/

#if defined __linux__
	#define os_value              linux_distribution
	#define os_linux_distribution 1
	#define kernel_value          linux
	#define kernel_linux          1
	#define PLATFORM_OS           PLATFORM_OS_LINUX_DISTRIBUTION
	#define PLATFORM_KERNEL       PLATFORM_KERNEL_LINUX
#endif

#if defined __MACH__
	#define kernel_value    mach
	#define kernel_mach     1
	#define PLATFORM_KERNEL MACH
#endif

#if defined __APPLE__
	#define os_value    macos
	#define os_macos    1
	#define PLATFORM_OS PLATFORM_OS_MACOS
#endif

#if defined _WIN16 || defined _WIN32 || defined _WIN64 || defined __WIN32__ || \
    defined __TOS_WIN__ || defined __WINDOWS__
	#define os_value          windows
	#define os_windows        1
	#define kernel_value      windows_nt
	#define kernel_windows_nt 1
	#define PLATFORM_OS       PLATFORM_OS_WINDOWS
	#define PLATFORM_KERNEL   PLATFORM_KERNEL_WINDOWS_NT
#endif

#define os_list os_linux_distribution, os_macos, os_windows
#define kernel_list kernel_linux, kernel_mach, kernel_windows_nt

#if sum(os_list) > 1
	#error "Conflicting OS macros are defined."
#elif sum(os_list) == 1
	static constexpr auto os = os_value;
#else
	static constexpr auto os = unknown;
#endif

#if sum(kernel_list) > 1
	#error "Conflicting kernel macros are defined."
#elif sum(kernel_list) == 1
	static constexpr auto kernel = kernel_value;
#else
	static constexpr auto kernel = unknown;
#endif

#undef os_value
#undef os_list
#undef kernel_value
#undef kernel_list
#undef os_linux_distribution
#undef os_macos
#undef os_windows
#undef kernel_linux
#undef kernel_mach
#undef kernel_windows_nt

/*
** Determine byte order.
*/

#if PLATFORM_COMPILER == PLATFORM_COMPILER_GCC || \
    PLATFORM_COMPILER == PLATFORM_COMPILER_CLANG
	#ifdef __BYTE_ORDER__
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			#define integer_byte_order_value    little
			#define integer_byte_order_little   1
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE_ENDIAN
		#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			#define integer_byte_order_value    big
			#define integer_byte_order_big      1
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_BIG_ENDIAN
		#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
			#define integer_byte_order_value       little_word
			#define integer_byte_order_little_word 1
			#define PLATFORM_INTEGER_BYTE_ORDER    PLATFORM_BYTE_ORDER_LITTLE_WORD
		#endif
	#endif
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	#include <sys/param.h>

	#ifdef __BYTE_ORDER
		#if __BYTE_ORDER == __LITTLE_ENDIAN
			#define integer_byte_order_value    little
			#define integer_byte_order_little   1
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE_ENDIAN
		#elif __BYTE_ORDER == __BIG_ENDIAN
			#define integer_byte_order_value    big
			#define integer_byte_order_big      1
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_BIG_ENDIAN
		#elif __BYTE_ORDER == __PDP_ENDIAN
			#define integer_byte_order_value       little_word
			#define integer_byte_order_little_word 1
			#define PLATFORM_INTEGER_BYTE_ORDER    PLATFORM_BYTE_ORDER_LITTLE_WORD
		#endif
	#endif
#elif PLATFORM_OS == PLATFORM_OS_MACOS
	#include <machine/endian.h>

	#ifdef BYTE_ORDER
		#if BYTE_ORDER == LITTLE_ENDIAN
			#define integer_byte_order_value    little
			#define integer_byte_order_little   1
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_LITTLE_ENDIAN
		#elif BYTE_ORDER == BIG_ENDIAN
			#define integer_byte_order_value    big
			#define integer_byte_order_big      1
			#define PLATFORM_INTEGER_BYTE_ORDER PLATFORM_BYTE_ORDER_BIG_ENDIAN
		#elif BYTE_ORDER == PDP_ENDIAN
			#define integer_byte_order_value       little_word
			#define integer_byte_order_little_word 1
			#define PLATFORM_INTEGER_BYTE_ORDER    PLATFORM_BYTE_ORDER_LITTLE_WORD
		#endif
	#endif
#endif

#define integer_byte_order_list \
	integer_byte_order_little, integer_byte_order_big, \
	integer_byte_order_little_word

#if sum(integer_byte_order_list) > 1
	#error "Conflicting byte order macros defined."
#elif sum(integer_byte_order_list) == 1
	static constexpr auto integer_byte_order = integer_byte_order_value;
#else
	static constexpr auto integer_byte_order = unknown;
#endif

#undef integer_byte_order_value
#undef integer_byte_order_list
#undef byte_order_little
#undef byte_order_big
#undef byte_order_little_word

};

}

#undef count
#undef count_impl
#undef sum
#undef sum_impl_1
#undef sum_impl_2
#undef sum_1
#undef sum_2
#undef sum_3
#undef sum_4
#undef sum_5
#undef sum_6
#undef sum_7
#undef sum_8
#undef sum_9
#undef sum_10
#undef sum_11
#undef sum_12
#undef sum_13
#undef sum_14
#undef sum_15
#undef sum_16
#undef sum_17
#undef sum_18
#undef sum_19
#undef sum_20

#endif
