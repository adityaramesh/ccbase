/*
** File Name:	integer_sequence.hpp
** Author:	Aditya Ramesh
** Date:	05/06/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z70F6B93C_E078_4BDE_AEDA_935F450BDE3B
#define Z70F6B93C_E078_4BDE_AEDA_935F450BDE3B

#include <mpl/integer.hpp>
#include <mpl/sequence.hpp>

namespace mpl {

template <std::uintmax_t... Ts>
using integer_sequence = sequence<integer<Ts>...>;

template <std::uintmax_t... Ts>
using coordinates = integer_sequence<Ts...>;

// Causes compiler error if done this way. I forgot if I reported this one.
// template <std::uintmax_t... Ts>
// using extents = integer_sequence<Ts...>;

template <std::uintmax_t... Ts>
using extents = sequence<integer<Ts>...>;

}

#endif
