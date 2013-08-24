/*
** File Name:	listing.cpp
** Author:	Aditya Ramesh
** Date:	08/24/2013
** Contact:	_@adityaramesh.com
*/

// POSIX open.
#include <fcntl.h>
// POSIX close.
#include <unistd.h>
// System call number for `getdents`.
#include <sys/syscall.h>
// POSIX stat.
#include <sys/stat.h>
// For defining linux_dirent.
#include <cstdint>

// For perror. We do not need this in the library.
#include <stdio.h>

#include <algorithm>
#include <array>
#include <memory>
#include <ccbase/format.hpp>

struct linux_dirent
{
	uint64_t d_ino;
	uint64_t d_off;
	uint16_t d_reclen;
	uint8_t  d_name[];
	/*
	** Although there are more fields after d_name, it does not do any good
	** to declare them here, because they can only be accessed after we know
	** d_reclen.
	*/
};

static CC_ALWAYS_INLINE int
getdents(unsigned fd, const char* buf, unsigned n)
{
	return ::syscall(SYS_getdents, fd, buf, n);
}

int main()
{
	auto fd = ::open("/home/aditya", O_RDONLY);
	if (fd < 0) {
		::perror(nullptr);
		cc::fail("Failed to open directory.");
	}

	struct stat s;
	if (::fstat(fd, &s) == -1) {
		::perror(nullptr);
		cc::fail("Failed to stat directory.");
	}
	cc::println("Directory file size: $0.", s.st_size);
	cc::println("Blocks allocated: $0.", s.st_blocks);
	cc::println("IO blocksize: $0.\n", s.st_blksize);

	// When returning an expected object with std::system_error, use
	// strerror or strerror_r to get the error string.
	// https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man3/strerror.3.html
	
	auto n   = std::max(s.st_size, s.st_blocks);
	auto buf = std::unique_ptr<char[]>{new char[n]};
	auto i   = 1u;
	ssize_t r;

	while ((r = getdents(fd, buf.get(), n)) > 0) {
		auto p = buf.get();
		auto l = buf.get() + r;
		do {
			auto e = (::linux_dirent*)p;
			auto t = *(char*)(p + e->d_reclen - 1);
			p += e->d_reclen;
			if (e->d_ino != 0) {
				cc::println("Entry $0.", i);
				cc::println("File number: $0.", e->d_ino); 
				cc::println("Seek offset: $0.", e->d_off);
				cc::println("Record length: $0.", e->d_reclen);
				cc::println("Type: $0.", (unsigned)t);
				cc::println("Name: \"$0\".\n", e->d_name);
				++i;
			}
		}
		while (p < l);
	}

	if (r == -1) {
		::perror(nullptr);
		cc::fail("Failed to enumerate entries.");
	}

	if (::close(fd) == -1) {
		::perror(nullptr);
		cc::fail("Failed to close directory.");
	}
}
