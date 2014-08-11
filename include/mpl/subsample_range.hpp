/*
** File Name:	subsample_range.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z2482C8DE_B3C1_444C_95A3_346DBDF5CFEB
#define Z2482C8DE_B3C1_444C_95A3_346DBDF5CFEB

#include <mpl/arithmetic_elementwise.hpp>
#include <mpl/bind.hpp>
#include <mpl/generate.hpp>
#include <mpl/generate_range.hpp>

namespace mpl {

template <
	class IncrementFactors,
	class Extents,
	class First             = constant_sequence<0, size<Extents>::value>,
	class Last              = First
>
using subsample_range = generate_range<
	identity,
	Extents,
	First,
	Last,
	IncrementFactors
>;

}

#endif
