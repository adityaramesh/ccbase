/*
** File Name: parse_wsv.hpp
** Author:    Aditya Ramesh
** Date:      01/11/2015
** Contact:   _@adityaramesh.com
*/

#ifndef Z3365E669_B970_4CA8_880B_72A46AA9B6F7
#define Z3365E669_B970_4CA8_880B_72A46AA9B6F7

#include <ccbase/mpl/sequence_operations.hpp>
#include <ccbase/mpl/skip_whitespace.hpp>

namespace cc {

/*
** Note: the precondition is that each time a metafunction is called, `Ts...`
** does not begin with whitespace. Otherwise, it becomes difficult to deal with
** the row delimiters. Once we ensure that this precondition holds, everything
** falls into place pretty easily.
*/

template <
	class CurrentRow,
	class Result,
	class Integer,
	template <class> class ValueParser,
	char RowDelim,
	class Sequence
>
struct parse_wsv_helper;

template <
	class CurrentRow,
	class Result,
	class Integer,
	template <class> class ValueParser,
	char RowDelim
>
struct parse_wsv_helper<
	CurrentRow,
	Result,
	Integer,
	ValueParser,
	RowDelim,
	std::integer_sequence<char>
>
{
	using type = append<Result, CurrentRow>;
};

template <
	class CurrentRow,
	class Result,
	class Integer,
	template <class> class ValueParser,
	char RowDelim,
	char... Ts
>
struct parse_wsv_helper<
	CurrentRow,
	Result,
	Integer,
	ValueParser,
	RowDelim,
	std::integer_sequence<char, RowDelim, Ts...>
>
{
	using next_row   = seq<>;
	using new_result = append<Result, CurrentRow>;
	using new_seq    = skip_whitespace<std::integer_sequence<char, Ts...>>;
	using next       = parse_wsv_helper<
		next_row,
		new_result,
		Integer,
		ValueParser,
		RowDelim,
		new_seq
	>;
	using type = typename next::type;
};

template <
	class CurrentRow,
	class Result,
	class Integer,
	template <class> class ValueParser,
	char RowDelim,
	char... Ts
>
struct parse_wsv_helper<
	CurrentRow,
	Result,
	Integer,
	ValueParser,
	RowDelim,
	std::integer_sequence<char, Ts...>
>
{
	using seq     = std::integer_sequence<char, Ts...>;
	using parser  = ValueParser<seq>;
	using tail    = typename parser::tail;
	using field   = typename parser::type;
	using new_row = append<CurrentRow, field>;
	using new_seq = skip_whitespace<tail>;
	using next = parse_wsv_helper<
		new_row,
		Result,
		Integer,
		ValueParser,
		RowDelim,
		new_seq
	>;
	using type = typename next::type;
};

template <
	class Integer,
	template <class> class ValueParser,
	char RowDelim,
	class Sequence
>
using parse_wsv = typename parse_wsv_helper<
	seq<>,
	seq<>,
	Integer,
	ValueParser,
	RowDelim,
	skip_whitespace<Sequence>
>::type;

}

#endif
