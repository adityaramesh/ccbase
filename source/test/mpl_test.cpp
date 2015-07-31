/*
** File Name: mpl_test.cpp
** Author:    Aditya Ramesh
** Date:      01/11/2015
** Contact:   _@adityaramesh.com
*/

#include <type_traits>
#include <ccbase/unit_test.hpp>
#include <ccbase/mpl/functional.hpp>

/*
#include <ccbase/mpl/parse_natural.hpp>
#include <ccbase/mpl/parse_ratio.hpp>
#include <ccbase/mpl/skip_whitespace.hpp>
#include <ccbase/mpl/parse_wsv.hpp>
#include <ccbase/utility/ratio_literal.hpp>
*/

module("test composition")
{
	using namespace cc::mpl;

	using parse_natural = bind_back<
		quote<foldl>,
		int_<0>,
		compose<
			quote<list>,
			uncurry<combine<
				bind_front<quote<multiplies>, int_<10>>,
				bind_back<quote<minus>, char_<'0'>>
			>>,
			uncurry<quote<plus>>
		>
	>;
	using r1 = apply<
		parse_natural,
		to_types<std::integer_sequence<char, '1', '2', '3'>>
	>;
	static_assert(r1::value == 123, "");

	using r2 = zip_with<
		make_nary<quote<plus>>,
		list<
			range_c<int, 0, 2>,
			range_c<int, 0, 2>,
			range_c<int, 0, 2>
		>
	>;
	using expected = to_types<std::integer_sequence<int, 0, 3, 6>>;
	static_assert(std::is_same<r2, expected>::value, "");

	using l1 = to_types<std::index_sequence<1, 2, 3>>;
	using f = bind_back<quote<greater>, cc::mpl::size_t<2>>;
	using r3 = find_first_if<f, l1>;
	static_assert(r3::value == 2, "");

	using r4 = slice_c<1, 1, l1>;
	static_assert(at_c<0, r4>::value == 2, "");
}

/*
** Example of bad use of higher-order metaprogramming:
**
** using apply_two_cycle =
** mpl::compose<
** 	mpl::quote<mpl::list>,
** 	mpl::select_c<0, 1, 1>,
** 	mpl::uncurry<mpl::combine<
** 		mpl::quote_trait<mpl::id>,
** 		mpl::quote<mpl::front>,
** 		mpl::quote<mpl::back>
** 	>>,
** 	mpl::bind_front<
** 		mpl::quote<mpl::repeat_n>,
** 		mpl::int_<3>
** 	>,
** 	mpl::uncurry<mpl::combine<
** 		mpl::quote<mpl::front>,
** 		mpl::quote_trait<mpl::id>,
** 		mpl::select_c<0, 2, 1>
** 	>>,
** 	mpl::group_range_c<1, 2>,
** 	mpl::uncurry<mpl::combine<
** 		mpl::quote_trait<mpl::id>,
** 		mpl::bind_back<
** 			mpl::quote<mpl::transform>,
** 			mpl::compose<
** 				mpl::bind_front<
** 					mpl::quote<mpl::repeat_n>,
** 					mpl::int_<3>
** 				>,
** 				mpl::uncurry<mpl::combine<
** 					mpl::bind_front<mpl::quote<mpl::at>, mpl::int_<1>>,
** 					mpl::compose<
** 						mpl::select_c<2, 0>,
** 						mpl::uncurry<mpl::quote<mpl::at>>,
** 						mpl::quote<get_coordinate>
** 					>,
** 					mpl::compose<
** 						mpl::select_c<1, 0>,
** 						mpl::uncurry<mpl::quote<mpl::at>>
** 					>
** 				>>,
** 				mpl::group_range_c<1, 2>,
** 				mpl::uncurry<mpl::combine<
** 					mpl::quote_trait<mpl::id>,
** 					mpl::uncurry<mpl::quote<set_coordinate>>
** 				>>
** 			>
** 		>
** 	>>,
** 	mpl::select_c<1, 0>,
** 	mpl::uncurry<mpl::bind_back<
** 		mpl::quote<mpl::foldl>,
** 		mpl::compose<
** 			mpl::combine<
** 				mpl::quote<mpl::list>,
** 				mpl::quote_trait<mpl::id>
** 			>,
** 			mpl::quote<mpl::join>,
** 			mpl::select_c<1, 2, 0>,
** 			mpl::uncurry<mpl::quote<mpl::set_at>>
** 		>
** 	>>
** >;
*/

suite("metaparse test");
