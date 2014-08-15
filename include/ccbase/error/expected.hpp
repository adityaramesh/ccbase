/*
** File Name:	expected.hpp
** Author:	Aditya Ramesh
** Date:	03/08/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z9F71ED6B_DBA6_4FFD_83F7_2D168D140002
#define Z9F71ED6B_DBA6_4FFD_83F7_2D168D140002

#include <memory>
#include <utility>
#include <typeinfo>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <ccbase/utility/enum_bitmask.hpp>

namespace cc {

struct in_place_t {};
struct no_error_t {};

static constexpr auto in_place = in_place_t{};
static constexpr auto no_error = no_error_t{};

class bad_expected_type final : std::logic_error
{
	using std::logic_error::logic_error;
};

enum class expected_state : uint8_t
{
	invalid = 0x0,
	valid   = 0x1,
	#ifndef CC_NO_DEBUG
		// Used to keep track of whether the state of the expected
		// object was checked prior to destruction.
		dismissed = 0x2,
	#endif
};

DEFINE_ENUM_BITWISE_OPERATORS(expected_state)

template <class T>
struct expected_traits
{
	using storage         = T;
	using value           = T;
	using pointer         = T*;
	using const_pointer   = const T*;
	using reference       = T&;
	using const_reference = const T&;
};

template <class T>
struct expected_traits<T&>
{
	using storage         = std::reference_wrapper<T>;
	using value           = T;
	using pointer         = T*;
	using const_pointer   = const T*;
	using reference       = T&;
	using const_reference = const T&;
};

template <class T>
struct expected_traits<const T&>
{
	using storage         = std::reference_wrapper<const T>;
	using value           = T;
	using pointer         = const T*;
	using const_pointer   = const T*;
	using reference       = const T&;
	using const_reference = const T&;
};

template <class T>
class expected final
{
	static_assert(std::is_nothrow_destructible<T>::value, "");

	using storage         = typename expected_traits<T>::storage;
	using value           = typename expected_traits<T>::value;
	using pointer         = typename expected_traits<T>::pointer;
	using const_pointer   = typename expected_traits<T>::const_pointer;
	using reference       = typename expected_traits<T>::reference;
	using const_reference = typename expected_traits<T>::const_reference;

	union {
		storage m_val;
		std::exception_ptr m_ptr;
	};
	mutable expected_state m_state;
public:
	template <
		bool B = std::is_default_constructible<storage>::value,
		typename std::enable_if<B, int>::type = 0
	>
	expected()
	noexcept(std::is_nothrow_default_constructible<storage>::value)
	: m_val{} {}

	/*
	** NOTE: We cannot use curly brackets to initialize `m_val`, because
	** initialization will fail for POD types. The curly bracket for POD
	** types does something different from the uniform initialization for
	** non-POD types. If we were to use the curly bracket when `T` is POD
	** type, the compiler would try to assign `rhs` to the first field of
	** `T`, rather than performing the copy-construction.
	*/
	template <
		bool B = std::is_copy_constructible<storage>::value,
		typename std::enable_if<B, int>::type = 0
	>
	expected(const value& rhs)
	noexcept(std::is_nothrow_copy_constructible<storage>::value)
	: m_val(rhs), m_state{expected_state::valid} {}

	/*
	** Disallow creation of references to temporaries.
	*/
	template <
		bool B = std::is_move_constructible<storage>::value &&
			!std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0
	>
	expected(value&& rhs)
	noexcept(std::is_nothrow_move_constructible<storage>::value)
	: m_val(rhs), m_state{expected_state::valid} {}

	/*
	** There is no need to use `enable_if` here, because this is a template
	** function. We will let the compiler error out normally.
	*/
	template <class... Args>
	expected(const in_place_t&, Args&&... args)
	noexcept(std::is_nothrow_constructible<storage, Args...>::value) :
	m_val(std::forward<Args>(args)...), m_state{expected_state::valid} {}

	expected(const std::exception_ptr& ptr)
	noexcept : m_state{expected_state::invalid}
	{ ::new (&m_ptr) std::exception_ptr{ptr}; }

	expected(std::exception_ptr&& ptr)
	noexcept : m_state{expected_state::invalid}
	{ ::new (&m_ptr) std::exception_ptr{std::move(ptr)}; }

	template <class E,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, int
		>::type = 0>
	expected(const E& e)
	#ifdef CC_NO_DEBUG
		noexcept
	#endif
	: m_state{expected_state::invalid}
	{
		#ifndef CC_NO_DEBUG
			if (typeid(e) != typeid(E)) {
				throw std::logic_error{"exception slicing "
					"detected during construction"};
			}
		#endif
		::new (&m_ptr) std::exception_ptr{std::make_exception_ptr(e)};
	}

	template <
		bool B = std::is_copy_constructible<storage>::value,
		typename std::enable_if<B, int>::type = 0
	>
	expected(const expected& rhs)
	noexcept(std::is_noexcept_copy_constructible<storage>::value)
	: m_state{rhs.m_state}
	{
		if (*this) {
			::new(std::addressof(m_val)) storage(rhs.m_val);
		}
		else {
			::new(&m_ptr) std::exception_ptr{rhs.m_ptr};
		}
	}

	/*
	** It's ok if `T` is a reference in this case, because we are
	** potentially copying a reference from `rhs`, but never a reference to
	** a temporary object.
	*/
	template <
		bool B = std::is_move_constructible<storage>::value,
		typename std::enable_if<B, int>::type = 0
	>
	expected(expected&& rhs)
	noexcept(std::is_noexcept_move_constructible<storage>::value)
	: m_state{m_state}
	{
		if (*this) {
			::new(std::addressof(m_val)) storage(std::move(rhs.m_val));
		}
		else {
			::new(&m_ptr) std::exception_ptr{std::move(rhs.m_ptr)};
		}
	}

	template <
		bool B = std::is_copy_assignable<storage>::value,
		typename std::enable_if<B, int>::type = 0
	>
	expected& operator=(const expected& rhs)
	#ifdef CC_NO_DEBUG
		noexcept(
			std::is_nothrow_copy_constructible<storage>::value &&
			std::is_nothrow_copy_assignable<storage>::value
		)
	#else
	{
		check_if_dismissed();

		if (*this) {
			if (*rhs) {
				m_val = rhs.m_val;
			}
			else {
				m_val.~storage();
				::new(m_ptr) (&m_ptr)
					std::exception_ptr{rhs.m_ptr};
			}
		}
		else {
			if (*rhs) {
				m_ptr.~exception_ptr();
				::new(m_val) (std::addressof(m_val))
					storage{rhs.m_val};
			}
			else {
				m_ptr = rhs.m_ptr;
			}
		}
	}

	/*
	** It's ok if `T` is a reference in this case, because we are
	** potentially copying a reference from `rhs`, but never a reference to
	** a temporary object.
	*/
	template <bool B = std::is_move_assignable<storage>::value,
		 typename std::enable_if<B, int>::type = 0>
	expected& operator=(expected&& rhs)
	#ifdef CC_NO_DEBUG
		noexcept(
			std::is_nothrow_move_constructibile<storage>::value &&
			std::is_nothrow_move_assignable<storage>::value
		)
	#else
	{
		check_if_dismissed();

		if (*this) {
			if (*rhs) {
				m_val = std::move(rhs.m_val);
			}
			else {
				m_val.~storage();
				::new(m_ptr) (&m_ptr)
					std::exception_ptr{std::move(rhs.m_ptr)};
			}
		}
		else {
			if (*rhs) {
				m_ptr.~exception_ptr();
				::new(m_val) (std::addressof(m_val))
					storage{std::move(rhs.m_val)};
			}
			else {
				m_ptr = std::move(rhs.m_ptr);
			}
		}
	}

	~expected()
	{
		/*
		** Make sure we release any resources before potentially
		** throwing because this object was not dismissed.
		*/
		if (*this) {
			m_val.~storage();
		}
		else {
			m_ptr.~exception_ptr();
		}
		check_if_dismissed();
	}
