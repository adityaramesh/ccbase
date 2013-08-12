/*
** File Name:	compiler.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z558BFDC9_0048_4DD1_B19F_A5F1286E7173
#define Z558BFDC9_0048_4DD1_B19F_A5F1286E7173

#include <ccbase/platform/compiler_version.hpp>
#include <ccbase/platform/definitions.hpp>

namespace cc
{

class compiler
{
public:
	enum type
	{
		clang   = PLATFORM_COMPILER_CLANG,
		comeau  = PLATFORM_COMPILER_COMEAU,
		gcc     = PLATFORM_COMPILER_GCC,
		icc     = PLATFORM_COMPILER_ICC,
		msvc    = PLATFORM_COMPILER_MSVC,
		unknown = PLATFORM_COMPILER_UNKNOWN
	};
private:
	const type c;
	const compiler_version v;
public:
	constexpr compiler(
		const type c,
		const compiler_version v
	) : c{c}, v{v} {}

	constexpr compiler_version version() const
	{
		return v;
	}

	constexpr bool operator==(const type& rhs) const
	{
		return c == rhs;
	}

	constexpr bool operator!=(const type& rhs) const
	{
		return c != rhs;
	}

	constexpr bool operator==(const compiler& rhs) const
	{
		return c == rhs.c && v == rhs.v;
	}

	constexpr bool operator!=(const compiler& rhs) const
	{
		return !(*this == rhs);
	}
};

}

#endif
