/*
** File Name: ratio_literal.hpp
** Author:    Aditya Ramesh
** Date:      01/07/2015
** Contact:   _@adityaramesh.com
*/

#ifndef ZE92EBAFE_95B1_4471_9200_5DB1F8851CB0
#define ZE92EBAFE_95B1_4471_9200_5DB1F8851CB0

#include <ratio>
#include <ccbase/mpl/parse_ratio.hpp>
#include <ccbase/mpl/parse_wsv.hpp>

namespace cc {

template <class Scalar, class Ratio>
static constexpr auto cast = Scalar(Ratio::num) / Ratio::den;

}

template <class Char, Char... Ts>
constexpr auto operator"" _ratio()
{
	using seq = std::integer_sequence<Char, Ts...>;
	using result = typename cc::parse_ratio<seq>::type;
	return result{};
}

#define cc_ratio(x) decltype(#x ## _ratio)

#endif
