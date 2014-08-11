/*
** File Name:	arithmetic_range.hpp
** Author:	Aditya Ramesh
** Date:	07/17/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZF33C7A81_9E0D_441E_8ED1_F31A4ACBC274
#define ZF33C7A81_9E0D_441E_8ED1_F31A4ACBC274

#include <mpl/accumulate_range.hpp>
#include <mpl/integer.hpp>
#include <mpl/operation.hpp>

namespace mpl {

/*
** `sum_range`
*/

template <class S, template <class...> class Function>
using sum_range = accumulate_range<integer<0>, Function, add, S>;

}

#endif
