/*
** File Name:	module.hpp
** Author:	Aditya Ramesh
** Date:	07/15/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z0D8274E6_5C59_4EAE_A9D0_D83E87C7BF49
#define Z0D8274E6_5C59_4EAE_A9D0_D83E87C7BF49

#include <utility>
#include <vector>

#include <boost/range/algorithm.hpp>
#include <boost/utility/string_ref.hpp>
#include <ccbase/utility/accessors.hpp>
#include <ccbase/unit_test/result.hpp>

namespace cc {
namespace detail {

class module
{
public:
	using list           = std::vector<result>;
	using iterator       = typename list::iterator;
	using const_iterator = typename list::const_iterator;
private:
	list m_results{};
	size_t m_line;
	const boost::string_ref m_name{};
	const boost::string_ref m_desc{};
public:
	explicit module() noexcept {}

	explicit module(const boost::string_ref name, const size_t line)
	noexcept : m_line{line}, m_name{name} {}

	explicit module(
		const boost::string_ref name,
		const size_t line,
		const boost::string_ref desc
	) noexcept : m_line{line}, m_name{name}, m_desc{desc} {}

	DEFINE_COPY_GETTER(line, m_line)
	DEFINE_COPY_GETTER(name, m_name)
	DEFINE_COPY_GETTER(description, m_desc)

	template <class... Ts>
	void add_result(Ts&&... ts)
	{ m_results.emplace_back(std::forward<Ts>(ts)...); }

	size_t passed() const
	{
		return boost::count_if(m_results,
			[](const result& r) { return r.passed(); });
	}

	size_t failed() const
	{
		return boost::count_if(m_results,
			[](const result& r) { return !r.passed(); });
	}

	unsigned total() const
	{ return m_results.size(); }

	iterator begin() noexcept { return m_results.begin(); }
	iterator end() noexcept { return m_results.end(); }
	const_iterator cbegin() const noexcept { return m_results.cbegin(); }
	const_iterator cend() const noexcept { return m_results.cend(); }
};

typename module::iterator
begin(module& m) noexcept
{ return m.begin(); }

typename module::iterator
end(module& m) noexcept
{ return m.end(); }

typename module::const_iterator
cbegin(const module& m) noexcept
{ return m.cbegin(); }

typename module::const_iterator
cend(const module& m) noexcept
{ return m.cend(); }

}}

#endif
