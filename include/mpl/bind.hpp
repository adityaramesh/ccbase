/*
** File Name:	bind.hpp
** Author:	Aditya Ramesh
** Date:	07/16/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z6C5CC430_AF22_4290_B6F7_593E11D47606
#define Z6C5CC430_AF22_4290_B6F7_593E11D47606

#include <type_traits>
#include <mpl/apply.hpp>

namespace mpl {

template <
	std::uintmax_t            Index,
	class                     T,
	template <class...> class Function
>
struct bind
{
	template <class... Us>
	struct rebind
	{
		using s = sequence<Us...>;
		using args = insert_at<Index, T, s>;
		using type = apply_sequence<Function, args>;
	};
};

}

#endif
