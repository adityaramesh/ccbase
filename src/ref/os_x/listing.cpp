/*
** File Name:	darwin_listing.cpp
** Author:	Aditya Ramesh
** Date:	08/24/2013
** Contact:	_@adityaramesh.com
*/

// POSIX open.
#include <fcntl.h>
// POSIX close.
#include <unistd.h>
// Syscall number for `getdirentries64`.
#include <sys/syscall.h>
// Definition of struct dirent and file type macros.
#include <sys/dirent.h>
// POSIX stat.
#include <sys/stat.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <ccbase/format.hpp>
#include <ccbase/platform.hpp>

static CC_ALWAYS_INLINE ssize_t
getdirentries64(int fd, char* buf, size_t n, off_t* pos)
{
	return ::syscall(SYS_getdirentries64, fd, buf, n, pos);
}

int main()
{
	auto fd = ::open("/Users/aditya", O_RDONLY);
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
	auto bp  = off_t{0};
	auto i   = 1u;
	ssize_t r;

	while ((r = getdirentries64(fd, buf.get(), n, &bp)) > 0) {
		auto p = buf.get();
		auto l = buf.get() + r;
		do {
			auto e = (::dirent*)p;
			cc::println("Entry $0.", i);
			cc::println("File number: $0.", e->d_ino); 
			cc::println("Seek offset: $0.", e->d_seekoff);
			cc::println("Record length: $0.", e->d_reclen);
			cc::println("Name length: $0.", e->d_namlen);
			cc::println("Type: $0.", (unsigned)e->d_type);
			cc::println("Name: \"$0\".\n", e->d_name);
			++i;
			p += e->d_reclen;
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
