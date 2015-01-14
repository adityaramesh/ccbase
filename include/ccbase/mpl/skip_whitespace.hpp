/*
** File Name: skip_whitespace.hpp
** Author:    Aditya Ramesh
** Date:      01/11/2015
** Contact:   _@adityaramesh.com
*/

#ifndef Z933851A7_BBBA_4352_854E_C6B8093E69D7
#define Z933851A7_BBBA_4352_854E_C6B8093E69D7

namespace cc {

template <class Sequence>
struct skip_whitespace_helper;

template <char... Ts>
struct skip_whitespace_helper<std::integer_sequence<char, Ts...>>
{ using tail = std::integer_sequence<char, Ts...>; };

#define nd_define_specialization(lit)                                          \
	template <char... Ts>                                                  \
	struct skip_whitespace_helper<std::integer_sequence<char, lit, Ts...>> \
	{                                                                      \
		using seq  = std::integer_sequence<char, Ts...>;               \
		using next = skip_whitespace_helper<seq>;                      \
		using tail = typename next::tail;                              \
	};

nd_define_specialization(' ')
nd_define_specialization('\t')

#undef nd_define_specialization

template <class Sequence>
using skip_whitespace = typename skip_whitespace_helper<Sequence>::tail;

}

#endif
