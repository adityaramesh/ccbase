/*
** File Name:	directory_entry.hpp
** Author:	Aditya Ramesh
** Date:	08/23/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZDDEA7CE4_14FD_40C7_AA27_9BBF59D67383
#define ZDDEA7CE4_14FD_40C7_AA27_9BBF59D67383

#include <cstdint>
#include <ostream>
#include <ccbase/format.hpp>
#include <ccbase/platform.hpp>

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
	#include <dirent.h>
#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	#include <sys/dirent.h>
#else
	#error "Unsupported kernel."
#endif

namespace cc {

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

std::ostream& operator<<(std::ostream& os, const file_type& t)
{
	switch (t) {
	case file_type::block:         cc::write (os, "block");         return os;
	case file_type::character:     cc::write (os, "character");     return os;
	case file_type::directory:     cc::write (os, "directory");     return os;
	case file_type::fifo:          cc::write (os, "fifo");          return os;
	case file_type::symbolic_link: cc::write (os, "symbolic link"); return os;
	case file_type::regular:       cc::write (os, "regular");       return os;
	case file_type::socket:        cc::write (os, "socket");        return os;
	case file_type::unknown:       cc::write (os, "unknown");       return os;
	}
}

class directory_iterator;

class directory_entry
{
	friend class directory_iterator;
	using length_type = uint16_t;

	const directory_iterator& m_dir_it;
	const boost::string_ref m_name;
	const file_type m_type;

	directory_entry(
		const directory_iterator& dir_it,
		const char* name,
		const length_type len,
		const file_type type
	) noexcept : m_dir_it{dir_it}, m_name{name, len}, m_type{type} {}
public:
	// Defined in `directory_iterator.hpp` due to cyclic dependencies.
	const boost::string_ref path() const noexcept;
	const boost::string_ref name() const noexcept { return m_name; }
	file_type type() const noexcept { return m_type; }
};

std::ostream& operator<<(std::ostream& os, const directory_entry& e)
{
	cc::write(os, "{{name: $, type: $}}", e.name(), e.type());
	return os;
}

}

#endif
