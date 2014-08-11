/*
** File Name:	permutation.hpp
** Author:	Aditya Ramesh
** Date:	08/19/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z79D7AA9A_5C94_463C_A304_31C6483902F1
#define Z79D7AA9A_5C94_463C_A304_31C6483902F1

#include <mpl/integer_sequence.hpp>

namespace mpl
{

template <std::uintmax_t... Ts> 
using permutation = integer_sequence<Ts...>;

/*
** TODO
**
** Permutation utility functions.
*/

}

#endif
