/*
** File Name: argument.hpp
** Author:    Aditya Ramesh
** Date:      08/04/2014
** Contact:   _@adityaramesh.com
*/

#ifndef ZE8E94707_4331_4D04_939E_A962E4E5F333
#define ZE8E94707_4331_4D04_939E_A962E4E5F333

#include <algorithm>
#include <type_traits>
#include <boost/range/algorithm.hpp>
#include <ccbase/format/attribute.hpp>

namespace cc {

template <class Char, class Traits>
class argument
{
	using m_attribute = attribute<Char, Traits>;
	using string_ref = boost::basic_string_ref<Char, Traits>;
	static constexpr auto max_attributes = 5;

	std::array<m_attribute, max_attributes> m_attrs;
	std::array<uint8_t, num_attribute_functions> m_attr_counts{};
	uint8_t m_attr_count{};
	uint8_t m_index{};
public:
	explicit argument() noexcept {}

	explicit argument(uint8_t index)
	noexcept : m_index{index} {}

	argument(const argument& rhs) noexcept :
	m_attr_count{rhs.m_attr_count},
	m_index{rhs.m_index}
	{
		std::copy(rhs.m_attrs.data(), rhs.m_attrs.data() + m_attr_count,
			m_attrs.data());
		boost::copy(rhs.m_attrs, m_attrs.begin());
	}

	uint8_t index() const noexcept
	{ return m_index; }

	uint8_t attributes() const noexcept
	{ return m_attr_count; }

	argument& add_attribute(attribute_type t)
	{
		assert(m_attr_count != max_attributes);
		m_attrs[m_attr_count] = m_attribute{t};
		update_attribute_counts(m_attrs[m_attr_count].type().function());
		++m_attr_count;
		return *this;
	}

	argument& add_attribute(const string_ref str)
	{
		assert(m_attr_count != max_attributes);
		m_attrs[m_attr_count] = m_attribute{str};
		update_attribute_counts(m_attrs[m_attr_count].type().function());
		++m_attr_count;
		return *this;
	}

	uint8_t count(const attribute_function& f)
	const noexcept
	{
		auto n = static_cast<uint8_t>(f);
		assert(n < num_attribute_functions);
		return m_attr_counts[n];
	}

	m_attribute& operator[](uint8_t n)
	noexcept
	{
		assert(n < attributes());
		return m_attrs[n];
	}

