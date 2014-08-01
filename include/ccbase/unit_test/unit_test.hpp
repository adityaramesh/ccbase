/*
** File Name:	unit_test.hpp
** Author:	Aditya Ramesh
** Date:	12/18/2012
** Contact:	_@adityaramesh.com
**
** This file implements some basic unit-testing functionality. Each file
** functions as a suite, and contains a number of modules. Each module is
** intended to test the behavior of one component of your software. A typical
** unit test would look like this:
**
**	module("Test 1")
**	{
**		require(true);
**	}
**
**	module("Test 2", "This module has a description.")
**	{
**		require(false);
**	}
**
**	// This declaration must always appear last in the file.
**	suite("This is an example test suite.")
**
** The executable resulting from compiling the unit test source file hasd
** various command-line options that can be acccessed by specifying the `--help`
** flag.
*/

#ifndef Z474488B0_98AB_4098_886B_372A345C5121
#define Z474488B0_98AB_4098_886B_372A345C5121

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <vector>
#include <ccbase/format.hpp>
#include <ccbase/platform.hpp>
#include <ccbase/unit_test/module.hpp>
#include <ccbase/unit_test/module_list.hpp>
#include <ccbase/unit_test/result.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

/*
** The purpose of the 0 in the argument list is only to ensure that there is at
** least one variadic argument for `CC_VARIADIC_SIZE_IMPL`. Otherwise, the code
** is not standards-compliant.
*/
#define CC_VARIADIC_SIZE(...) CC_VARIADIC_SIZE_IMPL(__VA_ARGS__, 4, 3, 2, 1, 0)
#define CC_VARIADIC_SIZE_IMPL(_1, _2, _3, _4, N, ...) N

#define module(...) \
	BOOST_PP_CAT(module_impl_, CC_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)

#define module_impl_1(name)                                         \
	static const bool CC_UNUSED BOOST_PP_CAT(temp_, __LINE__) = \
	cc::detail::module_list::add_module(name, __LINE__);        \
	static void BOOST_PP_CAT(module_, __COUNTER__)()

#define module_impl_2(name, description)                                  \
	static const bool CC_UNUSED BOOST_PP_CAT(temp_, __LINE__) =       \
	cc::detail::module_list::add_module(name, __LINE__, description); \
	static void BOOST_PP_CAT(module_, __COUNTER__)()

#define require(x)                                                  \
	static const bool CC_UNUSED BOOST_PP_CAT(temp_, __LINE__) = \
	cc::detail::module_list::add_result(__LINE__, #x, (x))

#define DECL(z, n, text) \
	BOOST_PP_CAT(text, n)();

/*
** The label is needed here, because we can only mention `__COUNTER__` once.
*/
#define suite(description)                                                     \
	int main(int argc, char** argv)                                        \
	{                                                                      \
		if (argc <= 1) {                                               \
	generate:                                                              \
			BOOST_PP_REPEAT_FROM_TO(0, __COUNTER__, DECL, module_) \
		}                                                              \
		else if (argc == 3) {                                          \
			auto arg1 = boost::string_ref{argv[1]};                \
			if (arg1 == "-v" || arg1 == "--verbosity") {           \
				goto generate;                                 \
			}                                                      \
		}                                                              \
		return cc::detail::parse_flags(argc, argv, description);       \
	}

namespace cc {
namespace detail {

enum class verbosity
{
	low,
	medium,
	high
};

static constexpr char help_message[] = R"(
Options:
-h        --help
-l        --list-modules
-v        --verbosity [low, medium, high]
)";

boost::string_ref get_suite(const boost::string_ref prog)
{
	auto f = prog.find_last_of("/\\");
	if (f == boost::string_ref::npos) {
		f = 0;
	}
	else {
		++f;
	}

	auto l = prog.find_last_of(".");
	if (l == boost::string_ref::npos) {
		l = prog.size();
	}
	return prog.substr(f, l - f);
}

int print_error(int, char** argv, const std::string msg)
{
	cc::writeln(std::cerr, "$", msg);
	cc::writeln(std::cerr, "Please type \"$ --help\" for a list of "
		"options.", argv[0]);
	return EXIT_FAILURE;
}

int run_modules(const boost::string_ref prog, verbosity v)
{
	auto passed = 0;
	auto total = 0;
	auto suite = get_suite(prog);

	for (auto& m : module_list{}) {
		passed += m.passed();
		total += m.total();
		if (v == verbosity::medium) {
			for (const auto& res : m) {
				if (!res.passed()) {
					cc::println("Failure in module \"$\", "
					"line $: \"$\".", m.name(), res.line(),
					res.source());
				}
			}
		}
		else if (v == verbosity::high) {
			for (const auto& res : m) {
				cc::println("$ in module \"$\", line $: \"$\".",
				res.passed() ? "Success" : "Failure", m.name(),
				res.line(), res.source());
			}
		}
		cc::println("Summary for module \"$\": $ of $ "
			"assertions passed.", m.name(), m.passed(),
			m.total());
	}
	cc::println("Summary for suite \"$\": $ of $ assertions "
		"passed.", suite, passed, total);
	return EXIT_SUCCESS;
}

int print_help()
{
	// XXX why is there +1 here?
	print(help_message + 1);
	return EXIT_SUCCESS;
}

int list_modules(
	const boost::string_ref prog,
	const boost::string_ref desc
)
{
	if (desc.length() > 0) {
		println("Suite \"$\": $.", get_suite(prog), desc);
	}
	else {
		println("Suite \"$\".", get_suite(prog));
	}

	for (const auto& m : module_list{}) {
		if (m.description().length() > 0) {
			println("Module \"$\": $.", m.name(), m.description());
		}
		else {
			println("Module \"$\".", m.name(), m.description());
		}
	}
	return EXIT_SUCCESS;
}

int parse_flags(int argc, char** argv, const char* d = nullptr)
{
	if (argc <= 1) {
		return run_modules(argv[0], verbosity::low);
	}
	else if (argc <= 3) {
		auto arg1 = boost::string_ref{argv[1]};

		if (arg1 == "-h" || arg1 == "--help") {
			return print_help();
		}
		else if (arg1 == "-l" || arg1 == "--list-modules") {
			return list_modules(argv[0], d);
		}
		else if (arg1 == "-v" || arg1 == "--verbosity") {
			if (argc < 3) {
				auto s = cc::format("Error: expected verbosity "
					"level after \"$\" flag.", arg1);
				return print_error(argc, argv, s);
			}

			auto arg2 = boost::string_ref{argv[2]};
			if (arg2 == "low") {
				return run_modules(argv[0], verbosity::low);
			}
			else if (arg2 == "medium") {
				return run_modules(argv[0], verbosity::medium);
			}
			else if (arg2 == "high") {
				return run_modules(argv[0], verbosity::high);
			}
			else {
				auto s = cc::format("Error: invalid verbosity "
					"level \"$\".", argv[2]);
				return print_error(argc, argv, s);
			}
		}
		else {
			auto s = cc::format("Error: unrecognized flag \"$\".", arg1);
			return print_error(argc, argv, s);
		}
	}
	else {
		return print_error(argc, argv, "Error: too many flags.");
	}
}

}}

#endif
