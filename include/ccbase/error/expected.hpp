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
** available [here][error_handling]. Support was later added for
** `expected<void>`, so that methods that return void can still take advantage
** of the this idiom. Finally, support for references was added, so that objects
** of type `expected<T&>` and `expected<const T&>` can now be created. The fact
** that generalized unions cannot contain references was alluded to in [this
** blog post][extending_expected], and the approach taken to rectify the problem
** is adapted from the one given in the blog post.
**
** # Introduction
** 
** From the horse's mouth: `expected<T>` is a variant type that either contains
** `T` or the exception that prevented its creation. It allows you to perform an
** action that may raise an exception, and postpone dealing with the exception
** until it is convenient. This approach essentially gives you the ability to
** return "arbitrarily rich error codes." See [Alexandrescu's
** talk][error_handling] for a great discussion of its uses, as well as a
** walkthrough of the design.
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
** changed to `attempt`. Methods that return values, pointers, references, and
** even void are all supported.
**
** 3. There is a specialization for `expected<void>`, with the obvious
** modifications.
**
** 4. There are specializations for `expected<T&>` and `expected<const T&>`, as
** described by [this blog post][extending_expected].
**
** [error_handling]:
** http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C
** "Alexandrescu's Talk on Systematic Error Handling"
**
** [extending_expected]:
** http://anto-nonco.blogspot.com/2013/03/extending-expected-to-deal-with.html
** "Extending `expected<T>` to Deal with References"
*/

#ifndef Z9F71ED6B_DBA6_4FFD_83F7_2D168D140002
#define Z9F71ED6B_DBA6_4FFD_83F7_2D168D140002

#include <cassert>
#include <exception>
#include <functional>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace cc {

template <class T>
struct expected_traits
{
	using storage   = T;
	using value     = T;
	using pointer   = T*;
	using reference = T&;
};

template <class T>
struct expected_traits<T&>
{
	using storage   = std::reference_wrapper<T>;
	using value     = T;
	using pointer   = T*;
	using reference = T&;
};

template <class T>
struct expected_traits<const T&>
{
	using storage   = std::reference_wrapper<const T>;
	using value     = T;
	using pointer   = const T*;
	using reference = const T&;
};

template <class> class expected;

template <class T>
class expected_base
{
	friend class expected<T>;

	using storage   = typename expected_traits<T>::storage;
	using value     = typename expected_traits<T>::value;
	using pointer   = typename expected_traits<T>::pointer;
	using reference = typename expected_traits<T>::reference;

	union
	{
		storage t_;
		std::exception_ptr p_;
	};

	bool valid_;
	#ifndef NDEBUG
		mutable bool read_{false};
	#endif

	/*
	** These constructors are used to create `expected` objects in valid
	** states.
	**
	** XXX: We cannot use curly brackets to initialize `t_`, because it will
	** fail for POD types. The curly bracket for POD types does something
	** different from the uniform initialization for other types. If we used
	** the curly bracket when `T` is POD type, the compiler would try to
	** convert `rhs` to the first field of `rhs`, rather than performing the
	** copy-construction.
	*/

	expected_base(value& rhs) noexcept : t_(rhs), valid_{true} {}
	expected_base(const value& rhs) noexcept : t_(rhs), valid_{true} {}
	expected_base(value&& rhs) noexcept : t_(std::move(rhs)), valid_{true} {}

	/*
	** These constructors are used to create `expected` objects in invalid
	** states.
	*/

	expected_base() noexcept : valid_{false}
	{
		new (&p_) std::exception_ptr{std::move(std::current_exception())};
	}
	
	expected_base(std::exception_ptr p) noexcept : valid_{false}
	{
		new (&p_) std::exception_ptr{std::move(p)};
	}

	template <class E>
	expected_base(const E& e,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, E
		>::type* = 0
	) noexcept : valid_{false}
	{
		if (typeid(e) != typeid(E)) {
			throw std::invalid_argument{"Slicing detected."};
		}
		new (&p_) std::exception_ptr{std::move(std::make_exception_ptr(e))};
	}

	expected_base(const expected_base& rhs) noexcept : valid_{rhs.valid_}
	{
		if (valid_) new(&t_) storage(rhs.t_);
		else new(&p_) std::exception_ptr{rhs.p_};
	}

	expected_base(expected_base&& rhs) noexcept : valid_{rhs.valid_}
	{
		if (valid_) new(&t_) storage(std::move(rhs.t_));
		else new(&p_) std::exception_ptr{std::move(rhs.p_)};
	}

	~expected_base()
	{
		if (valid_) t_.~storage();
		else p_.~exception_ptr();
		#ifndef NDEBUG
			assert(read_ && "Potentially unchecked exception.");
		#endif
	}

public:
	bool valid() const noexcept
	{
		#ifndef NDEBUG
			read_ = true;
		#endif
		return valid_;
	}

	reference get()
	{
		#ifndef NDEBUG
			read_ = true;
		#endif
		if (!valid_) std::rethrow_exception(p_);
		return t_;
	}

	const reference get() const
	{
		if (!valid_) std::rethrow_exception(p_);
		return t_;
	}

	std::exception_ptr exception()
	const noexcept
	{
		assert(!valid_);
		return p_;
	}

