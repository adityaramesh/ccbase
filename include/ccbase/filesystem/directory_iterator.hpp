/*
** File Name:	directory_iterator.hpp
** Author:	Aditya Ramesh
** Date:	08/27/2013
** Contact:	_@adityaramesh.com
**
** This header defines a forward iterator that traverses the low-level directory
** entries stored by the operating system. It reads the directory entires into a
** buffer that is at least as large as the total size of the directory entries,
** and whose size is also a multiple of the blocksize reported by `fstat`. When
** the iterator is incremented, it reads the record length of the current
** directory entry, and uses it to reach the next directory entry.
**
** If you need to iterate a very large number of files as fast as possible, then
** this strategy could be optimized further by using two buffers and
** preemptively filling the second buffer on another thread while the first
** buffer is processed.
*/

#ifndef Z288360C0_5CDE_4818_A366_F1E1AA4CF599
#define Z288360C0_5CDE_4818_A366_F1E1AA4CF599

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <system_error>
#include <boost/iterator/iterator_facade.hpp>
#include <ccbase/platform.hpp>
#include <ccbase/filesystem/directory_entry.hpp>
#include <ccbase/filesystem/system_call.hpp>

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	// For POSIX open.
	#include <fcntl.h>
	// For POSIX close.
	#include <unistd.h>
	// For POSIX stat.
	#include <sys/stat.h>
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	// For POSIX open.
	#include <fcntl.h>
	// For POSIX close.
	#include <unistd.h>
	// For definition of struct dirent.
	#include <sys/dirent.h>
	// For POSIX stat.
	#include <sys/stat.h>
#else
	#error "Unsupported kernel."
#endif

#if PLATFORM_MAX_FILENAME_LENGTH == PLATFORM_MAX_FILENAME_LENGTH_UNKNOWN || \
    PLATFORM_MAX_PATHNAME_LENGTH == PLATFORM_MAX_PATHNAME_LENGTH_UNKNOWN || \
    !defined(PLATFORM_DIRECTORY_SEPARATOR)
	#error "Could not determine necessary information about platform."
#endif

namespace cc {

namespace detail {

/*
** Rounds a number to a multiple of another number that is a power of two.
*/
CC_ALWAYS_INLINE unsigned
rumpot(const unsigned p, const unsigned q)
{
	return p + q - (p & (q - 1));
}

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX

struct linux_dirent
{
	uint64_t d_ino;
	uint64_t d_off;
	uint16_t d_reclen;
	uint8_t  d_name[];

