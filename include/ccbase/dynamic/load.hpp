/*
** File Name:	load.hpp
** Author:	Aditya Ramesh
** Date:	06/30/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZDBB75EFD_5555_4AF8_9C85_102127F45636
#define ZDBB75EFD_5555_4AF8_9C85_102127F45636

#include <functional>
#include <stdexcept>
#include <type_traits>
#include <boost/utility/string_ref.hpp>
#include <ccbase/error.hpp>
#include <ccbase/platform.hpp>
#include <ccbase/utility/enum_bitmask.hpp>

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX || \
    PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	#include <dlfcn.h>
#else
	#error "Unsupported kernel."
#endif

namespace cc {

enum class binding_mode : int
{
	lazy   = RTLD_LAZY,
	now    = RTLD_NOW,
	global = RTLD_GLOBAL,
	local  = RTLD_LOCAL,

#ifdef RTLD_NODELETE
	nodelete = RTLD_NODELETE,
#endif

#ifdef RTLD_NOLOAD
	noload = RTLD_NOLOAD,
#endif

#ifdef RTLD_DEEPBIND
	depbind = RTLD_DEEPBIND,
#endif
};

DEFINE_ENUM_BITWISE_OPERATORS(binding_mode)

class image
{
	bool m_closed{false};
	void* m_handle;
public:
	explicit image(const boost::string_ref path, binding_mode m)
	{
		using integer = typename std::underlying_type<binding_mode>::type;
		m_handle = ::dlopen(path.begin(), static_cast<integer>(m));
		if (m_handle == nullptr) {
			m_closed = true;
			throw std::runtime_error{::dlerror()};
		}
	}

	~image() { close(); }

	void* handle() const noexcept
	{ return m_handle; }

	void close()
	{
		if (m_closed) {
			return;
		}
		if (::dlclose(m_handle) != 0) {
			throw std::runtime_error{::dlerror()};
		}
		m_closed = true;
	}
};

template <class Signature>
class function;

template <class ReturnType, class... Args>
class function<ReturnType(Args...)>
{
	using signature = ReturnType(Args...);
	using pointer = ReturnType(*)(Args...);

	std::function<signature> m_func;
	void* m_addr;
public:
	explicit function(void* addr) noexcept :
	m_func{reinterpret_cast<pointer>(addr)}, m_addr{addr} {}

	template <class... Args_>
	ReturnType operator()(Args_&&... args)
	const noexcept(noexcept(m_func(std::forward<Args_>(args)...)))
	{ return m_func(std::forward<Args_>(args)...); }

	const void* address() const noexcept
	{ return m_addr; }
};

class symbol_info
{
	::Dl_info m_data;
public:
	explicit symbol_info() noexcept {}

	const boost::string_ref path()
	const noexcept { return {m_data.dli_fname}; }

	const boost::string_ref name()
	const noexcept { return {m_data.dli_sname}; }

	const void* base_address()
	const noexcept { return m_data.dli_fbase; }

	const void* address()
	const noexcept { return m_data.dli_saddr; }

	Dl_info& handle()
	noexcept { return m_data; }

	const Dl_info& handle()
	const noexcept { return m_data; }
};

template <class T>
cc::expected<symbol_info>
query(const T& t) noexcept
{
	auto si = symbol_info{};
	if (::dladdr((void*)&t, &si.handle()) == 0) {
		throw std::runtime_error{::dlerror()};
	}
	return si;
}

template <class Signature>
cc::expected<symbol_info>
query(const function<Signature>& f) noexcept
{
	auto si = symbol_info{};
	if (::dladdr(f.address(), &si.handle()) == 0) {
		throw std::runtime_error{::dlerror()};
	}
	return si;
}


namespace detail {

/*
** This is the specialization for loading non-function objects from the image.
*/
template <class T>
struct load_helper
{
	static cc::expected<T&>
	apply(const boost::string_ref name, const image& img)
	noexcept
	{
		// The Linux manual states that the error state should be cleared before
		// checking the error state after the next `dl*` function call.
		#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
			::dlerror();
		#endif

		auto t = ::dlsym(img.handle(), name.begin());

		#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
			if (::dlerror() != nullptr) {
				return std::runtime_error{"Symbol not found."};
			}
		#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
			if (t == nullptr) {
				return std::runtime_error{::dlerror()};
			}
		#endif

		return *static_cast<T*>(t);
	}
};

/*
** This is the specialization for loading functions from the image.
*/
template <class R, class... Args>
struct load_helper<R(Args...)>
{
	using signature = R(Args...);

	/*
	** Note that this function returns an `expected<T&>`, so mutating the value type
	** from the `expected` object also mutates the original object retrieved from
	** the symbol address.
	*/
	static cc::expected<function<signature>>
	apply(const boost::string_ref name, const image& img)
	noexcept
	{
		// The Linux manual states that the error state should be cleared before
		// checking the error state after the next dl* function call.
		#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
			::dlerror();
		#endif

		auto t = ::dlsym(img.handle(), name.begin());

		#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX
			if (::dlerror() != nullptr) {
				return std::runtime_error{"Symbol not found."};
			}
		#elif PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
			if (t == nullptr) {
				return std::runtime_error{::dlerror()};
			}
		#endif

		return function<signature>{t};
	}
};

}

template <class T>
auto load(const boost::string_ref name, const image& img)
noexcept -> decltype(detail::load_helper<T>::apply(name, img))
{ return detail::load_helper<T>::apply(name, img); }

}

#endif
