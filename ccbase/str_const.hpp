/*
** File Name:	str_const.hpp
** Author:	Aditya Ramesh
** Date:	07/03/2013
** Contact:	_@adityaramesh.com
**
** # Introduction
**
** The `str_const` class provides a representation of a character array that can
** be queried and manipulated during compile time. It is based on Scott Schur's
** implementation of `str_const` given [here][new_tools].
**
** [new_tools]:
** https://github.com/boostcon/cppnow_presentations_2012/blob/master/wed/schurr_cpp11_tools_for_class_authors.pdf?raw=true
** "New Tools for Class and Library Authors"
*/

#ifndef Z6DB5E6FF_6826_4328_96A2_4798F500077A
#define Z6DB5E6FF_6826_4328_96A2_4798F500077A

#include <stdexcept>

class str_const
{
private:
	const char* const p_;
	const std::size_t s_;
public:
	template <std::size_t N>
	constexpr str_const(const char(&a)[N]) :
	p_{a}, s_{N - 1} {}

	constexpr char operator[](std::size_t n)
	{
		return n < s_ ? p_[n] : throw std::out_of_range{""};
	}

	constexpr std::size_t length()
	{
		return s_;
	}

	constexpr std::size_t size()
	{
		return s_;
	}

	constexpr operator const char*()
	{
		return p_;
	}
};

#endif
