/*
** File Name:	map.hpp
** Author:	Aditya Ramesh
** Date:	07/12/2013
** Contact:	_@adityaramesh.com
** 
** Two kinds of maps are supported: implicit maps and explicit multimaps.
** Implicit maps are maps whose values are computed by a member template struct
** called `get`. Implicit maps only map coordinates to unique values. Explicit
** maps are sequences of sequences, and can map types to sequences of arbitrary
** types.
*/

#ifndef Z4D435E2C_CEF3_4CB8_B438_59E5D3D9BEF9
#define Z4D435E2C_CEF3_4CB8_B438_59E5D3D9BEF9

#include <type_traits>
#include <mpl/sequence.hpp>

namespace mpl {

/*
** `get`
*/

// This is the implementation for implcit maps.

template <class Key, class Map>
struct get_impl
{
	using type = typename Map::template get<Key>::type;
};

// This is the implementation for explicit maps.

template <class Key, class S>
struct explicit_get_impl;

template <
	class    Key,
	class    CurrentKey,
	class    CurrentValue,
	class... Pairs
>
struct explicit_get_impl<
	Key,
	sequence<sequence<CurrentKey, CurrentValue>, Pairs...>
>
{
	using type =
	typename explicit_get_impl<
		Key,
		sequence<Pairs...>
	>::type;
};

template <
	class    Key,
	class    CurrentValue,
	class... Pairs
>
struct explicit_get_impl<
	Key,
	sequence<sequence<Key, CurrentValue>, Pairs...>
>
{
	using type = CurrentValue;
};

// If the compiler attempts to instantiate this specialization, then the key was
// not found in the given map, and a compilation error should be issued.

template <class Key>
struct explicit_get_impl<Key, sequence<>>;

template <class Key, class... Pairs>
struct get_impl<Key, sequence<Pairs...>>
{
	using type =
	typename explicit_get_impl<
		Key, sequence<Pairs...>
	>::type;
};

template <class Key, class Map>
using get = typename get_impl<Key, Map>::type;

/*
** `is_multimap`
*/

template <class Map>
struct is_multimap : std::false_type {};

template <class Key, class... Values, class... Pairs>
struct is_multimap<
	sequence<sequence<Key, sequence<Values...>>, Pairs...>
> : std::true_type {};

/*
** `insert`
**
** If the given map is a multimap, then this function does the following:
** - If a sequence corresponding to the given key exists and does not contain
** the given value, then the given value is pushed to the end of the sequence.
** - If a sequence corresponding to the given key exists but contains the given
** value, then no modification is performed.
** - If a sequence corresponding to the given key does not exist, then a new
** key-value pair is appeded to the end of the map, with the sequence containing
** the given value as the only element.
**
** If the given map is not a multimap (i.e. keys are associated with unique
** values), then this function does the following:
** - If a pair corresponding to the given key exists, then the value of that
** pair is set to the given value.
** - If a pair corresponding to the given key does not exist, then a new
** key-value pair is appended to the end of the map.
**
** Due to limitations in the language, this function does not work for implicit
** maps.
*/

template <bool IsMultimap, class Key, class Value, class Head, class Tail>
struct insert_impl;

// This is the implementation for multimaps.

template <
	class    Key,
	class    Value,
	class    Head,
	class    CurrentKey,
	class    CurrentValue,
	class... Pairs
>
struct insert_impl<
	true,
	Key,
	Value,
	Head,
	sequence<sequence<CurrentKey, CurrentValue>, Pairs...>
>
{
	using head = append<sequence<CurrentKey, CurrentValue>, Head>;

	using type =
	typename insert_impl<
		true,
		Key,
		Value,
		head,
		sequence<Pairs...>
	>::type;
};

template <
	class    Key,
	class    Value,
	class    Head,
	class    CurrentValue,
	class... Pairs
>
struct insert_impl<
	true,
	Key,
	Value,
	Head,
	sequence<sequence<Key, CurrentValue>, Pairs...>
>
{
	using value =
	typename std::conditional<
		contains<Value, CurrentValue>::value,
		CurrentValue,
		append<Value, CurrentValue>
	>::type;

	using pair = sequence<Key, value>;
	using type = cat<Head, sequence<pair, Pairs...>>;
};

template <
	class Key,
	class Value,
	class Head
>
struct insert_impl<
	true,
	Key,
	Value,
	Head,
	sequence<>
>
{
	using type = append<sequence<Key, sequence<Value>>, Head>;
};

// This is the implementation for regular maps.

template <
	class    Key,
	class    Value,
	class    Head,
	class    CurrentKey,
	class    CurrentValue,
	class... Pairs
>
struct insert_impl<
	false,
	Key,
	Value,
	Head,
	sequence<sequence<CurrentKey, CurrentValue>, Pairs...>
>
{
	using head = append<sequence<CurrentKey, CurrentValue>, Head>;

	using type =
	typename insert_impl<
		false,
		Key,
		Value,
		head,
		sequence<Pairs...>
	>::type;
};

template <
	class    Key,
	class    Value,
	class    Head,
	class    CurrentValue,
	class... Pairs
>
struct insert_impl<
	false,
	Key,
	Value,
	Head,
	sequence<sequence<Key, CurrentValue>, Pairs...>
>
{
	using pair = sequence<Key, Value>;
	using type = cat<Head, sequence<pair, Pairs...>>;
};

template <
	class Key,
	class Value,
	class Head
>
struct insert_impl<
	false,
	Key,
	Value,
	Head,
	sequence<>
>
{
	using type = append<sequence<Key, Value>, Head>;
};

template <class Key, class Value, class Map>
using insert = typename insert_impl<
	is_multimap<Map>::value,
	Key,
	Value,
	sequence<>,
	Map
>::type;

/*
** `replace`
**
** The `replace` function works similarly to `insert`, except that it replaces
** any values associated given with the key by the provided value. The effect of
** `replace` is not the same as the effect of `erase` followed by `insert`,
** because the latter would always cause the new pair to be appended to the end
** of the map.
*/

template <bool IsMultimap, class Key, class Value, class Head, class Tail>
struct replace_impl;

template <
	class    Key,
	class    Value,
	class    Head,
	class    CurrentKey,
	class    CurrentValue,
	class... Pairs
>
struct replace_impl<
	true,
	Key,
	Value,
	Head,
	sequence<sequence<CurrentKey, CurrentValue>, Pairs...>
>
{
	using head = append<sequence<CurrentKey, CurrentValue>, Head>;

	using type =
	typename replace_impl<
		true,
		Key,
		Value,
		head,
		sequence<Pairs...>
	>::type;
};

template <
	class    Key,
	class    Value,
	class    Head,
	class    CurrentValue,
	class... Pairs
>
struct replace_impl<
	true,
	Key,
	Value,
	Head,
	sequence<sequence<Key, CurrentValue>, Pairs...>
>
{
	using pair = sequence<Key, sequence<Value>>;
	using type = cat<Head, sequence<pair, Pairs...>>;
};

template <
	class Key,
	class Value,
	class Head
>
struct replace_impl<
	true,
	Key,
	Value,
	Head,
	sequence<>
>
{
	using type = Head;
};

// This is the implementation for regular maps.

template <
	class    Key,
	class    Value,
	class    Head,
	class    CurrentKey,
	class    CurrentValue,
	class... Pairs
>
struct replace_impl<
	false,
	Key,
	Value,
	Head,
	sequence<sequence<CurrentKey, CurrentValue>, Pairs...>
>
{
	using head = append<sequence<CurrentKey, CurrentValue>, Head>;

	using type =
	typename replace_impl<
		false,
		Key,
		Value,
		head,
		sequence<Pairs...>
	>::type;
};

template <
	class    Key,
	class    Value,
	class    Head,
	class    CurrentValue,
	class... Pairs
>
struct replace_impl<
	false,
	Key,
	Value,
	Head,
	sequence<sequence<Key, CurrentValue>, Pairs...>
>
{
	using pair = sequence<Key, Value>;
	using type = cat<Head, sequence<pair, Pairs...>>;
};

template <
	class Key,
	class Value,
	class Head
>
struct replace_impl<
	false,
	Key,
	Value,
	Head,
	sequence<>
>
{
	using type = Head;
};

template <class Key, class Value, class Map>
using replace = typename replace_impl<
	is_multimap<Map>::value,
	Key,
	Value,
	sequence<>,
	Map
>::type;

/*
** `erase`
** 
** The `erase` function removes the mapping associated with the given key from
** the map, if such a mapping exists.
*/

template <class Key, class Head, class Tail>
struct erase_impl;

template <
	class    Key,
	class    Head,
	class    CurrentKey,
	class    CurrentValue,
	class... Pairs
>
struct erase_impl<
	Key,
	Head,
	sequence<sequence<CurrentKey, CurrentValue>, Pairs...>
>
{
	using pair = sequence<CurrentKey, CurrentValue>;
	using head = append<pair, Head>;

	using type =
	typename erase_impl<
		Key,
		head,
		sequence<Pairs...>
	>::type;
};

template <
	class    Key,
	class    Head,
	class    CurrentValue,
	class... Pairs
>
struct erase_impl<
	Key,
	Head,
	sequence<sequence<Key, CurrentValue>, Pairs...>
>
{
	using type = cat<Head, sequence<Pairs...>>;
};

template <class Key, class Head>
struct erase_impl<Key, Head, sequence<>>
{
	using type = Head;
};

template <class Key, class Map>
using erase = typename erase_impl<Key, sequence<>, Map>::type;

/*
** `contains_key`
*/

template <class Key, class Map>
struct contains_key;

template <
	class Key,
	class CurrentKey,
	class CurrentValue,
	class... Pairs
>
struct contains_key<
	Key,
	sequence<sequence<CurrentKey, CurrentValue>, Pairs...>
>
{
	static constexpr bool value =
	contains_key<Key, sequence<Pairs...>>::value;
};

template <
	class Key,
	class CurrentValue,
	class... Pairs
>
struct contains_key<
	Key,
	sequence<sequence<Key, CurrentValue>, Pairs...>
> : std::true_type {};

template <class Key>
struct contains_key<Key, sequence<>> : std::false_type {};

/*
** `contains_value`
*/

template <class Value, class Map>
struct contains_value;

template <
	class Value,
	class CurrentKey,
	class CurrentValue,
	class... Pairs
>
struct contains_value<
	Value,
	sequence<sequence<CurrentKey, CurrentValue>, Pairs...>
>
{
	static constexpr bool value =
	contains_value<Value, sequence<Pairs...>>::value;
};

template <
	class Value,
	class CurrentKey,
	class... Pairs
>
struct contains_value<
	Value,
	sequence<sequence<CurrentKey, Value>, Pairs...>
> : std::true_type {};

template <class Value>
struct contains_value<Value, sequence<>> : std::false_type {};

}

#endif