private:
	void check_if_dismissed() const
	#ifdef CC_NO_DEBUG
		noexcept
	#endif
	{
		#ifndef CC_NO_DEBUG
			if (!(m_state & expected_state::dismissed)) {
				throw std::logic_error{"unchecked expected object"};
			}
		#endif
	}

	[[noreturn]] void rethrow_exception() const noexcept(false)
	{
		if (m_ptr == nullptr) {
			throw std::bad_expected_type{"expected object is "
				"invalid, but the exception pointer has "
				"been moved"};
		}
		std::rethrow_exception(m_ptr);
	}
public:
	[[noreturn]] void raise() const noexcept(false)
	{
		if (*this) {
			throw std::bad_expected_type{"attempt to throw "
				"exception from valid expected object"};
		}
		rethrow_exception();
	}

	void dismiss() const noexcept
	{
		#ifndef CC_NO_DEBUG
			m_state |= expected_state::dismissed;
		#else
	}

	operator bool() const noexcept
	{
		dismiss();
		return !!(m_state & expected_state::valid);
	}

	reference value() &
	{
		if (!*this) rethrow_exception();
		return m_val;
	}

	const_reference value() const&
	{
		if (!*this) rethrow_exception();
		return m_val;
	}

	reference operator*() & { return value(); }
	const_reference operator*() const& { return value(); }
	reference operator*() & { return value(); }
	const_reference operator*() const& { return value(); }

	/*
	** We don't need to check for constness here, because the return value
	** has the correct constness.
	*/
	template <
		bool B = !std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0
	>
	pointer operator->()
	{
		if (!*this) rethrow_exception();
		return std::addressof(m_val);
	}

	template <
		bool B = !std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0
	>
	const_pointer operator->() const
	{
		if (!*this) rethrow_exception();
		return std::addressof(m_val);
	}

	/*
	** Remarks:
	**   - We don't need to check for constness here, because the return
	**   value has the correct constness.
	**   - Since this function returns a pointer to the value, we disallow
	**   invocation on rvalue references.
	*/
	template <
		bool B = std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0
	>
	pointer operator->() &
	{
		if (!*this) rethrow_exception();
		return std::addressof(m_val.get());
	}

	template <
		bool B = std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0
	>
	const_pointer operator->() const&
	{
		if (!*this) rethrow_exception();
		return std::addressof(m_val.get());
	}

	template <
		bool B = !std::is_reference<T>::value &&
		         !std::is_const<T>::value,
		typename std::enable_if<B, int>::type = 0
	>
	T&& value() &&
	{
		if (!*this) rethrow_exception();
		return std::move(m_val);
	}

	template <
		bool B = std::is_reference<T>::value &&
			!std::is_const<
				typename std::remove_reference<T>::type
			>::value,
		typename std::enable_if<B, int>::type = 0
	>
	T&& value() &&
	{
		if (!*this) rethrow_exception();
		return std::move(m_val.get());
	}

	const std::exception_ptr& exception() const&
	const noexcept
	{
		if (*this) {
			throw bad_expected_type{"attempt to get exception "
				"pointer from valid expected object"};
		}
		return m_ptr;
	}

	std::exception_ptr exception() &&
	noexcept
	{
		if (*this) {
			throw bad_expected_type{"attempt to move exception "
				"pointer from valid expected object"};
		}

		auto tmp = std::move(m_ptr);
		/*
		** This step is *crucial.* If we didn't nullify `m_ptr`, then
		** the program would crash because of a double-free. This is
		** because an exception pointer uses shared ownership semantics.
		** The sequence of operations leading to this would be as
		** follows:
		**
		**   - Create `A` (ref count 1)
		**   - Destroy `A` (ref count 0, free)
		**   - Copy construct `B` from `A` (ref count 1)
		**   - Destroy `B` (ref count 0, free): CRASH!
		*/
		m_ptr = nullptr;
		return std::move(tmp);
	}

	/*
	** XXX: This is broken because the `swap` function that is actually
	** found through ADL may use something other than move construction.
	** FIXME when C++ gets `is_swappable` traits.
	*/
	template <
		bool B = std::is_move_constructible<storage>::value,
		typename std::enable_if<B, int>::type = 0
	>
	void swap(expected& rhs)
	noexcept(std::is_nothrow_move_constructible<storage>::value)
	{
		if (*this) {
			if (*rhs) {
				using std::swap;
				swap(m_val, rhs.m_val);
			}
			else {
				/*
				** We need to either move either `rhs.m_ptr` or
				** `this->m_val` object into a temporary. When
				** we mutate a member of the union of either
				** `this` or the `rhs`, we will invalidate the
				** other member of that union. We make the
				** assumption that choosing to load whichever of
				** the two is smaller (either `storage` or
				** `std::exception_ptr`) into a temporary will
				** be most efficient.
				*/
				if (sizeof(storage) < sizeof(std::exception_ptr)) {
					auto tmp = std::move(m_val);
					::new (&m_ptr) std::exception_ptr{rhs.m_ptr};
					::new (std::addressof(rhs.m_val)) storage(std::move(tmp));
				}
				else {
					auto tmp = std::move(rhs.m_ptr);
					::new (std::addressof(rhs.m_val)) storage(std::move(m_val));
					::new (&m_ptr) std::exception_ptr{std::move(tmp)};
				}

				/*
				** Note: we do not have to invalidate
				** `rhs.m_ptr` here, because its destructor will
				** never be called, as a result of `rhs`'s
				** change to a valid state.
				*/

				#ifdef CC_NO_DEBUG
					m_state &= ~expected_state::valid;
					rhs.m_state |= expected_state::valid;
				#endif
			}
		}
		else {
			if (*rhs) {
				if (sizeof(storage) < sizeof(std::exception_ptr)) {
					auto tmp = std::move(rhs.m_val);
					::new (&rhs.m_ptr) std::exception_ptr{m_ptr};
					::new (std::addressof(m_val)) storage(std::move(tmp));
				}
				else {
					auto tmp = std::move(m_ptr);
					::new (std::addressof(m_val)) storage(std::move(rhs.m_val));
					::new (&rhs.m_ptr) std::exception_ptr{std::move(tmp)};
				}

				#ifdef CC_NO_DEBUG
					m_state |= expected_state::valid;
					rhs.m_state &= ~expected_state::valid;
				#endif
			}
			else {
				std::swap(m_ptr, rhs.m_ptr);
			}
		}

		/*
		** When not in debug mode, we only have to worry about
		** exchanging states in two cases. Otherwise, we need to deal
		** with the `dismissed` flag, so we should always swap states.
		*/
		#ifndef CC_NO_DEBUG
			std::swap(m_state, rhs.m_state);
		#endif
	}

	template <class... Args>
	void emplace(Args&&... args)
	{
		this->~expected();
		::new (std::addressof(m_val)) storage{std::forward<Args>(args)...};
		m_state = expected_state::valid;
	}

	template <class E>
	E expect() const
	{
		try {
			raise();
		}
		catch (const E& e) {
			return e;
		}
		catch (...) {
			std::throw_with_nested(
				bad_expected_type{"expected object does not "
					"contain exception of specified type"}
			);
		}
	}
};

