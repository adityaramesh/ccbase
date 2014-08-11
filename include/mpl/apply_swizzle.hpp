/*
** File Name:	apply_swizzle.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z0BC13F65_4BEA_46C0_BC96_1D783FA779C1
#define Z0BC13F65_4BEA_46C0_BC96_1D783FA779C1

#include <mpl/apply.hpp>
#include <mpl/swizzle.hpp>

namespace mpl {

template <
	class                     Indices,
	template <class...> class Function
>
struct apply_swizzle
{
	template <class... Ts>
	struct rebind
	{
		using s = sequence<Ts...>;
		using t = swizzle<Indices, s>;
		using type = apply_sequence<Function, t>;
	};
};

}

#endif
