/*
** File Name:	module_list.hpp
** Author:	Aditya Ramesh
** Date:	07/15/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z84D931C7_5FDA_41C6_8372_6587A760C35A
#define Z84D931C7_5FDA_41C6_8372_6587A760C35A

#include <boost/range/algorithm.hpp>
#include <ccbase/unit_test/module.hpp>

namespace cc {
namespace detail {

class module_list
{
public:
	using list           = std::vector<module>;
	using iterator       = typename list::iterator;
	using const_iterator = typename list::const_iterator;
private:
	static std::vector<module> m_modules;
public:
	template <class... Ts>
	static bool add_module(Ts&&... ts)
	{
		m_modules.emplace_back(std::forward<Ts>(ts)...);
		return true;
	}

	template <class... Ts>
	static bool add_result(size_t line, Ts&&... ts)
	{
		/*
		** Each module spans a certain range of lines. We need to
		** iterate through the modules to find the one into which we
		** emplace the `result` object.
		*/
		auto it = boost::find_if(m_modules,
			[&](const module& m) { return m.line() >= line; });

		if (it == m_modules.end()) {
			m_modules.back().add_result(line, std::forward<Ts>(ts)...);
		}
		else {
			it->add_result(line, std::forward<Ts>(ts)...);
		}
		return true;
	}

	static iterator begin() { return m_modules.begin(); }
	static iterator end() { return m_modules.end(); }
	static const_iterator cbegin() { return m_modules.cbegin(); }
	static const_iterator cend() { return m_modules.cend(); }
};

std::vector<module> module_list::m_modules{};

typename module_list::iterator
begin(module_list& m)
{ return m.begin(); }

typename module_list::iterator
end(module_list& m)
{ return m.end(); }

typename module_list::const_iterator
cbegin(const module_list& m)
{ return m.cbegin(); }

typename module_list::const_iterator
cend(const module_list& m)
{ return m.cend(); }

}}

#endif
