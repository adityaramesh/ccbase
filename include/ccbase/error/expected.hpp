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
	#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		// Used to keep track of whether the state of the expected
		// object was checked prior to destruction.
		dismissed = 0x2,
	#endif
};

DEFINE_ENUM_BITWISE_OPERATORS(expected_state)

template <class T>
struct expected_traits
{
	using storage              = T;
	using value_type           = T;
	using non_const_value_type = typename std::remove_const<T>::type;
	using pointer              = T*;
	using reference            = T&;
	using non_const_reference  = non_const_value_type&;
	using const_reference      = const T&;
};

template <class T>
struct expected_traits<T&>
{
	using storage             = std::reference_wrapper<T>;
	using value_type          = T;
	using pointer             = T*;
	using reference           = T&;
	using non_const_reference = T&;
	using const_reference     = const T&;
};

template <class T>
struct expected_traits<const T&>
{
	using storage             = std::reference_wrapper<const T>;
	using value_type          = T;
	using pointer             = const T*;
	using reference           = const T&;
	using non_const_reference = T&;
	using const_reference     = const T&;
};

template <class T>
class expected final
{
	using storage             = typename expected_traits<T>::storage;
	using value_type          = typename expected_traits<T>::value_type;
	using pointer             = typename expected_traits<T>::pointer;
	using reference           = typename expected_traits<T>::reference;
	using non_const_reference = typename expected_traits<T>::non_const_reference;
	using const_reference     = typename expected_traits<T>::const_reference;

	/*
	** Allowing either of the below would result in ambiguous overloads.
	*/
	static_assert(!std::is_same<
		typename std::decay<value_type>::type, std::exception_ptr
	>::value, "");

	static_assert(!std::is_base_of<
		std::exception, typename std::decay<value_type>::type
	>::value, "");

	// Disallow function types and `void`.
	static_assert(std::is_object<T>::value || std::is_lvalue_reference<T>::value, "");
	// So that we can copy and move the `expected` object.
	static_assert(std::is_copy_constructible<storage>::value, "");
	// For exception safety.
	static_assert(std::is_nothrow_destructible<storage>::value, "");

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
	: m_val(), m_state{expected_state::valid} {}

	/*
	** NOTE: We cannot use curly brackets to initialize `m_val`, because
	** initialization will fail for POD types. The curly bracket for POD
	** types does something different from the uniform initialization for
	** non-POD types. If we were to use the curly bracket when `T` is POD
	** type, the compiler would try to assign `rhs` to the first field of
	** `T`, rather than performing the copy-construction.
	*/
	template <
		bool B = std::is_copy_constructible<storage>::value &&
		        !std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0
	>
	expected(const_reference rhs)
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
	expected(value_type&& rhs)
	noexcept(std::is_nothrow_move_constructible<storage>::value)
	: m_val(rhs), m_state{expected_state::valid} {}

	template <
		bool B = std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0,
		class = void
	>
	expected(reference rhs)
	noexcept(std::is_nothrow_copy_constructible<storage>::value)
	: m_val(rhs), m_state{expected_state::valid} {}

	/*
	** There is no need to use `enable_if` here, because this is a template
	** function. We will let the compiler error out normally.
	*/
	template <
		bool B = !std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0,
		class... Args
	>
	expected(const in_place_t&, Args&&... args)
	noexcept(std::is_nothrow_constructible<storage, Args...>::value) :
	m_val{std::forward<Args>(args)...}, m_state{expected_state::valid} {}

