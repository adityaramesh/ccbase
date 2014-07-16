/*
** File Name: accessors.hpp
** Author:    Aditya Ramesh
** Date:      07/01/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z19D16F4C_D8F1_4708_ABE5_EBFBF560B64D
#define Z19D16F4C_D8F1_4708_ABE5_EBFBF560B64D

#include <utility>

#define DEFINE_REF_GETTER(name, member)                         \
	decltype(member)& name() { return member; }             \
	const decltype(member)& name() const { return member; }

#define DEFINE_COPY_GETTER(name, member) \
	decltype(member) name() const { return member; }

#define DEFINE_SETTER(self, name, member)     \
	self& name(const decltype(member)& x) \
	{                                     \
		this->member = x;             \
		return *this;                 \
	}                                     \
                                              \
	self& name(decltype(member)&& x)      \
	{                                     \
		this->member = std::move(x);  \
		return *this;                 \
	}

#define DEFINE_REF_GETTER_SETTER(self, name, member) \
	DEFINE_REF_GETTER(name, member)              \
	DEFINE_SETTER(self, name, member)

#define DEFINE_COPY_GETTER_SETTER(self, name, member) \
	DEFINE_COPY_GETTER(name, member)              \
	DEFINE_SETTER(self, name, member)

#endif
