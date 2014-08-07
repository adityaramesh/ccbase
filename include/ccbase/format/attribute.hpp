/*
** File Name: attribute.hpp
** Author:    Aditya Ramesh
** Date:      08/03/2014
** Contact:   _@adityaramesh.com
*/

#ifndef ZF1D988C4_9465_4056_A062_2E7B7FB28FE7
#define ZF1D988C4_9465_4056_A062_2E7B7FB28FE7

#include <cassert>
#include <cstdint>
#include <limits>

#include <array>
#include <bitset>
#include <unordered_map>
#include <string>

#include <locale>
#include <ostream>
#include <sstream>
#include <iomanip>

#include <boost/lexical_cast.hpp>
#include <boost/utility/string_ref.hpp>

namespace cc {

enum class attribute_id
{
	// General attributes:
	align,
	locale,
	quote,
	// Number attributes:
	sign,
	money,
	// Integer attributes:
	binary,
	octal,
	decimal,
	hex,
	bool_,
	char_,
	number,
	base,
	// Floating-point attributes:
	precision,
	fixed,
	scientific,
	percent,
	// String attributes:
	upper,
	lower,
};

enum class attribute_function : uint8_t
{
	adds_manipulators = 0,
	number_to_number,
	number_to_string,
	type_to_string,
	string_to_string,
};

static constexpr auto num_attribute_functions = 5;

class attribute_description
{
public:
	static constexpr auto max_priority = 1;
	static constexpr auto min_priority = 5;
private:
	attribute_id m_id{};
	attribute_function m_func{};
	uint8_t m_priority{};
	uint8_t m_min_args{};
	uint8_t m_max_args{};
public:
	attribute_description() noexcept {}

	attribute_description(
		attribute_id id,
		attribute_function func,
		uint8_t priority,
		uint8_t min_args,
		uint8_t max_args
	) noexcept : m_id{id}, m_func{func}, m_priority{priority},
	m_min_args{min_args}, m_max_args{max_args} {}

	attribute_id id()
	const noexcept { return m_id; }

	attribute_function function()
	const noexcept { return m_func; }

	uint8_t priority() const noexcept
	{ return m_priority; }

	uint8_t min_args() const noexcept
	{ return m_min_args; }

	uint8_t max_args() const noexcept
	{ return m_max_args; }