	const m_attribute& operator[](uint8_t n)
	const noexcept
	{
		assert(n < attributes());
		return m_attrs[n];
	}
private:
	void update_attribute_counts(const attribute_function& f)
	{
		auto n = static_cast<uint8_t>(f);

		if (
			f == attribute_function::number_to_number ||
			f == attribute_function::number_to_string
		)
		{
			if (m_attr_counts[n] != 0) {
				throw std::runtime_error{"Incompatible attributes."};
			}
		}
		++m_attr_counts[n];
	}
};

template <
	class T,
	class Char,
	class Traits,
	class Function1,
	class Function2
>
void apply_number_to_number_attribute(
	const argument<Char, Traits>& arg,
	const T& t,
	std::basic_ostream<Char, Traits>& dst,
	std::basic_ostringstream<Char, Traits>& buf,
	const Function1& func1,
	const Function2& func2
)
{
	for (auto i = 0; i != arg.attributes(); ++i) {
		if (arg[i].type().id() == attribute_id::char_) {
			if (!std::is_integral<T>::value) {
				throw std::runtime_error{"The char attribute "
					"can only be applied to integral "
					"types."};
			}
			auto c = (char)t;
			func1(arg, c, dst, buf);
			return;
		}
		else if (arg[i].type().id() == attribute_id::number) {
			func2(arg, +t, dst, buf);
			return;
		}
	}
}

template <class Char, class Traits>
void apply_manipulator_attributes(
	const argument<Char, Traits>& arg,
	std::basic_ostream<Char, Traits>& os
)
{
	for (auto i = 0; i != arg.attributes(); ++i) {
		if (arg[i].type().function() == attribute_function::adds_manipulators) {
			apply_manipulator_attribute(arg[i], os);
		}
	}
}

template <class T, class Char, class Traits>
void apply_string_output_attributes(
	const argument<Char, Traits>& arg,
	const T&,
	std::basic_ostringstream<Char, Traits>& buf,
	uint8_t priority
)
{
	using string_ref = boost::basic_string_ref<Char, Traits>;

	for (auto i = 0; i != arg.attributes(); ++i) {
		if (arg[i].type().priority() == priority) {
			auto str = buf.str();
			buf.str("");
			apply_string_output_attribute(arg[i], string_ref{str}, buf);
		}
	}
}

template <class T, class Char, class Traits>
void apply_first_string_output_attribute(
	const argument<Char, Traits>& arg,
	const T& t,
	std::basic_ostream<Char, Traits>& os
)
{
	for (auto i = 0; i != arg.attributes(); ++i) {
		auto f = arg[i].type().function();
		if (
			f == attribute_function::number_to_string ||
			f == attribute_function::string_to_string ||
			f == attribute_function::type_to_string
		) {
			apply_string_output_attribute(arg[i], t, os);
			return;
		}
	}
}

template <class T, class Char, class Traits>
void apply_first_string_output_attribute(
	const argument<Char, Traits>& arg,
	const T& t,
	std::basic_ostream<Char, Traits>& os,
	uint8_t priority
)
{
	for (auto i = 0; i != arg.attributes(); ++i) {
		if (arg[i].type().priority() == priority) {
			apply_string_output_attribute(arg[i], t, os);
			return;
		}
	}
}

/*
** This is the specialization for types that are not arithmetic or strings.
*/
template <class T, class Enable = void>
struct apply_argument_helper
{
	template <class Char, class Traits>
	static void apply(
		const argument<Char, Traits>& arg,
		const T& t,
		std::basic_ostream<Char, Traits>& dst,
		std::basic_ostringstream<Char, Traits>& buf
	)
	{
		if (arg.count(attribute_function::number_to_number)) {
			throw std::runtime_error{"Number to number attributes "
				"are not applicable to strings."};
		}
		if (arg.count(attribute_function::number_to_string)) {
			throw std::runtime_error{"Number to string attributes "
				"are not applicable to strings."};
		}

		auto m = arg.count(attribute_function::adds_manipulators);
		auto sts = arg.count(attribute_function::string_to_string);
		auto tts = arg.count(attribute_function::type_to_string);

		/*
		** Do we need to buffer output in `buf`, or can we write to the
		** destination output stream directly?
		*/
		if (sts + tts > 1 || sts > 0) {
			std::basic_ios<Char, Traits> state{nullptr};
			if (m > 0) {
				state.copyfmt(buf);
				apply_manipulator_attributes(arg, buf);
			}

			/*
			** TODO: We could optimize this by passing `t` directly
			** to the first attribute to be applied, rather than
			** writing it to `buf`.
			*/
			buf << t;
			apply_string_output_attributes(arg, t, buf, 3);
			apply_string_output_attributes(arg, t, buf, 4);
			apply_string_output_attributes(arg, t, buf, 5);

			if (m > 0) {
				buf.copyfmt(state);
			}
			dst << buf.str();
			buf.str("");
		}
		else {
			std::basic_ios<Char, Traits> state{nullptr};
			if (m > 0) {
				state.copyfmt(dst);
				apply_manipulator_attributes(arg, dst);
			}

			if (sts + tts > 0) {
				apply_first_string_output_attribute(arg, t, dst);
			}
			else {
				dst << t;
			}

			if (m > 0) {
				dst.copyfmt(state);
			}
		}
	}
};

/*
** This is the specialization for arithmetic types.
*/
template <class T>
struct apply_argument_helper<T,
	typename std::enable_if<std::is_arithmetic<T>::value>::type
>
{
	template <class Char, class Traits>
	static void apply(
		const argument<Char, Traits>& arg,
		const T& t,
		std::basic_ostream<Char, Traits>& dst,
		std::basic_ostringstream<Char, Traits>& buf
	)
	{
		/*
		** Apply any `number_to_number` attributes.
		*/
		if (arg.count(attribute_function::number_to_number) == 1) {
			apply_number_to_number_attribute(arg, t, dst, buf,
				apply_argument_helper<char>::template apply_impl<Char, Traits>,
				apply_argument_helper<decltype(+t)>::template apply_impl<Char, Traits>
			);
		}
		else {
			apply_impl(arg, t, dst, buf);
		}
	}

	/*
	** We implement the rest of the `apply` function here to prevent
	** infinite recursion when applying `number_to_number` attributes.
	*/
	template <class Char, class Traits>
	static void apply_impl(
		const argument<Char, Traits>& arg,
		const T& t,
		std::basic_ostream<Char, Traits>& dst,
		std::basic_ostringstream<Char, Traits>& buf
	)
	{
		auto m = arg.count(attribute_function::adds_manipulators);
		auto nts = arg.count(attribute_function::number_to_string);
		auto sts = arg.count(attribute_function::string_to_string);
		auto tts = arg.count(attribute_function::type_to_string);

		/*
		** Do we need to buffer output in `buf`, or can we write to the
		** destination output stream directly?
		*/
		if (nts + sts + tts > 1 || sts > 0) {
			std::basic_ios<Char, Traits> state{nullptr};
			if (m > 0) {
				state.copyfmt(buf);
				apply_manipulator_attributes(arg, buf);
			}

			/*
			** Is there a "number to string" attribute, or should we
			** write `t` to `buf` manually to prepare for future "to
			** string" attributes?
			*/
			if (nts == 1) {
				// Apply the number to string attribute.
				apply_first_string_output_attribute(arg, t, buf, 2);
			}
			else {
				buf << t;
			}

			apply_string_output_attributes(arg, t, buf, 3);
			apply_string_output_attributes(arg, t, buf, 4);
			apply_string_output_attributes(arg, t, buf, 5);

			if (m > 0) {
				buf.copyfmt(state);
			}
			dst << buf.str();
			buf.str("");
		}
		else {
			std::basic_ios<Char, Traits> state{nullptr};
			if (m > 0) {
				state.copyfmt(dst);
				apply_manipulator_attributes(arg, dst);
			}

			if (nts + sts + tts > 0) {
				apply_first_string_output_attribute(arg, t, dst);
			}
			else {
				dst << t;
			}

			if (m > 0) {
				dst.copyfmt(state);
			}
		}
	}
};

/*
** This is the specialization for strings.
*/
template <class Char, class Traits>
struct apply_argument_helper<boost::basic_string_ref<Char, Traits>, void>
{
	using string_ref = boost::basic_string_ref<Char, Traits>;

