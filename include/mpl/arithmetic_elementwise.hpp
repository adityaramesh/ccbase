/*
** File Name:	arithmetic_elementwise.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZDD8E3EAC_DDED_4370_A83B_F1005C58A59A
#define ZDD8E3EAC_DDED_4370_A83B_F1005C58A59A

#include <mpl/elementwise.hpp>
#include <mpl/operation.hpp>

namespace mpl {

template <class S1, class S2>
using elementwise_sum = elementwise<add, S1, S2>;

template <class S1, class S2>
using elementwise_product = elementwise<multiply, S1, S2>;

}

#endif
