/*
** File Name:	match.hpp
** Author:	Aditya Ramesh
** Date:	08/19/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZBA6E37A5_D27B_4A51_8578_94FD484FF597
#define ZBA6E37A5_D27B_4A51_8578_94FD484FF597

#include <mpl/bind.hpp>
#include <mpl/type_traits.hpp>

namespace mpl
{

template <template <class...> class Predicate, class Sequence>
struct contains_match;

template <template <class...> class Predicate, class T, class... Ts>
struct contains_match<Predicate, sequence<T, Ts...>>
{
	static constexpr auto value = Predicate<T>::value ||
	contains_match<Predicate, sequence<Ts...>>::value;
};

template <template <class...> class Predicate>
struct contains_match<Predicate, sequence<>> : std::false_type {};

template <template <class...> class Template, class Sequence>
struct contains_specialization_of;

template <template <class...> class Template, class T, class... Ts>
struct contains_specialization_of<Template, sequence<T, Ts...>>
{
	static constexpr auto value =
	is_specialization_of<Template, T>::value ||
	contains_specialization_of<Template, sequence<Ts...>>::value;
};

template <template <class...> class Template>
struct contains_specialization_of<Template, sequence<>> : std::false_type {};

}

#endif
