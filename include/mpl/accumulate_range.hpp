/*
** File Name:	accumulate_range.hpp
** Author:	Aditya Ramesh
** Date:	07/15/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z2E21DDDA_0E07_4263_9D22_2F7E447FDF87
#define Z2E21DDDA_0E07_4263_9D22_2F7E447FDF87

#include <mpl/apply.hpp>
#include <mpl/arithmetic.hpp>
#include <mpl/generate.hpp>
#include <mpl/step.hpp>

namespace mpl {

/*
** `accumulate_range`
*/

template <
	bool                      FirstIteration,
	class                     Current,
	class                     Last,
	class                     Extents,
	class                     IncrementFactor,
	class                     Result,
	template <class...> class Function,
	template <class...> class Operation
>
struct accumulate_range_impl
{
	using next = step<Current, Extents, 1, IncrementFactor>;
	using t1 = apply<Function, Current>;
	using t2 = apply<Operation, Result, t1>;

	using type =
	typename accumulate_range_impl<
		false,
		next,
		Last,
		Extents,
		IncrementFactor,
		t2,
		Function,
		Operation
	>::type;
};

template <
	class                     Last,
	class                     Extents,
	class                     IncrementFactor,
	class                     Result,
	template <class...> class Function,
	template <class...> class Operation
>
struct accumulate_range_impl<
	false,
	Last,
	Last,
	Extents,
	IncrementFactor,
	Result,
	Function,
	Operation
>
{
	using type = Result;
};

template <
	class                     Initial,
	template <class...> class Function,
	template <class...> class Operation,
	class                     Extents,
	class                     First           = constant_sequence<0, size<Extents>::value>,
	class                     Last            = First,
	class                     IncrementFactor = constant_sequence<1, size<Extents>::value>
>
using accumulate_range =
typename accumulate_range_impl<
	true,
	First,
	Last,
	Extents,
	IncrementFactor,
	Initial,
	Function,
	Operation
>::type;

}

#endif
