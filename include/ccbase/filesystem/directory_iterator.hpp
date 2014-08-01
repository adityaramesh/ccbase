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

#include <boost/range/algorithm.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/string_ref.hpp>
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
noexcept
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

	mutable std::array<char, PLATFORM_MAX_PATHNAME_LENGTH> m_path_buf;
	std::unique_ptr<char[]> m_buf{};
	char* m_buf_cur{};
	char* m_buf_end{};

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	int m_read{};
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	::user_ssize_t m_read{};
#endif

	::ssize_t m_bufsz{};
	int m_fd{-1};
	int32_t m_pos{};
	uint32_t m_dir_len{};
	mutable uint32_t m_path_len{};
public:
	explicit directory_iterator() noexcept : m_pos{-1} {}

	explicit directory_iterator(const boost::string_ref dir)
	: m_dir_len(dir.length())
	{
		// Ensure that the string resulting from concatenating the path
		// to the directory, the platform directory separator, and the
		// file name can fit in the path buffer. The trailing "+ 1" term
		// accounts for the null terminating character.
		assert(m_dir_len + 1 + PLATFORM_MAX_FILENAME_LENGTH + 1 <=
			PLATFORM_MAX_PATHNAME_LENGTH);

		// We need to copy `dir` to `m_path_buf`, because `dir` might
		// not be null-terminated.
		boost::copy(dir, m_path_buf.begin());
		m_path_buf[dir.length()] = '\0';
		m_fd = ::open(m_path_buf.begin(), O_RDONLY);

		if (m_fd < 0) {
			throw std::system_error{errno, std::system_category(),
				"failed to open directory"};
		}

		struct stat st;
		if (::fstat(m_fd, &st) == -1) {
			throw std::system_error{errno, std::system_category(),
				"failed to get directory status"};
		}

		m_bufsz = detail::rumpot(st.st_size, st.st_blksize);
		m_buf = std::unique_ptr<char[]>{new char[m_bufsz]};

		// We do not want to copy the null character, so we only copy
		// until dir + dir_len rather than dir + dir_len + 1.
		boost::copy(dir, m_path_buf.data());
		m_path_buf[m_dir_len] = PLATFORM_DIRECTORY_SEPARATOR;
		read_chunk();
	}

	~directory_iterator()
	{ ::close(m_fd); }

	/*
	** Copying a directory iterator creates another one that is backed by a
	** different file descriptor to the same directory. The new iterator is
	** incremented until its position is the same as that of the original.
	** If the original iterator is an end iterator, the copy will also be an
	** end iterator, although no IO operations will be performed.
	*/
	directory_iterator(const directory_iterator& rhs) :
	m_bufsz{rhs.m_bufsz}, m_dir_len{rhs.m_dir_len}
	{
		if (rhs.m_pos == -1) {
			m_pos = -1;
			return;
		}

		m_buf = std::unique_ptr<char[]>{new char[m_bufsz]};
		std::copy(rhs.m_path_buf.data(), rhs.m_path_buf.data() + m_dir_len,
			m_path_buf.data());

		// Careful: we need the null character at the end when
		// interfacing with `open`.
		m_path_buf[m_dir_len] = '\0';
		m_fd = ::open(m_path_buf.data(), O_RDONLY);
		if (m_fd < 0) {
			throw std::system_error{errno, std::system_category(),
				"failed to open directory"};
		}

		m_path_buf[m_dir_len] = PLATFORM_DIRECTORY_SEPARATOR;
		read_chunk();

		while (m_pos != rhs.m_pos) {
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
			m_read = getdents(m_fd, m_buf.get(), m_bufsz);
		#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
			auto off = ::off_t{};
			m_read = getdirentries64(m_fd, m_buf.get(), m_bufsz, &off);
		#endif

		if (m_read > 0) {
			m_buf_cur = m_buf.get();
			m_buf_end = m_buf.get() + m_read;
		}
		else if (m_read == 0) {
			m_pos = -1;
		}
		else if (m_read == -1) {
			throw std::system_error{errno, std::system_category(),
				"failed to read directory entries"};
		}
	}

	void increment()
	{
		native_dirent* ent;
		do {
			ent = (native_dirent*)m_buf_cur;
			m_buf_cur += ent->d_reclen;
		}
		while (ent->d_ino == 0 && m_buf_cur < m_buf_end);

		++m_pos;
		if (m_buf_cur >= m_buf_end) {
			read_chunk();
		}
	}

	directory_entry dereference()
	const noexcept
	{
	#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
		auto ent = (native_dirent*)m_buf_cur;
		// The type of the file is stored in the last byte of the
		// directory record.
		auto type = static_cast<file_type>(*(char*)(m_buf_cur + ent->d_reclen - 1));
		// Compute the length of the file name.
		auto len = length_type{ent->d_reclen - 2 -
			offsetof(detail::linux_dirent, d_name)};
		return {*this, (char*)ent->d_name, len, type};
	#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
		auto ent = (native_dirent*)m_buf_cur;
		return {*this, ent->d_name, ent->d_namlen,
			static_cast<file_type>(ent->d_type)};
	#endif
	}

	bool equal(const directory_iterator& rhs)
	const noexcept { return m_pos == rhs.m_pos; }

	/*
	** Updates the current file at the end of the directory path string.
	*/
	void update_path(const boost::string_ref filename)
	const noexcept
	{
		boost::copy(filename, m_path_buf.data() + m_dir_len + 1);
		m_path_len = m_dir_len + filename.length();
	}

	const boost::string_ref path()
	const noexcept { return {m_path_buf.data(), m_path_len}; }
};

const boost::string_ref
directory_entry::path() const noexcept
{
	m_dir_it.update_path(m_name);
	return m_dir_it.path();
}

using const_directory_iterator = directory_iterator;

}

#endif
