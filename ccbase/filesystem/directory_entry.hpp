/*
** File Name:	directory_entry.hpp
** Author:	Aditya Ramesh
** Date:	08/23/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZDDEA7CE4_14FD_40C7_AA27_9BBF59D67383
#define ZDDEA7CE4_14FD_40C7_AA27_9BBF59D67383

#include <cstdint>
#include <ccbase/platform.hpp>

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	#include <dirent.h>
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	#include <sys/dirent.h>
#else
	#error "Unsupported kernel."
#endif

namespace cc
{

enum class file_type : unsigned char
{
	block         = DT_BLK,
	character     = DT_CHR,
	directory     = DT_DIR,
	fifo          = DT_FIFO,
	symbolic_link = DT_LNK,
	regular       = DT_REG,
	socket        = DT_SOCK,
	unknown       = DT_UNKNOWN
};

class directory_iterator;

class directory_entry
{
private:
	friend class directory_iterator;

	using length_type = uint16_t;

	const directory_iterator* p;
	const char* n;
	const length_type len;
	const file_type t;

	directory_entry(
		const directory_iterator& p,
		const char* n,
		const length_type len,
		const file_type t
	) noexcept : p{&p}, n{n}, len{len}, t{t} {}
public:
	// Defined in `directory_iterator.hpp` due to cyclic dependencies.
	const char* path() const;
	const char* name() const { return n; }
	file_type type() const { return t; }
};

}

#endif