	expected(const expected& rhs)
	noexcept(std::is_nothrow_copy_constructible<storage>::value)
	: m_state{rhs.m_state}
	{
		if (rhs) {
			::new((void*)std::addressof(m_val)) storage(rhs.m_val);
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
	expected(expected&& rhs)
	noexcept(std::is_nothrow_move_constructible<storage>::value)
	: m_state{rhs.m_state}
	{
		if (rhs) {
			::new((void*)std::addressof(m_val)) storage(std::move(rhs.m_val));
		}
		else {
			::new(&m_ptr) std::exception_ptr{std::move(rhs.m_ptr)};
		}
	}

	expected(const std::exception_ptr& ptr)
	noexcept : m_state{expected_state::invalid}
	{ ::new(&m_ptr) std::exception_ptr{ptr}; }

	expected(std::exception_ptr&& ptr)
	noexcept : m_state{expected_state::invalid}
	{ ::new(&m_ptr) std::exception_ptr{std::move(ptr)}; }

	template <class E,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, int
		>::type = 0>
	expected(const E& e)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
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
		::new(&m_ptr) std::exception_ptr{std::make_exception_ptr(e)};
	}

	/*
	** XXX: Ideally, we would disable assignment in the case that `T` is
	** `const`. But I don't want to go through the template specialization
	** bullshit now, given how complex things already are.
	*/

	expected& operator=(const expected& rhs)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept(noexcept(assign_storage(rhs.m_val)))
	#endif
	{
		enforce_dismissed();

		if (*this) {
			if (rhs) {
				assign_storage(rhs.m_val);
			}
			else {
				m_val.~storage();
				::new(&m_ptr) std::exception_ptr{rhs.m_ptr};

				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state &= ~expected_state::valid;
				#endif
			}
		}
		else {
			if (rhs) {
				m_ptr.~exception_ptr();
				// We can't use `assign_storage` in this case,
				// because the storage is uninitialized.
				::new((void*)std::addressof(m_val))
					storage{rhs.m_val};

				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state |= expected_state::valid;
				#endif
			}
			else {
				m_ptr = rhs.m_ptr;
			}
		}

		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = rhs.m_state;
		#endif
		return *this;
	}

	/*
	** It's ok if `T` is a reference in this case, because we are
	** potentially copying a reference from `rhs`, but never a reference to
	** a temporary object.
	*/
	expected& operator=(expected&& rhs)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept(noexcept(assign_storage(std::move(rhs.m_val))))
	#endif
	{
		enforce_dismissed();

		if (*this) {
			if (rhs) {
				assign_storage(std::move(rhs.m_val));
				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state &= ~expected_state::valid;
				#endif
			}
			else {
				m_val.~storage();
				::new(&m_ptr)
					std::exception_ptr{std::move(rhs.m_ptr)};

				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state &= ~expected_state::valid;
				#endif
			}
		}
		else {
			if (rhs) {
				m_ptr.~exception_ptr();
				// We can't use `assign_storage` in this case,
				// because the storage is uninitialized.
				::new((void*)std::addressof(m_val))
					storage{std::move(rhs.m_val)};

				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state |= expected_state::valid;
				#endif
			}
			else {
				m_ptr = std::move(rhs.m_ptr);
			}
		}

		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = rhs.m_state;
		#endif
		return *this;
	}

	template <bool B = !std::is_reference<T>::value>
	auto operator=(const storage& rhs)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept(
			std::is_nothrow_copy_constructible<storage>::value &&
			std::is_nothrow_copy_assignable<storage>::value
		)
	#endif
	-> typename std::enable_if<B, expected&>::type
	{
		enforce_dismissed();

		if (*this) {
			assign_storage(std::move(rhs));
		}
		else {
			m_ptr.~exception_ptr();
			// We can't use `assign_storage` in this case,
			// because the storage is uninitialized.
			::new((void*)std::addressof(m_val))
				storage{rhs.m_val};
		}

		#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = expected_state::valid;
		#else
			m_state = expected_state::valid | expected_state::dismissed;
		#endif
		return *this;
	}

	template <bool B = !std::is_reference<T>::value>
	auto operator=(storage&& rhs)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept(
			std::is_nothrow_move_constructible<storage>::value &&
			std::is_nothrow_move_assignable<storage>::value
		)
	#endif
	-> typename std::enable_if<B, expected&>::type
	{
		enforce_dismissed();

		if (*this) {
			assign_storage(std::move(rhs));
		}
		else {
			m_ptr.~exception_ptr();
			// We can't use `assign_storage` in this case,
			// because the storage is uninitialized.
			::new((void*)std::addressof(m_val))
				storage{std::move(rhs)};
		}

		#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = expected_state::valid;
		#else
			m_state = expected_state::valid | expected_state::dismissed;
		#endif
		return *this;
	}

	template <bool B = std::is_reference<T>::value, class = void>
	auto operator=(reference rhs)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	-> typename std::enable_if<B, expected&>::type
	{
		enforce_dismissed();

		if (*this) {
			m_val = storage{rhs};
		}
		else {
			m_ptr.~exception_ptr();
			::new((void*)std::addressof(m_val))
				storage{rhs};
		}

		#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = expected_state::valid;
		#else
			m_state = expected_state::valid | expected_state::dismissed;
		#endif
		return *this;
	}

	expected& operator=(const std::exception_ptr& ptr) 
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		enforce_dismissed();
		if (!*this) m_ptr.~exception_ptr();
		::new(&m_ptr) std::exception_ptr{ptr};

		#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = expected_state::invalid;
		#else
			m_state = expected_state::invalid | expected_state::dismissed;
		#endif
		return *this;
	}

	expected& operator=(std::exception_ptr&& ptr) 
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		enforce_dismissed();
		if (!*this) m_ptr.~exception_ptr();
		::new(&m_ptr) std::exception_ptr{std::move(ptr)};

