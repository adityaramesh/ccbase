/*
** File Name:	dynamic.hpp
** Author:	Aditya Ramesh
** Date:	06/30/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZDBB75EFD_5555_4AF8_9C85_102127F45636
#define ZDBB75EFD_5555_4AF8_9C85_102127F45636

#include <functional>
#include <stdexcept>
#include <type_traits>
#include <ccbase/platform/features.hpp>
#include <ccbase/utility/expected.hpp>

#if PLATFORM_KERNEL == PLATFORM_KERNEL_LINUX || \
    PLATFORM_KERNEL == PLATFORM_KERNEL_XNU
	#include <dlfcn.h>
#else
	#error "Unsupported kernel."
#endif

namespace cc
{

enum class mode : int
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

#ifdef RTLD_DEPBIND
	depbind = RTLD_DEPBIND,
#endif

};

static constexpr mode lazy = mode::lazy;
static constexpr mode now = mode::now;
static constexpr mode global = mode::global;
static constexpr mode local = mode::local;

#ifdef RTLD_NODELETE
	static constexpr mode nodelete = mode::nodelete;
#endif

#ifdef RTLD_NOLOAD
	static constexpr mode noload = mode::noload;
#endif

#ifdef RTLD_DEPBIND
	static constexpr mode depbind = mode::depbind;
#endif

constexpr mode
operator|(const mode x, const mode y)
{
	using integer = typename std::underlying_type<mode>::type;
	return static_cast<mode>(
		static_cast<integer>(x) |
		static_cast<integer>(y)
	);
}

class image
{
private:
	void* handle;
public:
	image(const char* path, mode m)
	{
		using integer = typename std::underlying_type<mode>::type;
		handle = ::dlopen(path, static_cast<integer>(m));
		if (handle == nullptr) {
			throw std::runtime_error{::dlerror()};
		}
	}

	~image()
	{
		if (::dlclose(handle) != 0) {
			// Ideally, if an error occurs in closing the handle,
			// then we would log the error.
			::dlerror();
		}
	}

	operator void*() const
	{
		return handle;
	}
};

template <class Signature>
class function;

template <class ReturnType, class... Args>
class function<ReturnType(Args...)>
{
private:
	using signature = ReturnType(Args...);
	using pointer = ReturnType(*)(Args...);

	std::function<signature> f;
	void* address;
public:
	function(void* address) noexcept :
	f{reinterpret_cast<pointer>(address)}, address{address} {}

	ReturnType operator()(Args... args) const
	{
		return f(args...);
	}

	operator void*() const
	{
		return address;
	}
};

class symbol_info
{
private:
	Dl_info data;
public:
	symbol_info() noexcept {}

	const char* path() const
	{
		return data.dli_fname;
	}

	const void* base_address() const
	{
		return data.dli_fbase;
	}

	const char* name() const
	{
		return data.dli_sname;
	}

	const void* address() const
	{
		return data.dli_saddr;
	}

	operator Dl_info*()
	{
		return &data;
	}
};

template <class T>
cc::expected<symbol_info>
get_info(const T& t)
{
	symbol_info d;
	auto r = ::dladdr(static_cast<void*>(const_cast<T*>(&t)), d);
	if (r == 0) {
		throw std::runtime_error{::dlerror()};
	}
	return d;
}

template <class Signature>
cc::expected<symbol_info>
get_info(const function<Signature> f)
{
	symbol_info d;
	auto r = ::dladdr(f, d);
	if (r == 0) {
		throw std::runtime_error{::dlerror()};
	}
	return d;
}

template <class Signature>
cc::expected<function<Signature>>
get_function(const char* name, const image& i)
{
	if (cc::platform::os.get_kernel() == cc::kernel::linux) {
		::dlerror();
	}
	auto t = ::dlsym(i, name);
	switch (cc::platform::os.get_kernel()) {
	case cc::kernel::linux:
		if (::dlerror() != nullptr) {
			return std::runtime_error{"Symbol not found."};
		}
	case cc::kernel::xnu:
		if (t == nullptr) {
			return std::runtime_error{::dlerror()};
		}
	}
	return function<Signature>{t};
}

/*
** Note that this function returns an `expected<T&>`, so mutating the value type
** from the `expected` object also mutates the original object retrieved from
** the symbol address.
*/

template <class T>
cc::expected<T&>
get_data(const char* name, const image& i)
{
	if (cc::platform::os.get_kernel() == cc::kernel::linux) {
		::dlerror();
	}
	auto t = ::dlsym(i, name);
	switch (cc::platform::os.get_kernel()) {
	case cc::kernel::linux:
		if (::dlerror() != nullptr) {
			return std::runtime_error{"Symbol not found."};
		}
	case cc::kernel::xnu:
		if (t == nullptr) {
			return std::runtime_error{::dlerror()};
		}
	}
	return *static_cast<T*>(t);
}

}

#endif
