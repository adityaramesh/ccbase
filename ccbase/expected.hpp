/*
** File Name:	expected.hpp
** Author:	Aditya Ramesh
** Date:	03/08/2013
** Contact:	_@adityaramesh.com
**
** # Preface
**
** This class is based on Andrei Alexandrescu's implementation of `expected<T>`,
** which he discussed in a talk at C++ Next 2012 called "Systematic Error
** Handling". The video and slides of the talk (which contain his code) are
** available
** [here](http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C).
**
** # Introduction
** 
** From the horse's mouth: `expected<T>` is a variant type that either contains
** `T` or the exception that prevented its creation. It allows you to perform
** some action that may raise an exception, and postpone dealing with the
** exception until it is convenient. This approach essentially gives you the
** ability to return "arbitrarily rich error codes." See Alexandrescu's talk for
** a great discussion of its uses, as well as a walkthrough of the design.
**
** This implementation of `expected<T>` is based on Alexandrescu's, but it has
** some modifications, namely:
**
** 1. It is assumed that the stored `std::exception_ptr` references a subclass
** of `std::exception`. This allows the user to construct `expected` objects
** directly from exceptions. With the original design, ambiguous situations may
** arise if both constructors that accepted `T` and the exception type are
** provided. In particular, if `T` is implicitly convertible to the type of the
** exception (or vice versa), there would be an ambiguous constructor overload
** resolution. This issue is circumvented with this assumption, so that the
** constructors work as intended in all situations.
**
** 2. I made Alexandrescu's `fromCode` function global, and used `decltype` to
** infer the return type of functor or lambda. The name of the function has been
** changed to `attempt`. The return type has been wrapped in an
** `std::enable_if`, so that if the user-provided functor returns void (as a
** result of a programming error), the compiler barfs less.
**
** 3. There is a specialization for `expected<void>`, with the obvious
** modifications.
*/

#ifndef Z9F71ED6B_DBA6_4FFD_83F7_2D168D140002
#define Z9F71ED6B_DBA6_4FFD_83F7_2D168D140002

