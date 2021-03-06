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
// System call number for `getdirentries64`.
#include <sys/syscall.h>
// Definition of struct dirent and file type macros.
#include <sys/dirent.h>
// POSIX stat.
#include <sys/stat.h>

#include <array>
#include <memory>
#include <ccbase/format.hpp>
#include <ccbase/platform.hpp>

/*
** RUMPOT: [R]ound [u]p to [m]ultiple of [p]ower [o]f [t]wo.
**
** If $p$ and $q$ are positive integers, then we can round $p$ to the next
** multiple of $q$ by computing
**
** 	r = p + q - (p % q).
**
** In the case that $q = 2^k$, where $k \geq 0$, we have
**
** 	r = p + q - (p & (q - 1)).
*/

static inline unsigned
rumpot(const unsigned p, const unsigned q)
{
	return p + q - (p & (q - 1));
}

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
	cc::println("Directory file size: $.", s.st_size);
	cc::println("Blocks allocated: $.", s.st_blocks);
	cc::println("IO blocksize: $.\n", s.st_blksize);

	// When returning an expected object with std::system_error, use
	// strerror or strerror_r to get the error string.
	// https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man3/strerror.3.html
	
	auto n   = rumpot(s.st_size, s.st_blksize);
	auto buf = std::unique_ptr<char[]>{new char[n]};
	auto bp  = off_t{0};
	auto i   = 1u;
	ssize_t r;

	while ((r = getdirentries64(fd, buf.get(), n, &bp)) > 0) {
		auto p = buf.get();
		auto l = buf.get() + r;
		do {
			auto e = (::dirent*)p;
			p += e->d_reclen;
			if (e->d_ino != 0) {
				cc::println("Entry $.", i);
				cc::println("File number: $.", e->d_ino); 
				cc::println("Seek offset: $.", e->d_seekoff);
				cc::println("Record length: $.", e->d_reclen);
				cc::println("Name length: $.", e->d_namlen);
				cc::println("Type: $.", (unsigned)e->d_type);
				cc::println("Name: \"$\".\n", e->d_name);
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
