/*
** File Name:	module_list.hpp
** Author:	Aditya Ramesh
** Date:	07/15/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z84D931C7_5FDA_41C6_8372_6587A760C35A
#define Z84D931C7_5FDA_41C6_8372_6587A760C35A

#include <ccbase/unit_test/module.hpp>

namespace cc
{
namespace internal
{

class module_list
{
public:
	using size_type = typename result::size_type;
	using list = std::vector<module>;
	using iterator = typename list::iterator;
	using const_iterator = typename list::const_iterator;
private:
	static std::vector<module> l;
public:
	template <class... Ts>
	static bool add(Ts&&... ts)
	{
		l.emplace_back(std::forward<Ts>(ts)...);
		return true;
	}

	template <class... Ts>
	static bool require(const size_type line, Ts&&... ts)
	{
		unsigned i{0};
		do ++i; while (i < l.size() && l[i].line() < line);
		--i;
		l[i].add(line, std::forward<Ts>(ts)...);
		return true;
	}

	static iterator begin() { return l.begin(); }
	static iterator end() { return l.end(); }
	static const_iterator cbegin() { return l.cbegin(); }
	static const_iterator cend() { return l.cend(); }
};

std::vector<module> module_list::l{};

typename module_list::iterator
begin(module_list m)
{
	return m.begin();
}

typename module_list::iterator
end(module_list m)
{
	return m.end();
}

typename module_list::const_iterator
cbegin(const module_list m)
{
	return m.cbegin();
}

typename module_list::const_iterator
cend(const module_list m)
{
	return m.cend();
}

}
}

#endif
