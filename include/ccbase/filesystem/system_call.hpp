/*
** File Name:	system_call.hpp
** Author:	Aditya Ramesh
** Date:	08/27/2013
** Contact:	_@adityaramesh.com
**
** Documentation for Linux system calls is readily available. Documentation for
** XNU system calls is available [here][xnu_syscalls].
**
** [xnu_syscalls]:
** http://www.opensource.apple.com/source/xnu/xnu-1504.3.12/bsd/kern/syscalls.master
** "XNU System Calls"
*/

#ifndef Z6C7E2BB5_EFCF_4AFF_9752_571AF3EDF467
#define Z6C7E2BB5_EFCF_4AFF_9752_571AF3EDF467

#include <cstdint>
#include <ccbase/platform.hpp>

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	#include <sys/syscall.h>
	#include <sys/types.h>
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	// For `user_size_t` and `user_ssize_t`.
	#include <unistd.h>
	#include <machine/types.h>
	#include <sys/syscall.h>
	#include <sys/types.h>
#else
	#error "Unsupported kernel."
#endif

namespace cc {

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX

CC_ALWAYS_INLINE int
getdents(unsigned fd, char* buf, unsigned n)
noexcept
{
	return ::syscall(SYS_getdents, fd, buf, n);
}

#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU

CC_ALWAYS_INLINE user_ssize_t
getdirentries64(int fd, char* buf, user_size_t n, off_t* pos)
noexcept
{
	return ::syscall(SYS_getdirentries64, fd, buf, n, pos);
}

#endif

}

#endif