	void swap(expected_base& rhs) noexcept
	{
		if (valid_) {
			if (rhs.valid_) {
				using std::swap;
				swap(t_, rhs.t_);
			}
			else {
				// We need to either move `rhs`'s
				// `std::exception_ptr` or our `storage` object
				// into a temporary. When we mutate a member of
				// the union of either the LHS or the RHS, we
				// will invalidate the other member of that
				// union. We make the assumption that choosing
				// to load whichever of the two is smaller
				// (either `storage` or `std::exception_ptr`)
				// into a temporary will be most efficient.
				if (sizeof(storage) < sizeof(std::exception_ptr)) {
					auto t = std::move(t_);
					new (&p_) std::exception_ptr{rhs.p_};
					new (&rhs.t_) storage(std::move(t));
				}
				else {
					auto t = std::move(rhs.p_);
					new (&rhs.t_) storage(std::move(t_));
					new (&p_) std::exception_ptr{t};
				}
				valid_ = false;
				rhs.valid_ = true;
			}
		}
		else {
			if (rhs.valid_) {
				if (sizeof(storage) < sizeof(std::exception_ptr)) {
					auto t = std::move(rhs.t_);
					new (&rhs.p_) std::exception_ptr{p_};
					new (&t_) storage(std::move(t));
				}
				else {
					auto t = std::move(p_);
					new (&t_) storage(std::move(rhs.t_));
					new (&rhs.p_) std::exception_ptr{t};
				}
				rhs.valid_ = false;
				valid_ = true;
			}
			else {
				std::swap(p_, rhs.p_);
			}
		}
	}

	/*
	** Checks whether this object has an exception of type `E`.
	*/
	template <class E>
	bool has_exception()
	const noexcept
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

template <class T>
class expected : public expected_base<T>
{
private:
	friend class expected_base<T>;
	using base = expected_base<T>;
public:
	expected(const T& rhs) noexcept : base{rhs} {}
	expected(T&& rhs) noexcept : base{std::move(rhs)} {}

	expected() noexcept : base{} {}
	expected(std::exception_ptr p) noexcept : base{p} {}

	template <class E>
	expected(const E& e,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, E
		>::type* = 0
	) noexcept : base{e} {}

	expected(const expected& rhs) noexcept :
	base{static_cast<const base&>(rhs)} {}

	expected(expected&& rhs) noexcept :
	base{static_cast<base&&>(rhs)} {}

	void swap(expected& rhs) noexcept
	{
		base::swap(static_cast<base&>(rhs));
	}
};

template <class T>
class expected<T&> : public expected_base<T&>
{
private:
	friend class expected_base<T&>;
	using base = expected_base<T&>;
public:
	expected(T& rhs) noexcept : base{rhs} {}

	expected() noexcept : base{} {}
	expected(std::exception_ptr p) noexcept : base{p} {}

	template <class E>
	expected(const E& e,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, E
		>::type* = 0
	) noexcept : base{e} {}

	expected(const expected& rhs) noexcept : base{static_cast<const base&>(rhs)} {}
	expected(expected&& rhs) noexcept : base{static_cast<base&&>(rhs)} {}

	void swap(expected& rhs) noexcept
	{
		base::swap(static_cast<base&>(rhs));
	}
};

template <class T>
class expected<const T&> : public expected_base<const T&>
{
private:
	friend class expected_base<const T&>;
	using base = expected_base<const T&>;
public:
	expected(const T& rhs) noexcept : base{rhs} {}

	expected() noexcept : base{} {}
	expected(std::exception_ptr p) noexcept : base{p} {}

	template <class E>
	expected(const E& e,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, E
		>::type* = 0
	) noexcept : base{e} {}

	expected(const expected& rhs) noexcept : base{static_cast<const base&>(rhs)} {}
	expected(expected&& rhs) noexcept : base{static_cast<base&&>(rhs)} {}

	void swap(expected& rhs) noexcept
	{
		base::swap(static_cast<base&>(rhs));
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
	#ifndef NDEBUG
		mutable bool read_{false};
	#endif
public:
	expected(bool) noexcept : valid_{true} {}

	/*
	** These constructors are used to create `expected` objects in invalid
	** states.
	*/

	expected() noexcept : valid_{false}
	{
		new (&p_) std::exception_ptr{std::move(std::current_exception())};
	}
	
	expected(std::exception_ptr p) noexcept : valid_{false}
	{
		new (&p_) std::exception_ptr{std::move(p)};
	}

	template <class E>
	expected(const E& e,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, E
		>::type* = 0
	) noexcept : valid_{false}
	{
		if (typeid(e) != typeid(E)) {
			throw std::invalid_argument{"Slicing detected."};
		}
		new (&p_) std::exception_ptr{std::move(std::make_exception_ptr(e))};
	}

	expected(const expected& rhs) noexcept : valid_{rhs.valid_}
	{
		if (!valid_) new(&p_) std::exception_ptr{rhs.p_};
	}

	expected(expected&& rhs) noexcept : valid_{rhs.valid_}
	{
		if (!valid_) new(&p_) std::exception_ptr{std::move(rhs.p_)};
	}

	~expected()
	{
		// We need the `using` statement here, because `::~` does not
		// parse, so we would not be able to not write
		// `p_.::~exception_ptr()`.
		if (!valid_) p_.~exception_ptr();
		#ifndef NDEBUG
			assert(read_ && "Potentially unchecked exception.");
		#endif
	}

	bool valid() const noexcept
	{
		#ifndef NDEBUG
			read_ = true;
		#endif
		return valid_;
	}
	
	void get() const
	{
		#ifndef NDEBUG
			read_ = true;
		#endif
		if (!valid_) std::rethrow_exception(p_);
	}

	std::exception_ptr exception() const noexcept
	{
		assert(!valid_);
		return p_;
	}

	void swap(expected& rhs) noexcept
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
				std::swap(p_, rhs.p_);
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
** We need to use SFINAE, because `expected<void>` objects have different
** construction semantics than the other specializations. This is because we
** cannot pass `void` as an argument.
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

template <class F>
auto attempt(F f) ->
typename std::enable_if<
	std::is_same<decltype(f()), void>::value,
	expected<void>
>::type
{
	try {
		f();
	}
	catch (...) {
		return {};
	}
	return { true };
}

}

#endif