	static attribute_description
	from_name(const boost::string_ref name)
	{
		static constexpr auto adds_manipulators = attribute_function::adds_manipulators;
		static constexpr auto number_to_number  = attribute_function::number_to_number;
		static constexpr auto number_to_string  = attribute_function::number_to_string;
		static constexpr auto type_to_string    = attribute_function::type_to_string;
		static constexpr auto string_to_string  = attribute_function::string_to_string;

		static const auto attr_map =
		std::unordered_map<std::string, attribute_description>
		{
			{"loc",   {attribute_id::locale,     adds_manipulators, 1, 1, 1}},
			{"base",  {attribute_id::base,       adds_manipulators, 1, 0, 1}},
			{"oct",   {attribute_id::octal,      adds_manipulators, 1, 0, 0}},
			{"dec",   {attribute_id::decimal,    adds_manipulators, 1, 0, 0}},
			{"hex",   {attribute_id::hex,        adds_manipulators, 1, 0, 0}},
			{"prec",  {attribute_id::precision,  adds_manipulators, 1, 1, 1}},
			{"fixed", {attribute_id::fixed,      adds_manipulators, 1, 0, 0}},
			{"sci",   {attribute_id::scientific, adds_manipulators, 1, 0, 0}},

			{"char",  {attribute_id::char_,  number_to_number, 1, 0, 0}},
			{"num",   {attribute_id::number, number_to_number, 1, 0, 0}},

			{"bool",  {attribute_id::bool_,   number_to_string, 2, 0, 0}},
			{"money", {attribute_id::money,   number_to_string, 2, 0, 1}},
			{"sign",  {attribute_id::sign,    number_to_string, 2, 1, 1}},
			{"bin",   {attribute_id::binary,  number_to_string, 2, 0, 0}},
			{"%",     {attribute_id::percent, number_to_string, 2, 0, 0}},

			{"upper", {attribute_id::upper, string_to_string, 3, 0, 0}},
			{"lower", {attribute_id::lower, string_to_string, 3, 0, 0}},

			{"quote", {attribute_id::quote, type_to_string,   4, 0, 0}},
			{"align", {attribute_id::align, string_to_string, 5, 2, 3}}
		};

		auto it = attr_map.find(static_cast<std::string>(name));
		if (it == attr_map.end()) {
			std::ostringstream msg{};
			msg << "Unknown attribute name \"" << name << "\".";
			throw std::runtime_error{msg.str()};
		}
		else {
			return it->second;
		}
	}
};

enum class sign_option : uint8_t
{
	always,
	space,
};

template <class Char, class Traits>
Char parse_argument(
	const attribute_description& t,
	uint8_t num,
	const boost::basic_string_ref<Char, Traits> str
)
{
	static constexpr auto max_size = std::numeric_limits<Char>::max();

	if (t.id() == attribute_id::align) {
		if (num == 0) {
			if (str.length() > 1) {
				throw std::runtime_error{"Argument too long."};
			}
			if (str[0] == 'L' || str[0] == 'R' || str[0] == 'C') {
				return str[0];
			}
			else {
				throw std::runtime_error{"Invalid argument."};
			}
		}
		else if (num == 1) {
			try {
				auto n = boost::lexical_cast<uint32_t>(str);
				if (n > max_size) {
					throw std::runtime_error{"Argument too large."};
				}
				return n;
			}
			catch (const boost::bad_lexical_cast& e) {
				throw std::runtime_error{"Invalid argument."};
			}
		}
		else if (num == 2) {
			/*
			** TODO: this is broken for escape sequences.
			*/
			if (str.length() != 3) {
				throw std::runtime_error{"Invalid argument."};
			}
			return str[1];
		}
	}
	else if (t.id() == attribute_id::sign) {
		if (num == 0) {
			if (str == "always") {
				return static_cast<Char>(sign_option::always);
			}
			else if (str == "space") {
				return static_cast<Char>(sign_option::space);
			}
			else {
				throw std::runtime_error{"Invalid argument."};
			}
		}
	}
	else if (t.id() == attribute_id::precision) {
		if (num == 0) {
			try {
				auto n = boost::lexical_cast<uint32_t>(str);
				if (n > max_size) {
					throw std::runtime_error{"Argument too large."};
				}
				return n;
			}
			catch (const boost::bad_lexical_cast& e) {
				throw std::runtime_error{"Invalid argument."};
			}
		}
	}
	else if (t.id() == attribute_id::base) {
		if (num == 0) {
			if (str == "upper") {
				return 1;
			}
			else {
				throw std::runtime_error{"Invalid argument."};
			}
		}
	}
	else if (t.id() == attribute_id::money) {
		if (num == 0) {
			if (str == "intl") {
				return 1;
			}
			else {
				throw std::runtime_error{"Invalid argument."};
			}
		}
	}
	else {
		throw std::runtime_error{"Attribute does not take any arguments."};
	}
	throw std::runtime_error{"Too many arguments to attribute."};
}

template <class Char, class Traits>
class attribute
{
public:
	using string_ref = boost::basic_string_ref<Char, Traits>;
	static constexpr auto max_arg_count = 3;
private:
	attribute_description m_type;
	uint8_t m_arg_count{};
	union {
		std::array<Char, max_arg_count> m_args;
		string_ref m_locale_name;
	};
public:
	explicit attribute() noexcept {}

	explicit attribute(attribute_description t) noexcept
	: m_type{t} {}

	explicit attribute(const boost::string_ref name)
	: m_type{attribute_description::from_name(name)} {}

	attribute(const attribute& rhs) noexcept
	: m_type{rhs.m_type}, m_arg_count{rhs.m_arg_count}
	{
		if (m_type.id() == attribute_id::locale) {
			m_locale_name = rhs.m_locale_name;
		}
		else {
			std::copy(rhs.m_args.data(), rhs.m_args.data() +
				m_arg_count, m_args.data());
		}
	}

	attribute(attribute&& rhs) noexcept
	: m_type{std::move(rhs.m_type)},
	m_arg_count{std::move(rhs.m_arg_count)}
	{
		if (m_type.id() == attribute_id::locale) {
			m_locale_name = std::move(rhs.m_locale_name);
		}
		else {
			std::copy(rhs.m_args.data(), rhs.m_args.data() +
				m_arg_count, m_args.data());
		}
	}

