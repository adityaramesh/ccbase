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
	big_endian
};

#if defined(__APPLE__) || defined(__linux__)
	#include <sys/param.h>
	
	#if !defined(__BYTE_ORDER) || \
	    (!defined(__BIG_ENDIAN) && !defined(__LITTLE_ENDIAN)) || \
            (defined(__BIG_ENDIAN) && !defined(__LITTLE_ENDIAN) && __BYTE_ORDER != __BIG_ENDIAN) || \
	    (defined(__LITTLE_ENDIAN) && !defined(__BIG_ENDIAN) && __BYTE_ORDER != __LITTLE_ENDIAN)
		#error "Error: apparently, I found and included the file " \
		"'sys/param.h', but because certain macros I was looking for " \
		"were not defined, I could not determine the byte order of " \
		"your system. If your system is little-endian or big-endian, " \
		"an easy fix would be to set the constant 'order' in this " \
		"header manually. I am not equipped to handle other kinds of " \
		"byte orders."
	#endif

	#if __BYTE_ORDER == __LITTLE_ENDIAN
		static constexpr byte_order order{byte_order::little_endian};
	#elif __BYTE_ORDER == __BIG_ENDIAN
		static constexpr byte_order order{byte_order::big_endian};
	#else
		#error "Error: I could not determine the byte order of your " \
		"system because '__BYTE_ORDER' was neither set to " \
		"'__BIG_ENDIAN' nor '__LITTLE_ENDIAN'. If your system is " \
		"little-endian or big-endian, an easy fix would be to set " \
		"the constant 'byte_order' in this header manually. I am not " \
		"equipped to handle other kinds of byte orders."
	#endif
#else
	#error "Error: I could not determine the byte order of your " \
	"system because I do not know where or how your system defines it. " \
	"If your system is little-endian or big-endian, an easy fix would " \
	"be to set the constant 'order' in this header manually. I am not " \
	"equipped to handle other kinds of byte orders."
#endif

}

#endif
