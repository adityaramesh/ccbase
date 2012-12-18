/*
** File Name:	unit_test.hpp
** Author:	Aditya Ramesh
** Date:	12/18/2012
** Contact:	_@adityaramesh.com
**
** This file implements some very basic unit-testing functionality. Units tests
** are composed of file-based suites, in which each suite contains a set of
** modules. Suites are designed to encapsulate a set of related tests, where
** each test is implemented within a module block. By default, assertion
** information is printed only when assertions fail. If XU_UNIT_TEST_VERBOSE is
** defined, information will be printed about every assertion in the suite,
** regardless of whether each assertion passed or failed. A typical test file
** would be structured as follows:
**
**	XU_BEGIN_MODULE(test1)
**		XU_ASSERT(1);
**	XU_END_MODULE(test1)
**	
**	XU_BEGIN_MODULE(test2)
**		XU_ASSERT(0);
**	XU_END_MODULE(test2)
**	
**	XU_BEGIN_SUITE(example)
**		test1();
**		test2();
**	XU_END_SUITE(example)
*/

#ifndef Z474488B0_98AB_4098_886B_372A345C5121
#define Z474488B0_98AB_4098_886B_372A345C5121

#include <cstddef>
#include <string>
#include <tuple>
#include <vector>
#include <xutil/format.hpp>

namespace xu {
namespace unit_test {
	using result_type = std::tuple<size_t, size_t, std::string>;
	using result_list = std::vector<result_type>;
}}

#define XU_ASSERT(x) results.push_back(std::make_tuple((x), __LINE__, #x))

#ifdef XU_UNIT_TEST_VERBOSE

#define XU_BEGIN_MODULE(name)                               \
	static void name()                                  \
	{                                                   \
		std::size_t successes = 0;                  \
		xu::unit_test::result_list results;         \
		xu::println("Entering module {0}.", #name);

#define XU_END_MODULE(name)                                                           \
	for (const auto& x : results) {                                               \
		successes += std::get<0>(x);                                          \
		xu::println("{0} in file \"{1}\", module \"{2}\", at line {3}: {4}.", \
			std::get<0>(x) ? "Success" : "Failure", __FILE__, #name,      \
			std::get<1>(x), std::get<2>(x));                              \
	}                                                                             \
	xu::println("Exiting module \"{0}\"; {1} of {2} assertions passed.",          \
		#name, successes, size(results));                                     \
}

#define XU_BEGIN_SUITE(name)                               \
	int main()                                         \
	{                                                  \
		xu::println("Entering suite {0}.", #name);

#define XU_END_SUITE(name)                                \
		xu::println("Exiting suite {0}.", #name); \
		return EXIT_SUCCESS;                      \
	}

#else

#define XU_BEGIN_MODULE(name)                       \
	static void name()                          \
	{                                           \
		xu::unit_test::result_list results; \
			
#define XU_END_MODULE(name)                                                               \
	for (const auto& x : results) {                                                   \
		if (std::get<0>(x)) continue;                                             \
		xu::println("Failure in file \"{0}\", module \"{1}\", at line {2}: {3}.", \
			__FILE__, #name, std::get<1>(x), std::get<2>(x));                 \
	}                                                                                 \
}

#define XU_BEGIN_SUITE(name) \
	int main()           \
	{

#define XU_END_SUITE(name)           \
		return EXIT_SUCCESS; \
	}

#endif

#endif