		#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = expected_state::invalid;
		#else
			m_state = expected_state::invalid | expected_state::dismissed;
		#endif
		return *this;
	}

	~expected()
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		/*
		** Make sure we release any resources before potentially
		** throwing because this object was not dismissed.
		*/
		if (!!(m_state & expected_state::valid)) {
			m_val.~storage();
		}
		else {
			m_ptr.~exception_ptr();
		}
		enforce_dismissed();
	}
private:
	template <bool B = std::is_copy_assignable<storage>::value>
	auto assign_storage(const storage& rhs)
	noexcept(std::is_nothrow_copy_assignable<storage>::value)
	-> typename std::enable_if<B>::type
	{
		m_val = rhs;
	}

	template <bool B = !std::is_copy_assignable<storage>::value, class = void>
	auto assign_storage(const storage& rhs)
	noexcept(std::is_nothrow_copy_constructible<storage>::value)
	-> typename std::enable_if<B>::type
	{
		m_val.~storage();
		::new((void*)std::addressof(m_val)) storage{rhs};
	}

	template <bool B = std::is_move_assignable<storage>::value>
	auto assign_storage(storage&& rhs)
	noexcept(std::is_nothrow_move_assignable<storage>::value)
	-> typename std::enable_if<B>::type
	{
		m_val = std::move(rhs);
	}

	template <bool B = !std::is_move_assignable<storage>::value, class = void>
	auto assign_storage(storage&& rhs)
	noexcept(std::is_nothrow_move_constructible<storage>::value)
	-> typename std::enable_if<B>::type
	{
		m_val.~storage();
		::new((void*)std::addressof(m_val)) storage{std::move(rhs)};
	}

	void enforce_dismissed() const
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			if (!(m_state & expected_state::dismissed)) {
				throw std::logic_error{"unchecked expected object"};
			}
		#endif
	}

	[[noreturn]] void rethrow_exception() const noexcept(false)
	{
		if (m_ptr == nullptr) {
			throw bad_expected_type{"expected object is "
				"invalid, but the exception pointer has "
				"been moved"};
		}
		std::rethrow_exception(m_ptr);
	}
