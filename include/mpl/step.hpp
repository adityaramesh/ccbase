/*
** File Name:	step.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
**
** The `step` function steps a multidimensional index counter associated with a
** sequence of extents and a sequence of increment factors.  When the size of a
** dimension of the counter is incremented, it is increased by an amount equal
** to the increment factor corresponding to the dimension.
**
** As a concrete example, consider the a 3-tuple counter initially set to
** (0,0,0), with extents (3,3,3). In this example, we set the increment factor
** sequence associated with the counter to (1,1,1). This means that when a
** particular dimension is incremented, it is increased by one. Iteratively
** stepping the counter starting from the value (0,0,0) results in the following
** sequence:
**
** 	(0,0,0)
** 	(1,0,0) (step 1)
** 	(2,0,0) (step 2)
** 	(0,1,0) (step 3)
** 	(1,1,0) (step 4)
** 	(2,1,0) (step 5)
** 	(0,2,0) (step 6)
** 	(1,2,0) (step 7)
** 	(2,2,0) (step 8)
** 	(0,0,1) (step 9)
** 	...
** 	(2,2,2) (step 26)
** 	(0,0,0) (step 27)
*/

#ifndef Z5500A288_2302_4287_A2F7_23E03B79649A
#define Z5500A288_2302_4287_A2F7_23E03B79649A

#include <mpl/bind.hpp>
#include <mpl/generate.hpp>
#include <mpl/repeat.hpp>

namespace mpl {

template <
	std::uintmax_t CurrentDimension,
	std::uintmax_t Carry,
	class          Counter,
	class          Extents,
	class          IncrementFactors
>
struct step_impl
{
	// Determine the values for this dimension.
	static constexpr auto num = size<Extents>::value;
	static constexpr auto cur = at<CurrentDimension, Counter>::value;
	static constexpr auto max = at<CurrentDimension, Extents>::value;
	static constexpr auto inc = at<CurrentDimension, IncrementFactors>::value;

	// Determine the new size of this dimension.
	static constexpr auto n = Carry * inc;
	static constexpr auto i = (cur + n) % max;
	static constexpr auto c1 = (cur + n) / max;

	// If we are at the last dimension and the carry is nonzero, then the
	// next state should be the zero tuple. Hence, we subtract one from the
	// carry under these conditions.
	static constexpr auto c2 = (CurrentDimension == num - 1 && c1 > 0) ? c1 - 1 : c1;

	using counter = set<
		CurrentDimension,
		integer<i>,
		Counter
	>;

	// If we are at the last dimension and there is nonzero carry, we may
	// have to start over by incrementing the first dimension's size again.
	static constexpr auto next = (CurrentDimension + 1) % num;

	using type = typename step_impl<
		next,
		c2,
		counter,
		Extents,
		IncrementFactors
	>::type;
};

template <
	std::uintmax_t CurrentDimension,
	class          Counter,
	class          Extents,
	class          IncrementFactors
>
struct step_impl<
	CurrentDimension,
	0,
	Counter,
	Extents,
	IncrementFactors
>
{
	using type = Counter;
};

template <
	class          Counter,
	class          Extents,
	std::uintmax_t Count            = 1,
	class          IncrementFactors = constant_sequence<1, size<Extents>::value>
>
using step = typename step_impl<
	0, Count, Counter, Extents, IncrementFactors
>::type;

}

#endif
