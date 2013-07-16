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
#include <vector>
#include <ccbase/format.hpp>
#include <ccbase/internal/module.hpp>
#include <ccbase/internal/modules.hpp>
#include <ccbase/internal/result.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Unfortunately, `BOOST_PP_VARIADIC_SIZE` is not enabled for Clang, so we use
// our own implementation instead. For our use cases, we only need to be able to
// count a few arguments.

#define CC_COUNT(...) CC_COUNT_IMPL(__VA_ARGS__, 3, 2, 1)
#define CC_COUNT_IMPL(_1, _2, _3, N, ...) N

#define module(...) \
	BOOST_PP_CAT(module_impl_, CC_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define module_impl_1(name)                               \
	static const bool BOOST_PP_CAT(temp_, __LINE__) = \
	cc::internal::modules::add(name, __LINE__);       \
	static void BOOST_PP_CAT(module_, __COUNTER__)()

#define module_impl_2(name, description)                         \
	static const bool BOOST_PP_CAT(temp_, __LINE__) =        \
	cc::internal::modules::add(name, __LINE__, description); \
	static void BOOST_PP_CAT(module_, __COUNTER__)()

#define require(x)                                        \
	static const bool BOOST_PP_CAT(temp_, __LINE__) = \
	cc::internal::modules::require(__LINE__, #x, (x))

#define DECL(z, n, text) \
	BOOST_PP_CAT(text, n)();

#define suite(description)                                                     \
	int main(int argc, char** argv)                                        \
	{                                                                      \
		if (                                                           \
			argc <= 1 || (argc == 3 &&                             \
			cc::internal::equal(argv[1], "-v") ||                  \
			cc::internal::equal(argv[1], "--verbosity"))           \
		) {                                                            \
			BOOST_PP_REPEAT_FROM_TO(0, __COUNTER__, DECL, module_) \
		}                                                              \
		return cc::internal::parse_flags(argc, argv, description);     \
	}

namespace cc
{
namespace internal
{

enum class verbosity : unsigned
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

static bool
equal(const char* a, const char* b)
{
	return std::strcmp(a, b) == 0;
}

static std::string
get_suite()
{
	std::string s = __FILE__;
	auto f = s.find_last_of("/\\");
	if (f == std::string::npos) {
		f = 0;
	}
	else {
		++f;
	}
	auto l = s.find_last_of(".");
	if (l == std::string::npos) {
		l = s.size();
	}
	return s.substr(f, l - f);
}

static int
print_error(int argc, char** argv, const std::string msg)
{
	cc::writeln(std::cerr, "{0}", msg);
	cc::writeln(std::cerr, "Please type \"{0} --help\" for a list of "
		"options.", argv[0]);
	return EXIT_FAILURE;
}

static int
run_modules(const verbosity v)
{
	unsigned p{0};
	unsigned t{0};
	auto suite = get_suite();
	for (auto& m : modules{}) {
		p += m.passed();
		t += m.total();
		if (v == verbosity::medium) {
			for (const auto& r : m) {
				if (!r) {
					cc::println("Failure in module \"{0}\", "
					"line {1}: \"{2}\".", m.name(), r.line(),
					r.source());
				}
			}
		}
		else if (v == verbosity::high) {
			for (const auto& r : m) {
				cc::println("{0} in module \"{1}\", line {2}: "
				"\"{3}\".", r ? "Success" : "Failure", m.name(),
				r.line(), r.source());
			}
		}
		cc::println("Summary for module \"{0}\": {1} of {2} "
			"assertions passed.", m.name(), m.passed(),
			m.total());
	}
	cc::println("Summary for suite \"{0}\": {1} of {2} assertions "
		"passed.", suite, p, t);
	return EXIT_SUCCESS;
}

static int
print_help()
{
	print(help_message + 1);
	return EXIT_SUCCESS;
}

static int
list_modules(const char* d)
{
	if (d != nullptr) {
		println("Suite \"{0}\": {1}", get_suite(), d);
	}
	else {
		println("Suite \"{0}\"", get_suite());
	}
	for (const auto& m : modules{}) {
		if (m.description() != nullptr) {
			println("Module \"{0}\": {1}", m.name(), m.description());
		}
		else {
			println("Module \"{0}\"", m.name(), m.description());
		}
	}
	return EXIT_SUCCESS;
}

static int
parse_flags(int argc, char** argv, const char* d = nullptr)
{
	if (argc <= 1) {
		return run_modules(verbosity::low);
	}
	else if (argc <= 3) {
		if (
			equal(argv[1], "-h") ||
			equal(argv[1], "--help")
		) {
			return print_help();
		}
		else if (
			equal(argv[1], "-l") ||
			equal(argv[1], "--list-modules")
		) {
			return list_modules(d);
		}
		else if (
			equal(argv[1], "-v") ||
			equal(argv[1], "--verbosity")
		) {
			if (argc < 3) {
				auto s = cc::format("Error: expected verbosity "
					"level after \"{0}\" flag.", argv[1]);
				return print_error(argc, argv, s);
			}
			if (equal(argv[2], "low")) {
				return run_modules(verbosity::low);
			}
			else if (equal(argv[2], "medium")) {
				return run_modules(verbosity::medium);
			}
			else if (equal(argv[2], "high")) {
				return run_modules(verbosity::high);
			}
			else {
				auto s = cc::format("Error: invalid verbosity "
					"level \"{0}\".", argv[2]);
				return print_error(argc, argv, s);
			}
		}
		else {
			auto s = cc::format("Error: unrecognized flag \"{0}\".",
				argv[1]);
			return print_error(argc, argv, s);
		}
	}
	else {
		return print_error(argc, argv, "Error: too many flags.");
	}
}

}
}

#endif
