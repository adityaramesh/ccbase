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
#include <ccbase/unit_test/result.hpp>

namespace cc {
namespace detail {

class module
{
public:
	using size_type = std::size_t;
	using list = std::vector<result>;
	using iterator = typename list::iterator;
	using const_iterator = typename list::const_iterator;
private:
	list r{};
	size_type l;
	const char* n{nullptr};
	const char* d{nullptr};
public:
	explicit module() noexcept {}

	explicit module(const char* n, const size_type l)
	noexcept : l{l}, n{n} {}

	explicit module(const char* n, const size_type l, const char* d)
	noexcept : l{l}, n{n}, d{d} {}

	size_type line() const { return l; }
	const char* name() const { return n; }
	const char* description() const { return d; }

	template <class... Ts>
	void add(Ts&&... ts)
	{
		r.emplace_back(std::forward<Ts>(ts)...);
	}

	unsigned passed() const
	{
		unsigned p{0};
		for (const auto& i : r) {
			p += i;
		}
		return p;
	}

	unsigned failed() const
	{
		unsigned f{0};
		for (const auto& i : r) {
			f += !i;
		}
		return f;
	}

	unsigned total() const
	{
		return r.size();
	}

	iterator begin() { return r.begin(); }
	iterator end() { return r.end(); }
	const_iterator cbegin() const { return r.cbegin(); }
	const_iterator cend() const { return r.cend(); }
};

typename module::iterator
begin(module m)
{
	return m.begin();
}

typename module::iterator
end(module m)
{
	return m.end();
}

typename module::const_iterator
cbegin(const module m)
{
	return m.cbegin();
}

typename module::const_iterator
cend(const module m)
{
	return m.cend();
}

}
}

#endif