public:
	[[noreturn]] void raise() const noexcept(false)
	{
		if (*this) {
			throw bad_expected_type{"attempt to throw "
				"exception from valid expected object"};
		}
		rethrow_exception();
	}

	expected& dismiss() noexcept
	{
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state |= expected_state::dismissed;
		#endif
		return *this;
	}

	const expected& dismiss() const noexcept
	{
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state |= expected_state::dismissed;
		#endif
		return *this;
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

	const value_type& value() const&
	{
		if (!*this) rethrow_exception();
		return m_val;
	}

	reference operator*() & { return value(); }
	const value_type& operator*() const& { return value(); }

	/*
	** Remarks:
	**   - We don't need to check for constness here, because the return
	**   value has the correct constness.
	**   - Since this function returns a pointer to the value, we disallow
	**   invocation on rvalue references.
	*/
	template <bool B = !std::is_reference<T>::value>
	auto operator->() &
	-> typename std::enable_if<B, pointer>::type
	{
		if (!*this) rethrow_exception();
		return std::addressof(m_val);
	}

	template <bool B = !std::is_reference<T>::value>
	auto operator->() const&
	-> typename std::enable_if<B, const value_type*>::type
	{
		if (!*this) rethrow_exception();
		return std::addressof(m_val);
	}

	template <bool B = std::is_reference<T>::value, class = void>
	auto operator->() &
	-> typename std::enable_if<B, pointer>::type
	{
		if (!*this) rethrow_exception();
		return std::addressof(m_val.get());
	}

	template <bool B = std::is_reference<T>::value, class = void>
	auto operator->() const&
	-> typename std::enable_if<B, const value_type*>::type
	{
		if (!*this) rethrow_exception();
		return std::addressof(m_val.get());
	}

	template <
		bool B = !std::is_reference<T>::value &&
		         !std::is_const<T>::value
	>
	auto value() &&
	-> typename std::enable_if<B, T&&>::type
	{
		if (!*this) rethrow_exception();
		return std::move(m_val);
	}

	template <
		bool B = std::is_reference<T>::value &&
			!std::is_const<
				typename std::remove_reference<T>::type
			>::value,
		class = void
	>
	auto value() &&
	-> typename std::enable_if<B, value_type&&>::type
	{
		if (!*this) rethrow_exception();
		return std::move(m_val.get());
	}

	reference operator*() && { return value(); }

	const std::exception_ptr& exception() const&
	{
		if (*this) {
			throw bad_expected_type{"attempt to get exception "
				"pointer from valid expected object"};
		}
		return m_ptr;
	}

	std::exception_ptr exception() &&
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
	void swap(expected& rhs)
	noexcept(std::is_nothrow_move_constructible<storage>::value)
	{
		if (*this) {
			if (rhs) {
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
					rhs.m_ptr.~exception_ptr();

					auto tmp = std::move(m_val);
					::new(&m_ptr) std::exception_ptr{rhs.m_ptr};
					::new((void*)std::addressof(rhs.m_val))
						storage(std::move(tmp));
				}
				else {
					auto tmp = std::move(rhs.m_ptr);
					/*
					** Note: this must occur **after** the
					** move operation.
					*/
					rhs.m_ptr.~exception_ptr();

					::new((void*)std::addressof(rhs.m_val))
						storage(std::move(m_val));
					::new(&m_ptr) std::exception_ptr{std::move(tmp)};
				}

				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state &= ~expected_state::valid;
					rhs.m_state |= expected_state::valid;
				#endif
			}
		}
		else {
			if (rhs) {
				if (sizeof(storage) < sizeof(std::exception_ptr)) {
					m_ptr.~exception_ptr();

					auto tmp = std::move(rhs.m_val);
					::new(&rhs.m_ptr) std::exception_ptr{m_ptr};
					::new((void*)std::addressof(m_val))
						storage(std::move(tmp));
				}
				else {
					auto tmp = std::move(m_ptr);
					m_ptr.~exception_ptr();

					::new((void*)std::addressof(m_val))
						storage(std::move(rhs.m_val));
					::new(&rhs.m_ptr) std::exception_ptr{std::move(tmp)};
				}

				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
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
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			std::swap(m_state, rhs.m_state);
		#endif
	}

	template <
		class... Args,
		bool B = !std::is_reference<T>::value,
		typename std::enable_if<B, int>::type = 0
	>
	expected& emplace(Args&&... args)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept(std::is_nothrow_constructible<T, Args...>::value)
	#endif
	{
		this->~expected();
		::new((void*)std::addressof(m_val))
			storage{std::forward<Args>(args)...};

		#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = expected_state::valid;
		#else
			m_state = expected_state::valid | expected_state::dismissed;
		#endif
		return *this;
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

template <>
class expected<void> final
{
	std::exception_ptr m_ptr;
	mutable expected_state m_state;
public:
	expected() noexcept :
	m_state{expected_state::valid} {}

	expected(const no_error_t&) noexcept :
	expected{} {}

	expected(const expected& rhs) noexcept :
	m_state{rhs.m_state}
	{
		if (!rhs) {
			::new(&m_ptr) std::exception_ptr{rhs.m_ptr};
		}
	}

	expected(expected&& rhs) noexcept :
	m_state{rhs.m_state}
	{
		if (!rhs) {
			::new(&m_ptr) std::exception_ptr{std::move(rhs.m_ptr)};
		}
	}

	expected(const std::exception_ptr& ptr)
	noexcept : m_state{expected_state::invalid}
	{ ::new(&m_ptr) std::exception_ptr{ptr}; }

	expected(std::exception_ptr&& ptr)
	noexcept : m_state{expected_state::invalid}
	{ ::new(&m_ptr) std::exception_ptr{std::move(ptr)}; }

	template <class E,
		typename std::enable_if<
			std::is_base_of<std::exception, E>::value, int
		>::type = 0>
	expected(const E& e)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	: m_state{expected_state::invalid}
	{
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			if (typeid(e) != typeid(E)) {
				throw std::logic_error{"exception slicing "
					"detected during construction"};
			}
		#endif
		::new(&m_ptr) std::exception_ptr{std::make_exception_ptr(e)};
	}

	expected& operator=(const expected& rhs)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		enforce_dismissed();

		if (*this) {
			if (!rhs) {
				::new(&m_ptr) std::exception_ptr{rhs.m_ptr};
				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state &= ~expected_state::valid;
				#endif
			}
		}
		else {
			if (rhs) {
				m_ptr.~exception_ptr();
				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state |= expected_state::valid;
				#endif
			}
			else {
				m_ptr = rhs.m_ptr;
			}
		}

		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = rhs.m_state;
		#endif
		return *this;
	}

	expected& operator=(expected&& rhs)
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		enforce_dismissed();

		if (*this) {
			if (!rhs) {
				::new(&m_ptr) std::exception_ptr{std::move(rhs.m_ptr)};
				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state &= ~expected_state::valid;
				#endif
			}
		}
		else {
			if (rhs) {
				m_ptr.~exception_ptr();
				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
					m_state |= expected_state::valid;
				#endif
			}
			else {
				m_ptr = rhs.m_ptr;
			}
		}

		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = rhs.m_state;
		#endif
		return *this;
	}

	expected& operator=(const std::exception_ptr& ptr) 
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		enforce_dismissed();
		if (!*this) m_ptr.~exception_ptr();
		::new(&m_ptr) std::exception_ptr{ptr};

		#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = expected_state::invalid;
		#else
			m_state = expected_state::invalid | expected_state::dismissed;
		#endif
		return *this;
	}

	expected& operator=(std::exception_ptr&& ptr) 
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		enforce_dismissed();
		if (!*this) m_ptr.~exception_ptr();
		::new(&m_ptr) std::exception_ptr{std::move(ptr)};

		#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state = expected_state::invalid;
		#else
			m_state = expected_state::invalid | expected_state::dismissed;
		#endif
		return *this;
	}

	~expected()
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		/*
		** Make sure we release any resources before potentially
		** throwing because this object was not dismissed.
		*/
		if (!!(m_state & expected_state::valid)) {
			m_ptr.~exception_ptr();
		}
		enforce_dismissed();
	}
