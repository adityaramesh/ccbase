/*
** File Name:	type_traits.hpp
** Author:	Aditya Ramesh
** Date:	08/19/2013
** Contact:	_@adityaramesh.com
**
** Contains useful type traits not found in the standard library at the time of
** writing.
*/

#include <type_traits>

#ifndef ZAC34391A_54B3_4164_AD60_379C37934DEE
#define ZAC34391A_54B3_4164_AD60_379C37934DEE

namespace mpl
{

template <template <class...> class Template, class T>
struct is_specialization_of : std::false_type{};

template <template <class...> class Template, class... Args>
struct is_specialization_of<Template, Template<Args...>> : std::true_type{};

}

#endif
