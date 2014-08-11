/*
** File Name:	integer.hpp
** Author:	Aditya Ramesh
** Date:	07/17/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z239FDD54_6240_4D5A_AFF9_0547D7F0EEB0
#define Z239FDD54_6240_4D5A_AFF9_0547D7F0EEB0

#include <cstdint>

namespace mpl {

template <std::uintmax_t T>
struct integer
{
	static constexpr auto value = T;
};

}

#endif
