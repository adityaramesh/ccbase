/*
** File Name:	result.hpp
** Author:	Aditya Ramesh
** Date:	07/15/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z267B316A_BF50_4FF8_A898_D95A04FD7914
#define Z267B316A_BF50_4FF8_A898_D95A04FD7914

#include <string>
#include <ccbase/format.hpp>

namespace cc {
namespace detail {

class result
{
public:
	using size_type = std::size_t;
private:
	std::string s;
	size_type l;
	bool b;
public:
	result(size_type l, const char* s, const bool b)
	noexcept : s{format("require($0)", s)}, l{l}, b{b} {}

	operator bool() const { return b; }
	const char* source() const { return s.c_str(); }
	size_type line() const { return l; }
};

}}

#endif
