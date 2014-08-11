/*
** File Name:	generate.hpp
** Author:	Aditya Ramesh
** Date:	07/12/2013
** Contact:	_@adityaramesh.com
** 
** The `generate` function creates a sequence by applying a given function to
** each integer in an interval.
*/

#ifndef Z2C9CD465_6DAC_4433_8B7F_80E51E480145
#define Z2C9CD465_6DAC_4433_8B7F_80E51E480145

#include <mpl/bind.hpp>
#include <mpl/operation.hpp>

namespace mpl {

/*
** `generate`
*/

template <
	std::uintmax_t            Current,
	std::uintmax_t            Max,
	template <class...> class Function,
	class                     Head
>
struct generate_impl;

template <
	std::uintmax_t            Current,
	std::uintmax_t            Max,
	template <class...> class Function,
	class...                  Ts
>
struct generate_impl<
	Current,
	Max,
	Function,
	sequence<Ts...>
>
{
	using t = apply<Function, integer<Current>>;

	using type =
	typename generate_impl<
		Current + 1,
		Max,
		Function,
		sequence<Ts..., t>
	>::type;
};

template <
	std::uintmax_t            Max,
	template <class...> class Function,
	class...                  Ts
>
struct generate_impl<Max, Max, Function, sequence<Ts...>>
{
	using type = sequence<Ts...>;
};

template <
	template <class...> class Function,
	std::uintmax_t            Count
>
using generate = typename generate_impl<
	0, Count, Function, sequence<>
>::type;

/*
** `constant_sequence`
*/

template <std::uintmax_t Value, std::uintmax_t Count>
using constant_sequence = generate<
	constant<integer<Value>>::template rebind, Count
>;

/*
** `consecutive_sequence`
*/

template <std::uintmax_t Initial, std::uintmax_t Count>
using consecutive_sequence = generate<
	bind<0, integer<Initial>, add>::template rebind, Count
>;

}

#endif
