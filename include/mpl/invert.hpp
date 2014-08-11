/*
** File Name:	invert.hpp
** Author:	Aditya Ramesh
** Date:	07/13/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZE03E8396_DF78_44E4_A1F3_EF3DDD68FF1B
#define ZE03E8396_DF78_44E4_A1F3_EF3DDD68FF1B

#include <mpl/map.hpp>

namespace mpl {

namespace internal
{

/*
** `invert_pair`
**
** Given a key to value sequence pair, this function inserts into the given map
** a new value to key pair corresponding to each element in the original value
** sequence pair.
*/

template <class Key, class Value, class Map>
struct invert_pair_impl
{
	using type = typename insert_impl<
		true, Value, Key, sequence<>, Map
	>::type;
};

template <class Key, class T, class... Ts, class Map>
struct invert_pair_impl<
	Key,
	sequence<T, Ts...>,
	Map
>
{
	using t = typename insert_impl<
		true, T, Key, sequence<>, Map
	>::type;

	using type = typename invert_pair_impl<
		Key, sequence<Ts...>, t
	>::type;
};

template <class Key, class T, class Map>
struct invert_pair_impl<Key, sequence<T>, Map>
{
	using type = typename insert_impl<
		true, T, Key, sequence<>, Map
	>::type;
};

template <class Key, class Value, class Map>
using invert_pair =
typename invert_pair_impl<
	Key, Value, Map
>::type;

}

/*
** `invert`
** 
** Given an explicit map, the `invert` function constructs a new multimap
** consisting of the unique value-to-key pairs.
*/

template <class Head, class Map>
struct invert_impl;

template <class Head, class Key, class Value, class... Pairs>
struct invert_impl<
	Head,
	sequence<sequence<Key, Value>, Pairs...>
>
{
	using t = internal::invert_pair<Key, Value, Head>;
	using type = typename invert_impl<t, sequence<Pairs...>>::type;
};

template <class Head, class Key, class Value>
struct invert_impl<
	Head,
	sequence<sequence<Key, Value>>
>
{
	using type = internal::invert_pair<Key, Value, Head>;
};

template <class Map>
using invert = typename invert_impl<sequence<>, Map>::type;

}

#endif
