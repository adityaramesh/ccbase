/*
** File Name:	print.hpp
** Author:	Aditya Ramesh
** Date:	08/12/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z18CE7F37_CE09_4418_857C_204E01CC8104
#define Z18CE7F37_CE09_4418_857C_204E01CC8104

#include <ostream>
#undef major
#undef minor

#include <ccbase/platform/architecture.hpp>
#include <ccbase/platform/compiler.hpp>
#include <ccbase/platform/operating_system.hpp>

namespace cc
{

std::ostream& operator<<(std::ostream& os, const architecture rhs)
{
	if (rhs == architecture::arm) {
		os << "arm ";
	}
	else if (rhs == architecture::itanium) {
		os << "itanium ";
	}
	else if (rhs == architecture::x86) {
		os << "x86 ";
	}
	else {
		return os << "unknown";
	}

	if (rhs.word_size() != 0) {
		return os << "(" << rhs.word_size() << "-bit)";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const compiler_version rhs)
{
	if (rhs.major() == 0 && rhs.minor() == 0 && rhs.patch() == 0) {
		return os << "unknown";
	}
	else {
		return os << rhs.major() << "." << rhs.minor() << "." << rhs.patch();
	}
}

std::ostream& operator<<(std::ostream& os, const compiler rhs)
{
	if (rhs == compiler::clang) {
		os << "Clang ";
	}
	else if (rhs == compiler::comeau) {
		os << "Comeau ";
	}
	else if (rhs == compiler::gcc) {
		os << "GCC ";
	}
	else if (rhs == compiler::icc) {
		os << "ICC ";
	}
	else if (rhs == compiler::msvc) {
		os << "MSVC ";
	}
	return os << "(version " << rhs.version() << ")";
}

std::ostream& operator<<(std::ostream& os, const operating_system rhs)
{
	if (rhs == operating_system::linux_distribution) {
		return os << "GNU/Linux distribution";
	}
	else if (rhs == operating_system::os_x) {
		return os << "OS X";
	}
	else if (rhs == operating_system::windows) {
		return os << "Windows";
	}
	else {
		return os << "unknown";
	}
}

}

#endif