	/*
	** Although there are more fields after `d_name`, it does not do any
	** good to declare them here, because they can only be accessed after we
	** know `d_reclen`. The purpose of this structure is to make it easy to
	** access the first few fields without tedious pointer arithmetic
	** involving alignment computations.
	*/
};

#endif

}

/*
** The constructors of this class can throw. For most cases, the `cc::file_list`
** function, which returns an expected range object containing the first and
** last directory iterators, should be sufficient. The latter is also much more
** convenient to use.
*/

class directory_iterator :
public boost::iterator_facade<
	directory_iterator, directory_entry,
	boost::single_pass_traversal_tag, directory_entry
>
{
	using length_type = directory_entry::length_type;
#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	using native_dirent = detail::linux_dirent;
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	using native_dirent = ::dirent;
#endif

	mutable std::array<char, PLATFORM_MAX_PATHNAME_LENGTH> pathbuf;
	std::unique_ptr<char[]> buf;
	char* f;
	char* l;

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	int read;
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	user_ssize_t read;
	off_t        off{};
#endif

	ssize_t  bufsz;
	int      fd;
	int      pos{};
	unsigned dirlen;
public:
	directory_iterator() noexcept : pos{-1} {}

	directory_iterator(const char* dir) : dirlen(std::strlen(dir))
	{
		// Ensure that the string resulting from concatenating the path
		// to the directory, the platform directory separator, and the
		// file name can fit in the path buffer. The trailing "+ 1" term
		// accounts for the null terminating character.
		assert(dirlen + 1 + PLATFORM_MAX_FILENAME_LENGTH + 1 <=
			PLATFORM_MAX_PATHNAME_LENGTH);

		fd = ::open(dir, O_RDONLY);
		if (fd < 0) {
			throw std::system_error{errno, std::system_category(),
				"Failed to open directory"};
		}

		struct stat s;
		if (::fstat(fd, &s) == -1) {
			throw std::system_error{errno, std::system_category(),
				"Failed to get directory status"};
		}

		bufsz = detail::rumpot(s.st_size, s.st_blksize);
		buf   = std::unique_ptr<char[]>{new char[bufsz]};

		// We do not want to copy the null character, so we only copy
		// until dir + dirlen rather than dir + dirlen + 1.
		std::copy(dir, dir + dirlen, pathbuf.data());
		pathbuf[dirlen] = PLATFORM_DIRECTORY_SEPARATOR;
		read_chunk();
	}

	~directory_iterator()
	{
		::close(fd);
	}

	/*
	** Copying a directory iterator creates another one that is backed by a
	** different file descriptor to the same directory. The new iterator is
	** incremented until its position is the same as that of the original.
	** If the original iterator is an end iterator, the copy will also be an
	** end iterator, although no IO operations will be performed.
	*/
	directory_iterator(const directory_iterator& rhs) :
	bufsz{rhs.bufsz}, dirlen{rhs.dirlen}
	{
		if (rhs.pos == -1) {
			pos = -1;
			return;
		}

		buf = std::unique_ptr<char[]>{new char[bufsz]};
		std::copy(rhs.pathbuf.data(), rhs.pathbuf.data() + dirlen, pathbuf.data());
		pathbuf[dirlen] = '\0';

		fd = ::open(pathbuf.data(), O_RDONLY);
		if (fd < 0) {
			throw std::system_error{errno, std::system_category(),
				"Failed to open directory"};
		}

		pathbuf[dirlen] = PLATFORM_DIRECTORY_SEPARATOR;
		read_chunk();

		while (pos != rhs.pos) {
			increment();
		}
	}
private:
	friend class directory_entry;
	friend class boost::iterator_core_access;

	/*
	** Mmm... chunky.
	*/
	void read_chunk()
	{
		#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
			read = getdents(fd, buf.get(), bufsz);
		#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
			read = getdirentries64(fd, buf.get(), bufsz, &off);
		#endif

		if (read > 0) {
			f = buf.get();
			l = buf.get() + read;
		}
		else if (read == 0) {
			pos = -1;
		}
		else if (read == -1) {
			throw std::system_error{errno, std::system_category(),
				"Failed to read directory entries"};
		}
	}

	void increment()
	{
		native_dirent* e;
		do {
			e = (native_dirent*)f;
			f += e->d_reclen;
		}
		while (e->d_ino == 0 && f < l);

		++pos;
		if (f >= l) {
			read_chunk();
		}
	}

	directory_entry dereference() const
	{
		#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
			auto e  = (native_dirent*)f;
			// The type of the file is stored in the last byte of
			// the directory record.
			auto t  = static_cast<file_type>(*(char*)(f + e->d_reclen - 1));
			// Compute the length of the file name.
			auto nl = length_type(e->d_reclen - 2 - offsetof(detail::linux_dirent, d_name));
			return { *this, (char*)e->d_name, nl, t };
		#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
			auto e = (native_dirent*)f;
			return { *this, e->d_name, e->d_namlen,
				static_cast<file_type>(e->d_type) };
		#endif
	}

	bool equal(const directory_iterator& rhs) const
	{
		return pos == rhs.pos;
	}

	void update_path(const char* fn, length_type n) const
	{
		std::copy(fn, fn + n, pathbuf.data() + dirlen + 1);
		pathbuf[dirlen + 1 + n] = '\0';
	}

	const char* path() const { return pathbuf.data(); }
};

const char* directory_entry::path() const
{
	p->update_path(n, len);
	return p->path();
}

using const_directory_iterator = directory_iterator;

}

#endif
