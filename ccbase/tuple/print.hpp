/*
** File Name:	print.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZC216C426_75CD_4BC3_B7CC_5B44145C130F
#define ZC216C426_75CD_4BC3_B7CC_5B44145C130F

#include <cstring>
#include <ostream>
#include <tuple>
#include <string>

namespace cc {
namespace {

template <std::size_t Current, std::size_t Max, class Stream, class Tuple>
struct print_tuple
{
	static void apply(Stream& os, const Tuple t)
	{
		os << std::get<Current>(t) << ", ";
		return print_tuple<Current + 1, Max, Stream, Tuple>::apply(os, t);
	}
};

template <std::size_t Max, class Stream, class Tuple>
struct print_tuple<Max, Max, Stream, Tuple>
{
	static void apply(Stream& os, const Tuple t)
	{
		os << std::get<Max>(t) << ")";
	}
};

}

template <class T, class Traits = std::char_traits<T>, class... Us>
auto operator<<(std::basic_ostream<T, Traits>& os, const std::tuple<Us...> t)
noexcept -> decltype(os)
{
	if (sizeof...(Us) == 0) {
		return os;
	}

	os << "(";
	print_tuple<0, sizeof...(Us) - 1, decltype(os), decltype(t)>::apply(os, t);
	return os;
}

}

#endif