	~attribute() noexcept
	{
		if (m_type.id() == attribute_id::locale) {
			m_locale_name.~string_ref();
		}
	}

	attribute& operator=(const attribute& rhs)
	noexcept
	{
		m_type = rhs.m_type;
		m_arg_count = rhs.m_arg_count;
		if (m_type.id() == attribute_id::locale) {
			m_locale_name = rhs.m_locale_name;
		}
		else {
			std::copy(rhs.m_args.data(), rhs.m_args.data() +
				m_arg_count, m_args.data());
		}
		return *this;
	}

	attribute& operator=(attribute&& rhs)
	noexcept
	{
		m_type = std::move(rhs.m_type);
		m_arg_count = std::move(rhs.m_arg_count);
		if (m_type.id() == attribute_id::locale) {
			m_locale_name = std::move(rhs.m_locale_name);
		}
		else {
			std::copy(rhs.m_args.data(), rhs.m_args.data() +
				m_arg_count, m_args.data());
		}
		return *this;
	}

	attribute_description description()
	const noexcept { return m_type; }

	uint8_t arguments()
	const noexcept { return m_arg_count; }

	attribute& type(attribute_description t)
	noexcept
	{
		m_type = t;
		return *this;
	}

	attribute& add_argument(const boost::string_ref arg)
	noexcept
	{
		assert(m_arg_count != max_arg_count);
		if (m_type.id() == attribute_id::locale) {
			assert(m_arg_count == 0);
			m_locale_name = arg;
		}
		else {
			m_args[m_arg_count] = parse_argument(m_type, m_arg_count, arg);
		}
		++m_arg_count;
		return *this;
	}

	const Char& operator[](uint8_t n)
	const noexcept
	{
		assert(n <= max_arg_count);
		return m_args[n];
	}

