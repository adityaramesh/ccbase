/*
** File Name:	enumerate_range.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z249D7AED_14A1_4666_BCE3_E167EEF7E1C2
#define Z249D7AED_14A1_4666_BCE3_E167EEF7E1C2

#include <mpl/arithmetic_elementwise.hpp>
#include <mpl/bind.hpp>
#include <mpl/generate.hpp>
#include <mpl/generate_range.hpp>

namespace mpl {

template <
	class Extents,
	class Coordinates = constant_sequence<0, size<Extents>::value>
>
using enumerate_range = generate_range<
	bind<0, Coordinates, elementwise_sum>::template rebind,
	Extents
>;

}

#endif
