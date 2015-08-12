/*
** File Name: mpl_test.cpp
** Author:    Aditya Ramesh
** Date:      01/11/2015
** Contact:   _@adityaramesh.com
*/

#include <type_traits>
#include <ccbase/unit_test.hpp>
#include <ccbase/mpl/list.hpp>
#include <ccbase/mpl/functional.hpp>
#include <ccbase/mpl/operations.hpp>
#include <ccbase/mpl/list_operations.hpp>
#include <ccbase/mpl/string_literal.hpp>

namespace mpl = cc::mpl;

module("test composition")
{
	using parse_natural = mpl::bind_back<
		mpl::quote<mpl::fold>,
		mpl::int_<0>,
		mpl::compose<
			mpl::quote<mpl::list>,
			mpl::uncurry<mpl::make_list<
				mpl::bind_front<mpl::quote<mpl::multiplies>, mpl::int_<10>>,
				mpl::bind_back<mpl::quote<mpl::minus>, mpl::char_<'0'>>
			>>,
			mpl::uncurry<mpl::quote<mpl::plus>>
		>
	>;

	using r1 = mpl::apply<
		parse_natural,
		mpl::to_types<std::integer_sequence<char, '1', '2', '3'>>
	>;

	static_assert(r1::value == 123, "");

	using r2 = mpl::zip_with<
		mpl::quote<mpl::plus>,
		mpl::range_c<int, 0, 2>,
		mpl::range_c<int, 0, 2>,
		mpl::range_c<int, 0, 2>
	>;

	using e1 = mpl::to_types<std::integer_sequence<int, 0, 3, 6>>;
	static_assert(std::is_same<r2, e1>::value, "");

	using l1 = mpl::to_types<std::index_sequence<1, 2, 3>>;
	using f1 = mpl::bind_back<mpl::quote<mpl::greater>, cc::mpl::size_t<2>>;
	using r3 = mpl::find_if<f1, l1>;
	static_assert(r3::value == 2, "");

	using r4 = mpl::slice_c<1, 1, l1>;
	static_assert(mpl::at_c<0, r4>::value == 2, "");

	using r5 = mpl::lists_same<l1, l1>;
	static_assert(r5::value == true, "");

	using r6 = mpl::starts_with<mpl::list<mpl::size_t<1>>, l1>;
	static_assert(r6::value == true, "");

	using r7 = mpl::max<mpl::int_<0>, mpl::int_<-1>, mpl::int_<1>>;
	using r8 = mpl::min<mpl::int_<0>, mpl::int_<-1>, mpl::int_<1>>;
	static_assert(r7::value == 1, "");
	static_assert(r8::value == -1, "");
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
** 		mpl::quote<mpl::fold>,
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