	const boost::string_ref locale_name()
	const noexcept
	{
		assert(m_arg_count == 1);
		return m_locale_name;
	}
};

template <class Char, class Traits>
void apply_manipulator_attribute(
	const attribute<Char, Traits>& attr,
	std::basic_ostream<Char, Traits>& dst
)
{
	switch (attr.description().id()) {
	case attribute_id::locale:
		using string = std::basic_string<Char, Traits>;
		dst.imbue(std::locale(static_cast<string>(attr.locale_name())));
		break;
	case attribute_id::octal:
		dst << std::oct;
		break;
	case attribute_id::decimal:
		dst << std::dec;
		break;
	case attribute_id::hex:
		dst << std::hex;
		break;
	case attribute_id::base:
		if (attr.arguments() == 0) {
			dst << std::showbase;
		}
		else {
			dst << std::showbase << std::uppercase;
		}
		break;
	case attribute_id::precision:
		dst << std::setprecision(attr[1]);
		break;
	case attribute_id::fixed:
		dst << std::fixed;
		break;
	case attribute_id::scientific:
		dst << std::scientific;
		break;
	default:
		throw std::runtime_error{"Invalid attribute type."};
	}
}

template <class T, class Char, class Traits,
typename std::enable_if<
	std::is_arithmetic<T>::value, int
>::type = 0>
void apply_string_output_attribute(
	const attribute<Char, Traits>& attr,
	const T& t,
	std::basic_ostream<Char, Traits>& dst
)
{
	auto id = attr.description().id();

	if (id == attribute_id::bool_) {
		auto flags = dst.flags();
		dst << std::boolalpha << (bool)t;
		dst.setf(flags);
	}
	else if (id == attribute_id::money) {
		auto flags = dst.flags();
		if (attr.arguments() == 0) {
			dst << std::showbase
				<< std::put_money(static_cast<long double>(t));
		}
		else {
			// Use international currency strings.
			dst << std::showbase
				<< std::put_money(static_cast<long double>(t), true);
		}
		dst.setf(flags);
	}
	else if (id == attribute_id::sign) {
		auto s = static_cast<sign_option>(attr[0]);
		auto flags = dst.flags();
		if (s == sign_option::always) {
			dst << std::showpos << t;
		}
		else {
			if (t >= 0) {
				dst << std::noshowpos << " " << t;
			}
			else {
				dst << std::noshowpos << t;
			}
		}
		dst.setf(flags);
	}
	else if (id == attribute_id::binary) {
		auto tmp = t;
		if (dst.flags() & std::ios::showbase) {
			if (dst.flags() & std::ios::uppercase) {
				dst << "0B";
			}
			else {
				dst << "0b";
			}
		}
		dst << std::bitset<8 * sizeof(T)>(
			reinterpret_cast<unsigned long long&>(tmp));
	}
	else if (id == attribute_id::percent) {
		/*
		** TODO: Ideally, we should detect this during compile time, but
		** I don't want to go through the redundant template
		** specialization bullshit now.
		*/
		if (!std::is_floating_point<T>::value) {
			throw std::runtime_error{"Percent attribute only "
				"applies to floating-point types."};
		}
		auto flags = dst.flags();
		dst << std::fixed << (100 * t) << "%";
		dst.flags(flags);
	}
	else {
		throw std::runtime_error{"Invalid attribute type."};
	}
}

template <class T, class Char, class Traits,
typename std::enable_if<
	!std::is_arithmetic<T>::value, int
>::type = 0>
void apply_string_output_attribute(
	const attribute<Char, Traits>& attr,
	const T& t,
	std::basic_ostream<Char, Traits>& dst
)
{
	auto id = attr.description().id();

	if (id == attribute_id::quote) {
		dst << "\"" << t << "\"";
	}
	else {
		throw std::runtime_error{"Invalid attribute type."};
	}
}

template <class Char1, class Traits1, class Char2, class Traits2>
void apply_string_output_attribute(
	const attribute<Char2, Traits2>& attr,
	const boost::basic_string_ref<Char1, Traits1>& str,
	std::basic_ostream<Char2, Traits2>& dst
)
{
	using string = std::basic_string<Char1, Traits1>;
	auto id = attr.description().id();

	if (id == attribute_id::align) {
		if (attr.arguments() < 2 || attr.arguments() > 3) {
			throw std::runtime_error{"Too few arguments for "
				"align attribute."};
		}

		auto flags = dst.flags();
		auto old_width = dst.width();
		auto old_fill = dst.fill();

		auto dir = (char)attr[0];
		auto width = (size_t)attr[1];

		if (dir == 'C') {
			auto fill = ' ';
			if (attr.arguments() == 3) {
				fill = attr[2];
			}

			if (str.length() >= width) {
				dst << str.substr(0, width);
			}
			else {
				/*
				** FIXME: This is broken for unicode strings,
				** because we should not determine length by
				** counting elements.
				*/
				size_t fill_left = (width - str.length()) / 2;
				size_t fill_right = width - str.length() - fill_left;

				for (size_t i = 0; i != size_t{fill_left}; ++i) {
					dst << fill;
				}
				dst << str;
				for (size_t i = 0; i != size_t{fill_right}; ++i) {
					dst << fill;
				}
			}
			goto restore;
		}
		else if (dir == 'L') {
			dst << std::left << std::setw(width);
		}
		else if (dir == 'R') {
			dst << std::right << std::setw(width);
		}
		if (attr.arguments() == 3) {
			dst << std::setfill((char)attr[2]);
		}
		dst << str;
	restore:
		dst.flags(flags);
		dst.width(old_width);
		dst.fill(old_fill);
	}
	else if (id == attribute_id::quote) {
		dst << "\"" << str << "\"";
	}
	else if (id == attribute_id::upper) {
		auto loc = dst.getloc();
		for (const auto& c : str) {
			dst << std::toupper(c, loc);
		}
	}
	else if (id == attribute_id::lower) {
		auto loc = dst.getloc();
		for (const auto& c : str) {
			dst << std::tolower(c, loc);
		}
	}
	else if (id == attribute_id::money) {
		auto flags = dst.flags();
		if (attr.arguments() == 0) {
			dst << std::showbase
				<< std::put_money(static_cast<string>(str));
		}
		else {
			// Use international currency strings.
			dst << std::showbase
				<< std::put_money(static_cast<string>(str), true);
		}
		dst.flags(flags);
	}
	else {
		throw std::runtime_error{"Invalid attribute type."};
	}
}

}

#endif
