/*
** File Name: types.hpp
** Author:    Aditya Ramesh
** Date:      01/13/2015
** Contact:   _@adityaramesh.com
**
** Defines the basic types used in MPL algorithms.
*/

#ifndef ZB2EFAF00_D7AB_413B_810D_B90D84B03654
#define ZB2EFAF00_D7AB_413B_810D_B90D84B03654

#include <type_traits>
#include <utility>

namespace cc {

template <class... Ts>
struct seq
{
	static constexpr auto size()
	noexcept { return sizeof...(Ts); }
};

template <class Integer, Integer Value>
struct c { static constexpr auto value = Value; }; 

/*
** `type_seq` is used to convert `std::integer_sequence`s into
** `cc::seq`s, so that the same algorithms can be used for both types.
*/

template <class Seq>
struct type_seq_helper
{ using type = Seq; };

template <class Integer, Integer... Ts>
struct type_seq_helper<std::integer_sequence<Integer, Ts...>>
{ using type = seq<c<Integer, Ts>...>; };

template <class Seq>
using type_seq = typename type_seq_helper<Seq>::type;

/*
** `value_seq` is used to convert `cc::seq`s of `cc:c`s into
** `std::integer_sequence`s.
*/

template <class Seq>
struct value_seq_helper;

template <class Integer, Integer Value, class... Tail>
struct value_seq_helper<seq<c<Integer, Value>, Tail...>>
{
	using type = std::integer_sequence<Integer, Value, Tail::value...>;
};

template <class Seq>
using value_seq = typename value_seq_helper<Seq>::type;

}

#endif