#include <exception>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace cc
{

template <class T>
class expected
{
	union
	{
		T t_;
		std::exception_ptr p_;
	};

	bool valid_;
	
public:
	/*
	** These constructors are used to create `expected` objects in valid
	** states.
	*/

	expected(const T& rhs) : t_{rhs}, valid_{true} {}
	expected(T&& rhs) : t_{std::move(rhs)}, valid_{true} {}
	
	/*
	** These constructors are used to create `expected` objects in invalid
	** states.
	*/

	expected() : valid_{false}
	{
		new (&p_) std::exception_ptr{std::move(std::current_exception())};
	}
	
	expected(std::exception_ptr p) : valid_{false}
	{
		new (&p_) std::exception_ptr{std::move(p)};
	}

	template <class E>
	expected(const E& e,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, E
		>::type* = 0
	) : valid_{false}
	{
		if (typeid(e) != typeid(E)) {
			throw std::invalid_argument{"Slicing detected."};
		}
		new (&p_) std::exception_ptr{std::move(std::make_exception_ptr(e))};
	}

	expected(const expected& rhs) : valid_{rhs.valid_}
	{
		if (valid_) new(&t_) T{rhs.t_};
		else new(&p_) std::exception_ptr{rhs.p_};
	}

	expected(expected&& rhs) : valid_{rhs.valid_}
	{
		if (valid_) new(&t_) T{std::move(rhs.t_)};
		else new(&p_) std::exception_ptr{std::move(rhs.p_)};
	}

	~expected()
	{
		// We need the `using` statement here, because `::~` does not
		// parse, so we would not be able to not write
		// `p_.::~exception_ptr()`.
		using std::exception_ptr;
		if (valid_) t_.~T();
		else p_.~exception_ptr();
	}

	bool valid() const
	{
		return valid_;
	}

	T& get()
	{
		if (!valid_) std::rethrow_exception(p_);
		return t_;
	}

	const T& get() const
	{
		if (!valid_) std::rethrow_exception(p_);
		return t_;
	}

	void swap(expected& rhs)
	{
		if (valid_) {
			if (rhs.valid_) {
				using std::swap;
				swap(t_, rhs.t_);
			}
			else {
				// We need to either move `rhs`'s
				// `std::exception_ptr` or our `T` into a
				// temporary. When we mutate a member of the
				// union of either the LHS or the RHS, we will
				// invalidate the other member of that union. We
				// make the assumption that choosing to load
				// whichever of the two is smaller (either `T`
				// or `std::exception_ptr`) into a temporary
				// will be most efficient.
				if (sizeof(T) < sizeof(std::exception_ptr)) {
					auto t = std::move(t_);
					new (&p_) std::exception_ptr{rhs.p_};
					new (&rhs.t_) T{std::move(t)};
				}
				else {
					auto t = std::move(rhs.p_);
					new (&rhs.t_) T{std::move(t_)};
					new (&p_) std::exception_ptr{t};
				}
				valid_ = false;
				rhs.valid_ = true;
			}
		}
		else {
			if (rhs.valid_) {
				if (sizeof(T) < sizeof(std::exception_ptr)) {
					auto t = std::move(rhs.t_);
					new (&rhs.p_) std::exception_ptr{p_};
					new (&t_) T{std::move(t)};
				}
				else {
					auto t = std::move(p_);
					new (&t_) T{std::move(rhs.t_)};
					new (&rhs.p_) std::exception_ptr{t};
				}
				rhs.valid_ = false;
				valid_ = true;
			}
			else {
				p_.swap(rhs.p_);
			}
		}
	}

	/*
	** Checks whether this object has an exception of type `E`.
	*/
	template <class E>
	bool has_exception() const
	{
		try {
			if (!valid_) std::rethrow_exception(p_);
		}
		catch (const E& e) {
			return true;
		}
		catch (...) {}
		return false;
	}
};

/*
** You should use this specialization when you want to return an expected object
** from a method that would otherwise return `void`. This specialization does
** not store any expected type, and so the `get` member returns void, and throws
** in the case that this object is invalid.  Other functions also have the code
** involving the expected type stripped from them. Because this object does not
** store any value type, it will use slightly less memory and fewer instructions
** than `expected<bool>`.
*/

template <>
class expected<void>
{
	std::exception_ptr p_;
	bool valid_;
public:
	expected(bool) : valid_{true} {}

	/*
	** These constructors are used to create `expected` objects in invalid
	** states.
	*/

	expected() : valid_{false}
	{
		new (&p_) std::exception_ptr{std::move(std::current_exception())};
	}
	
	expected(std::exception_ptr p) : valid_{false}
	{
		new (&p_) std::exception_ptr{std::move(p)};
	}

	template <class E>
	expected(const E& e,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, E
		>::type* = 0
	) : valid_{false}
	{
		if (typeid(e) != typeid(E)) {
			throw std::invalid_argument{"Slicing detected."};
		}
		new (&p_) std::exception_ptr{std::move(std::make_exception_ptr(e))};
	}

	expected(const expected& rhs) : valid_{rhs.valid_}
	{
		if (!valid_) new(&p_) std::exception_ptr{rhs.p_};
	}

	expected(expected&& rhs) : valid_{rhs.valid_}
	{
		if (!valid_) new(&p_) std::exception_ptr{std::move(rhs.p_)};
	}

	~expected()
	{
		// We need the `using` statement here, because `::~` does not
		// parse, so we would not be able to not write
		// `p_.::~exception_ptr()`.
		using std::exception_ptr;
		if (!valid_) p_.~exception_ptr();
	}

	bool valid() const
	{
		return valid_;
	}
	
	void get() const
	{
		if (!valid_) std::rethrow_exception(p_);
	}

	void swap(expected& rhs)
	{
		if (valid_) {
			// If both `rhs` and `lhs` are valid, then we do not
			// have to do anything.
			if (!rhs.valid_) {
				new (&p_) std::exception_ptr{rhs.p_};
				valid_ = false;
				rhs.valid_ = true;
			}
		}
		else {
			if (rhs.valid_) {
				new (&rhs.p_) std::exception_ptr{p_};
				rhs.valid_ = false;
				valid_ = true;
			}
			else {
				p_.swap(rhs.p_);
			}
		}
	}

	/*
	** Checks whether this object has an exception of type `E`.
	*/
	template <class E>
	bool has_exception() const
	{
		try {
			if (!valid_) std::rethrow_exception(p_);
		}
		catch (const E& e) {
			return true;
		}
		catch (...) {}
		return false;
	}
};

/*
** We wrap the return type in an `std::enable_if`, so that the compiler does not
** barf (as much) when the callable object `f` returns `void`.
*/

template <class F>
auto attempt(F f) ->
typename std::enable_if<
	!std::is_same<decltype(f()), void>::value,
	expected<decltype(f())>
>::type
{
	try {
		return expected<decltype(f())>{f()};
	}
	catch (...) {
		return {};
	}
}

}

#endif