	template <class Char_, class Traits_>
	static void apply(
		const argument<Char_, Traits_>& arg,
		const string_ref& t,
		std::basic_ostream<Char_, Traits_>& dst,
		std::basic_ostringstream<Char_, Traits_>& buf
	)
	{
		if (arg.count(attribute_function::number_to_number)) {
			throw std::runtime_error{"Number to number attributes "
				"are not applicable to strings."};
		}
		if (arg.count(attribute_function::number_to_string)) {
			throw std::runtime_error{"Number to string attributes "
				"are not applicable to strings."};
		}

		auto m = arg.count(attribute_function::adds_manipulators);
		auto sts = arg.count(attribute_function::string_to_string);
		auto tts = arg.count(attribute_function::type_to_string);

		/*
		** Do we need to buffer output in `buf`, or can we write to the
		** destination output stream directly?
		*/
		if (sts + tts > 1) {
			std::basic_ios<Char, Traits> state{nullptr};
			if (m > 0) {
				state.copyfmt(buf);
				apply_manipulator_attributes(arg, buf);
			}

			/*
			** TODO: We could optimize this by passing `t` directly
			** to the first attribute to be applied, rather than
			** writing it to `buf`.
			*/
			buf << t;
			apply_string_output_attributes(arg, t, buf, 3);
			apply_string_output_attributes(arg, t, buf, 4);
			apply_string_output_attributes(arg, t, buf, 5);

			if (m > 0) {
				buf.copyfmt(state);
			}
			dst << buf.str();
			buf.str("");
		}
		else {
			std::basic_ios<Char, Traits> state{nullptr};
			if (m > 0) {
				state.copyfmt(dst);
				apply_manipulator_attributes(arg, dst);
			}

			if (sts + tts > 0) {
				apply_first_string_output_attribute(arg, t, dst);
			}
			else {
				dst << t;
			}

			if (m > 0) {
				dst.copyfmt(state);
			}
		}
	}
};

template <class Char, class Traits, class T>
void apply(
	const argument<Char, Traits>& arg,
	const T& t,
	std::basic_ostream<Char, Traits>& dst,
	std::basic_ostringstream<Char, Traits>& buf
)
{
	apply_argument_helper<T>::apply(arg, t, dst, buf);
}

}

#endif
