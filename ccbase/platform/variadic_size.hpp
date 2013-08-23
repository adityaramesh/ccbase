/*
** File Name:	variadic_size.hpp
** Author:	Aditya Ramesh
** Date:	07/28/2013
** Contact:	_@adityaramesh.com
**
** Support for empty-argument detection was adapted from the approach given in
** this [blog post][empty_macro].
**
** [empty_macro]:
** http://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments/
** "Detect Empty Macro Arguments"
*/

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/if.hpp>

#ifndef Z03BE52C2_8635_41BE_84BD_1348AE5FBE39
#define Z03BE52C2_8635_41BE_84BD_1348AE5FBE39

#define CC_LAST_ARGUMENT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, \
	_13, _14, _15, _16, _17, _18, _19, _20, ...) _20

#define CC_HAS_COMMA(...)                                                    \
	CC_LAST_ARGUMENT(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
	1, 1, 1, 1, 1, 0)

#define CC_TRIGGER_PARENTHESIS(...) ,

#define CC_IS_EMPTY(...)                                            \
	CC_IS_EMPTY_IMPL(                                           \
		CC_HAS_COMMA(__VA_ARGS__),                          \
		CC_HAS_COMMA(CC_TRIGGER_PARENTHESIS __VA_ARGS__),   \
		CC_HAS_COMMA(__VA_ARGS__ ()),                       \
		CC_HAS_COMMA(CC_TRIGGER_PARENTHESIS __VA_ARGS__ ()) \
	)

#define CC_IS_EMPTY_IMPL(_1, _2, _3, _4) \
	CC_HAS_COMMA(CC_PASTE_5(CC_IS_EMPTY_CASE_, _1, _2, _3, _4))

#define CC_IS_EMPTY_CASE_0001 ,

#define CC_PASTE_5(_1, _2, _3, _4, _5) \
	_1 ## _2 ## _3 ## _4 ## _5

#define CC_VARIADIC_SIZE(...)                                                  \
	BOOST_PP_IF(                                                           \
		BOOST_PP_EQUAL(CC_IS_EMPTY(__VA_ARGS__), 1), 0,                \
		CC_VARIADIC_SIZE_IMPL(__VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, \
		13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)                     \
	)

#define CC_VARIADIC_SIZE_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, \
	_12, _13, _14, _15, _16, _17, _18, _19, _20, N, ...) N

#endif
