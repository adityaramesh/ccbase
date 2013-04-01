/*
** File Name:	order.hpp
** Author:	Aditya Ramesh
** Date:	04/01/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z7B480DFE_EB09_4694_9122_2FE3FF17D0FB
#define Z7B480DFE_EB09_4694_9122_2FE3FF17D0FB

namespace cc
{

enum byte_order
{
	little_endian,
	big_endian,
	pdp_endian
};

#if defined(__APPLE__)
	#include <machine/endian.h>

	#if BYTE_ORDER == LITTLE_ENDIAN
		static constexpr byte_order order{byte_order::little_endian};
	#elif BYTE_ORDER == BIG_ENDIAN
		static constexpr byte_order order{byte_order::big_endian};
	#elif BYTE_ORDER == PDP_ENDIAN
		static constexpr byte_order order{byte_order::pdp_endian};
	#else
		#error Cannot determine machine byte order.
	#endif
#elif defined(__linux__)
	#include <sys/param.h>

	#if __BYTE_ORDER == __LITTLE_ENDIAN
		static constexpr byte_order order{byte_order::little_endian};
	#elif __BYTE_ORDER == __BIG_ENDIAN
		static constexpr byte_order order{byte_order::big_endian};
	#elif __BYTE_ORDER == __PDP_ENDIAN
		static constexpr byte_order order{byte_order::pdp_endian};
	#else
		#error Cannot determine machine byte order.
	#endif
#else
	#error Cannot determine machine byte order.
#endif

}

#endif
