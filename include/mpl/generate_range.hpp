/*
** File Name:	generate_range.hpp
** Author:	Aditya Ramesh
** Date:	07/15/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZD1BD4D1A_3990_4133_8437_AC126F0F48E4
#define ZD1BD4D1A_3990_4133_8437_AC126F0F48E4

#include <mpl/apply.hpp>
#include <mpl/arithmetic.hpp>
#include <mpl/generate.hpp>
#include <mpl/step.hpp>

namespace mpl {

/*
** `generate_range`
*/

template <
	bool                      FirstIteration,
	class                     Current,
	class                     Last,
	class                     Extents,
	class                     IncrementFactor,
	template <class...> class Function,
	class                     Head
>
struct generate_range_impl
{
	using next = step<Current, Extents, 1, IncrementFactor>;
	using t = apply<Function, Current>;

	using type =
	typename generate_range_impl<
		false,
		next,
		Last,
		Extents,
		IncrementFactor,
		Function,
		append<t, Head>
	>::type;
};

template <
	class                     Last,
	class                     Extents,
	class                     IncrementFactor,
	template <class...> class Function,
	class                     Head
>
struct generate_range_impl<
	false,
	Last,
	Last,
	Extents,
	IncrementFactor,
	Function,
	Head
>
{
	using type = Head;
};

template <
	template <class...> class Function,
	class                     Extents,
	class                     First           = constant_sequence<0, size<Extents>::value>,
	class                     Last            = First,
	class                     IncrementFactor = constant_sequence<1, size<Extents>::value>
>
using generate_range =
typename generate_range_impl<
	true,
	First,
	Last,
	Extents,
	IncrementFactor,
	Function,
	sequence<>
>::type;

}

#endif