//template <>
//class expected<void>
//{
//	std::exception_ptr m_ptr;
//	bool valid_;
//	#ifndef CC_NO_DEBUG
//		mutable bool read_{false};
//	#endif
//public:
//	expected(bool) noexcept : valid_{true} {}
//
//	/*
//	** These constructors are used to create `expected` objects in invalid
//	** states.
//	*/
//
//	expected() noexcept : valid_{false}
//	{
//		::new (&m_ptr) std::exception_ptr{std::move(std::current_exception())};
//	}
//	
//	expected(std::exception_ptr p) noexcept : valid_{false}
//	{
//		::new (&m_ptr) std::exception_ptr{std::move(p)};
//	}
//
//	template <class E,
//		typename std::enable_if<
//			std::is_base_of<std::exception, E>::value, int
//		>::type = 0>
//	expected(const E& e) noexcept : valid_{false}
//	{
//		if (typeid(e) != typeid(E)) {
//			throw std::invalid_argument{"exception slicing detected in constructor"};
//		}
//		::new (&m_ptr) std::exception_ptr{std::move(std::make_exception_ptr(e))};
//	}
//
//	expected(const expected& rhs) noexcept : valid_{rhs.valid_}
//	{
//		if (!(m_state & expected_state::valid)) ::new(&m_ptr) std::exception_ptr{rhs.m_ptr};
//	}
//
//	expected(expected&& rhs) noexcept : valid_{rhs.valid_}
//	{
//		if (!(m_state & expected_state::valid)) ::new(&m_ptr) std::exception_ptr{std::move(rhs.m_ptr)};
//	}
//
//	~expected()
//	{
//		// We need the `using` statement here, because `::~` does not
//		// parse, so we would not be able to not write
//		// `m_ptr.::~exception_ptr()`.
//		if (!(m_state & expected_state::valid)) m_ptr.~exception_ptr();
//		#ifndef CC_NO_DEBUG
//			assert(read_ && "Potentially unchecked exception.");
//		#endif
//	}
//
//	bool valid() const noexcept
//	{
//		#ifndef CC_NO_DEBUG
//			m_state |= expected_state::dismissed;
//		#endif
//		return valid_;
//	}
//
//	operator bool() const noexcept
//	{ return valid(); }
//	
//	void get() const
//	{
//		#ifndef CC_NO_DEBUG
//			m_state |= expected_state::dismissed;
//		#endif
//		if (!*this) {
//			std::rethrow_exception(m_ptr);
//		}
//	}
//
//	void operator*() const { return get(); }
//
//	std::exception_ptr exception() const noexcept
//	{
//		if (*this) {
//			throw bad_expected_type{"
//		}
//		return m_ptr;
//	}
//
//	void swap(expected& rhs) noexcept
//	{
//		if (*this) {
//			// If both `*this` and `rhs` are valid, then we do not
//			// have to do anything.
//			if (!rhs.valid_) {
//				::new (&m_ptr) std::exception_ptr{rhs.m_ptr};
//				valid_ = false;
//				rhs.valid_ = true;
//			}
//		}
//		else {
//			if (rhs.valid_) {
//				::new (&rhs.m_ptr) std::exception_ptr{m_ptr};
//				rhs.valid_ = false;
//				valid_ = true;
//			}
//			else {
//				std::swap(m_ptr, rhs.m_ptr);
//			}
//		}
//	}
//
//	/*
//	** Checks whether this object has an exception of type `E`.
//	*/
//	template <class E>
//	bool has_exception() const
//	{
//		try {
//			if (!(m_state & expected_state::valid)) std::rethrow_exception(m_ptr);
//		}
//		catch (const E& e) {
//			return true;
//		}
//		catch (...) {}
//		return false;
//	}
//};

}

#endif
