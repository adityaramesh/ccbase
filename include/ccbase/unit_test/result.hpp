/*
** File Name:	result.hpp
** Author:	Aditya Ramesh
** Date:	07/15/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z267B316A_BF50_4FF8_A898_D95A04FD7914
#define Z267B316A_BF50_4FF8_A898_D95A04FD7914

#include <string>

#include <boost/utility/string_ref.hpp>
#include <ccbase/format.hpp>
#include <ccbase/utility/accessors.hpp>

namespace cc {
namespace detail {

class result
{
	std::string m_src{};
	size_t m_line{};
	bool m_passed{};
public:
	explicit result(
		size_t line,
		const boost::string_ref src,
		bool passed
	) noexcept : m_src{format("require($)", src)}, m_line{line},
	 m_passed{passed} {}

	DEFINE_COPY_GETTER(passed, m_passed)
	DEFINE_COPY_GETTER(line, m_line)
	DEFINE_REF_GETTER(source, m_src)
};

}}

#endif
