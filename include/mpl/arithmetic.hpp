/*
** File Name:	arithmetic.hpp
** Author:	Aditya Ramesh
** Date:	07/17/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z9DD73259_29AB_4BCB_80DC_4F50EC37376F
#define Z9DD73259_29AB_4BCB_80DC_4F50EC37376F

#include <mpl/accumulate.hpp>
#include <mpl/integer.hpp>
#include <mpl/operation.hpp>

namespace mpl {

/*
** `sum`
*/

template <class S, template <class...> class Function = identity>
using sum = accumulate<integer<0>, Function, add, S>;

/*
** `product`
*/

template <class S, template <class...> class Function = identity>
using product = accumulate<integer<1>, Function, multiply, S>;

}

#endif
