/*
** File Name:	enumerate_map.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
**
** The `enumerate` takes an implicit map with coordinates as keys, and generates
** an explicit representation of its mappings by iterating through each index
** within the map's extents.
*/

#ifndef Z0C2AF2EC_93F8_4C12_978E_84622EE28609
#define Z0C2AF2EC_93F8_4C12_978E_84622EE28609

#include <mpl/enumerate_range.hpp>
#include <mpl/map.hpp>

namespace mpl {

template <class Map>
struct enumerate_map_impl
{
	using extents = typename Map::extents;
	using keys = enumerate_range<extents>;
	using values = generate_range<
		bind<1, Map, get>::template rebind, extents
	>;
	using type = elementwise<sequence, keys, values>;
};

template <class Map>
using enumerate_map = typename enumerate_map_impl<Map>::type;

}

#endif
