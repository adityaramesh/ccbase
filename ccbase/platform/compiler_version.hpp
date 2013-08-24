/*
** File Name:	compiler_version.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z178C9C24_0EEF_41B7_B90A_400FC8D6827D
#define Z178C9C24_0EEF_41B7_B90A_400FC8D6827D

#include <cstring>
#undef major
#undef minor

namespace cc
{

class compiler_version
{
private:
	const std::size_t v;
	const std::size_t r;
	const std::size_t p;
public:
	constexpr compiler_version(
		const std::size_t v,
		const std::size_t r,
		const std::size_t p
	) : v{v}, r{r}, p{p} {}

	constexpr std::size_t major() const
	{
		return v;
	}

	constexpr std::size_t minor() const
	{
		return r;
	}

	constexpr std::size_t patch() const
	{
		return p;
	}

	constexpr bool operator==(const compiler_version& rhs) const
	{
		return v == rhs.v && r == rhs.r && v == rhs.v;
	}

	constexpr bool operator!=(const compiler_version& rhs) const
	{
		return !(*this == rhs);
	}

	// TODO: Implement <, <=, >, >= when C++14 is released and generalized
	// constexpr support is available.
};

}

#endif
