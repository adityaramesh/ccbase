/*
** File Name: parse_natural.hpp
** Author:    Aditya Ramesh
** Date:      01/11/2015
** Contact:   _@adityaramesh.com
*/

#ifndef Z99B276F8_5038_4890_9062_3DA91F7D8E65
#define Z99B276F8_5038_4890_9062_3DA91F7D8E65

#include <ccbase/mpl/sequence_operations.hpp>

namespace cc {

template <uintmax_t Value, class Sequence>
struct parse_natural_helper;

template <uintmax_t Value, char... Ts>
struct parse_natural_helper<Value, std::integer_sequence<char, Ts...>>
{
	using tail = std::integer_sequence<char, Ts...>;
	static constexpr auto value = Value;
};

#define cc_define_specialization(digit, lit)                                                 \
	template <uintmax_t Value, char... Ts>                                               \
	struct parse_natural_helper<Value, std::integer_sequence<char, lit, Ts...>>          \
	{                                                                                    \
		using seq                   = std::integer_sequence<char, Ts...>;            \
		using next                  = parse_natural_helper<Value * 10 + digit, seq>; \
		using tail                  = typename next::tail;                           \
		static constexpr auto value = next::value;                                   \
	};

cc_define_specialization(0, '0')
cc_define_specialization(1, '1')
cc_define_specialization(2, '2')
cc_define_specialization(3, '3')
cc_define_specialization(4, '4')
cc_define_specialization(5, '5')
cc_define_specialization(6, '6')
cc_define_specialization(7, '7')
cc_define_specialization(8, '8')
cc_define_specialization(9, '9')

#undef cc_define_specialization

template <class Sequence>
struct parse_natural
{
	using valid_initial_chars = 
	std::integer_sequence<char, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'>;

	static_assert(
		Sequence::size() >= 1,
		"Sequence is empty."
	);

	static_assert(
		find<at<0, type_seq<Sequence>>, type_seq<valid_initial_chars>> != no_match,
		"Expected digit."
	);

	using helper = parse_natural_helper<0, Sequence>;
	using tail = typename helper::tail;
	using type = c<uintmax_t, helper::value>;
};

}

#endif
