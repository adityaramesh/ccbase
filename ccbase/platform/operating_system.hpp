/*
** File Name:	operating_system.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZE8F1E203_0839_49EF_961E_1870AAE48161
#define ZE8F1E203_0839_49EF_961E_1870AAE48161

#include <ccbase/platform/definitions.hpp>
#include <ccbase/platform/str_const.hpp>

namespace cc
{

enum class kernel_type
{
	linux      = PLATFORM_KERNEL_LINUX,
	xnu        = PLATFORM_KERNEL_XNU,
	windows_nt = PLATFORM_KERNEL_WINDOWS_NT,
	unknown    = PLATFORM_KERNEL_UNKNOWN
};

class operating_system
{
public:
	enum type
	{
		linux_distribution = PLATFORM_OS_LINUX_DISTRIBUTION,
		os_x               = PLATFORM_OS_OS_X,
		windows            = PLATFORM_OS_WINDOWS,
		unknown            = PLATFORM_OS_UNKNOWN
	};
private:
	const type os;
	const kernel_type k;
	const str_const nl;
public:
	template <std::size_t N>
	constexpr operating_system(
		const type os,
		const kernel_type k,
		const char(&nl)[N]
	) : os{os}, k{k}, nl{nl} {}

	constexpr kernel_type kernel() const
	{
		return k;
	}

	constexpr str_const newline() const
	{
		return nl;
	}

	constexpr bool operator==(const type& rhs) const
	{
		return os == rhs;
	}

	constexpr bool operator!=(const type& rhs) const
	{
		return os != rhs;
	}
};

}

#endif
