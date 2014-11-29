/*
** File Name:	printable_types.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
**
** This file overloads `operator<<` for a few special types.
*/

#ifndef ZC216C426_75CD_4BC3_B7CC_5B44145C130F
#define ZC216C426_75CD_4BC3_B7CC_5B44145C130F

#include <cstdint>
#include <cstring>
#include <ostream>
#include <string>

#include <tuple>
#include <boost/optional.hpp>

namespace cc {
namespace detail {

template <uintmax_t Current, uintmax_t Max, class Stream, class Tuple>
struct print_tuple
{
	static void apply(Stream& os, const Tuple& t)
	{
		os << std::get<Current>(t) << ", ";
		return print_tuple<Current + 1, Max, Stream, Tuple>::apply(os, t);
	}
};

template <uintmax_t Max, class Stream, class Tuple>
struct print_tuple<Max, Max, Stream, Tuple>
{
	static void apply(Stream& os, const Tuple& t)
	{
		os << std::get<Max>(t) << ")";
	}
};

}

template <class Char, class Traits = std::char_traits<Char>, class... Us>
auto operator<<(std::basic_ostream<Char, Traits>& os, const std::tuple<Us...>& t)
noexcept -> decltype(os)
{
	if (sizeof...(Us) == 0) {
		return os;
	}

	os << "(";
	detail::print_tuple<0, sizeof...(Us) - 1, decltype(os), decltype(t)>::apply(os, t);
	return os;
}

template <class Char, class Traits = std::char_traits<Char>, class T>
auto operator<<(std::basic_ostream<Char, Traits>& os, const boost::optional<T>& x)
noexcept -> decltype(os)
{
	if (x) {
		return os << *x;
	}
	else {
		return os << "none";
	}
}

template <class Char, class Traits = std::char_traits<Char>>
auto operator<<(std::basic_ostream<Char, Traits>& os, const decltype(boost::none)&)
noexcept -> decltype(os)
{
	return os << "none";
}

template <class Char, class Traits = std::char_traits<Char>, class T, size_t N>
auto operator<<(std::basic_ostream<Char, Traits>& os, const std::array<T, N>& arr)
noexcept -> decltype(os)
{
	os << "[";
	for (auto i = size_t{0}; i != N - 1; ++i) {
		os << arr[i] << ", ";
	}
	return os << arr[N - 1] << "]";
}

}

#endif
