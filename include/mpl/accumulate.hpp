/*
** File Name:	accumulate.hpp
** Author:	Aditya Ramesh
** Date:	07/11/2013
** Contact:	_@adityaramesh.com
**
** An accumulation operation produces one type from a sequence of types. An
** unary function is applied to each element in the sequence to produce a new
** type. A binary operation is then applied to the current result and the result
** of the unary function to produce the new result. This process continues until
** all of the elements in the sequence have been exhausted.
*/

#ifndef ZF64EBD40_233E_4EC9_9A4E_D84C49CBA419
#define ZF64EBD40_233E_4EC9_9A4E_D84C49CBA419

#include <mpl/apply.hpp>

namespace mpl {

/*
** `accumulate`
*/

template <
	class                     Result,
	template <class...> class Function,
	template <class...> class Operation,
	class                     S
>
struct accumulate_impl;

template <
	class                     Result,
	template <class...> class Function,
	template <class...> class Operation,
	class                     T,
	class...                  Ts
>
struct accumulate_impl<
	Result,
	Function,
	Operation,
	sequence<T, Ts...>
>
{
	using t = apply<Function, T>;
	using r = apply<Operation, Result, t>;

	using type = typename accumulate_impl<
		r, Function, Operation, sequence<Ts...>
	>::type;
};

template <
	class                     Result,
	template <class...> class Function,
	template <class...> class Operation
>
struct accumulate_impl<Result, Function, Operation, sequence<>>
{
	using type = Result;
};

template <
	class                     Initial,
	template <class...> class Function,
	template <class...> class Operation,
	class                     S
>
using accumulate = typename accumulate_impl<
	Initial, Function, Operation, S
>::type;

}

#endif
