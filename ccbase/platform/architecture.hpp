/*
** File Name:	architecture.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZF0CE30E8_E80C_425F_8FC3_F31738AC8E92
#define ZF0CE30E8_E80C_425F_8FC3_F31738AC8E92

#include <cstring>
#include <ccbase/platform/definitions.hpp>

namespace cc
{

enum class byte_order
{
	little      = PLATFORM_BYTE_ORDER_LITTLE,
	big         = PLATFORM_BYTE_ORDER_BIG,
	little_word = PLATFORM_BYTE_ORDER_LITTLE_WORD,
	unknown     = PLATFORM_BYTE_ORDER_UNKNOWN
};

class architecture
{
public:
	enum type
	{
		arm     = PLATFORM_ARCH_ARM,
		itanium = PLATFORM_ARCH_ITANIUM,
		x86     = PLATFORM_ARCH_X86,
		unknown = PLATFORM_ARCH_UNKNOWN
	};
private:
	const type t;
	const std::size_t ws;
	const byte_order ib;
public:
	constexpr architecture(
		const type t,
		const std::size_t ws,
		const byte_order ib
	) : t{t}, ws{ws}, ib{ib} {}

	constexpr std::size_t word_size() const
	{
		return ws;
	}

	constexpr byte_order integer_byte_order() const
	{
		return ib;
	}

	constexpr bool operator==(const type& rhs) const
	{
		return t == rhs;
	}

	constexpr bool operator!=(const type& rhs) const
	{
		return t != rhs;
	}

	constexpr bool operator==(const architecture& rhs) const
	{
		return t == rhs.t && ws == rhs.ws && ib == rhs.ib;
	}

	constexpr bool operator!=(const architecture& rhs) const
	{
		return !(*this == rhs);
	}
};

}

#endif
