/*
** File Name:	forward.hpp
** Author:	Aditya Ramesh
** Date:	07/17/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z33FE8F64_4CF2_42BE_88F3_F7FDF3EBFC17
#define Z33FE8F64_4CF2_42BE_88F3_F7FDF3EBFC17

#include <mpl/sequence.hpp>

namespace mpl {

template <std::uintmax_t Index>
struct forward
{
	template <class... Ts>
	struct rebind
	{
		using type = at<Index, sequence<Ts...>>;
	};
};

}

#endif
