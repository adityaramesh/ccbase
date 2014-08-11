/*
** File Name:	repeat.hpp
** Author:	Aditya Ramesh
** Date:	07/17/2013
** Contact:	_@adityaramesh.com
**
** The `repeat` function iterates a function on an initial type for a given
** number of iterations.
*/

#ifndef Z23434C2C_85AC_49DF_95E8_ABCDD011DB1B
#define Z23434C2C_85AC_49DF_95E8_ABCDD011DB1B

#include <mpl/apply.hpp>

namespace mpl {

template <
	std::uintmax_t            Current,
	std::uintmax_t            Last,
	class                     Result,
	template <class...> class Function
>
struct repeat_impl
{
	using r = apply<Function, Result>;
	using type = typename repeat_impl<
		Current + 1, Last, r, Function
	>::type;
};

template <
	std::uintmax_t            Last,
	class                     Result,
	template <class...> class Function
>
struct repeat_impl<Last, Last, Result, Function>
{
	using type = apply<Function, Result>;
};

template <
	std::uintmax_t            Count,
	class                     T,
	template <class...> class Function
>
using repeat = typename repeat_impl<
	0, Count - 1, T, Function
>::type;

}

#endif