private:
	void enforce_dismissed() const
	#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
		noexcept
	#endif
	{
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			if (!(m_state & expected_state::dismissed)) {
				throw std::logic_error{"unchecked expected object"};
			}
		#endif
	}

	[[noreturn]] void rethrow_exception() const noexcept(false)
	{
		if (m_ptr == nullptr) {
			throw bad_expected_type{"expected object is "
				"invalid, but the exception pointer has "
				"been moved"};
		}
		std::rethrow_exception(m_ptr);
	}
public:
	[[noreturn]] void raise() const noexcept(false)
	{
		if (*this) {
			throw bad_expected_type{"attempt to throw "
				"exception from valid expected object"};
		}
		rethrow_exception();
	}

	void operator*() const
	{
		dismiss();
		if (!*this) raise();
	}

	expected& dismiss() noexcept
	{
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state |= expected_state::dismissed;
		#endif
		return *this;
	}

	const expected& dismiss() const noexcept
	{
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			m_state |= expected_state::dismissed;
		#endif
		return *this;
	}

	operator bool() const noexcept
	{
		dismiss();
		return !!(m_state & expected_state::valid);
	}

	const std::exception_ptr& exception() const&
	{
		if (*this) {
			throw bad_expected_type{"attempt to get exception "
				"pointer from valid expected object"};
		}
		return m_ptr;
	}

	std::exception_ptr exception() &&
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

	void swap(expected& rhs) noexcept
	{
		if (*this && !rhs) {
			::new(&m_ptr) std::exception_ptr{rhs.m_ptr};
			rhs.m_ptr.~exception_ptr();

			#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
				m_state &= ~expected_state::valid;
				rhs.m_state |= expected_state::valid;
			#endif
		}
		else {
			if (rhs) {
				::new(&rhs.m_ptr) std::exception_ptr{m_ptr};
				m_ptr.~exception_ptr();

				#ifdef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
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
		#ifndef CC_EXPECTED_DONT_ENFORCE_DISMISSAL
			std::swap(m_state, rhs.m_state);
		#endif
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

template <class T>
void swap(expected<T>& lhs, expected<T>& rhs)
noexcept(noexcept(lhs.swap(rhs)))
{ lhs.swap(rhs); }

template <class NullaryFunction>
auto attempt(const NullaryFunction& f) ->
typename std::enable_if<
	!std::is_same<decltype(f()), void>::value,
	expected<decltype(f())>
>::type
{
	try {
		return f();
	}
	catch (const std::exception& e) {
		return e;
	}
}

template <class NullaryFunction>
auto attempt(const NullaryFunction& f) ->
typename std::enable_if<
	std::is_same<decltype(f()), void>::value,
	expected<void>
>::type
{
	try {
		f();
	}
	catch (const std::exception& e) {
		return e;
	}
	return cc::no_error;
}

}

namespace std {

template <class T>
struct hash<::cc::expected<T>>
{
	using result_type = typename hash<T>::result_type;
	using argument_type = ::cc::expected<T>;

	result_type operator()(const argument_type& t)
	const noexcept
	{
		return t ? hash<T>{}(*t) : result_type{};
	}
};

template <class T>
struct hash<::cc::expected<T&>>
{
	using result_type = typename hash<T>::result_type;
	using argument_type = ::cc::expected<T>;

	result_type operator()(const argument_type& t)
	const noexcept
	{
		return t ? hash<T>{}(*t) : result_type{};
	}
};

}

#endif
