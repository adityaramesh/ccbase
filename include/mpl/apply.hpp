/*
** File Name:	apply.hpp
** Author:	Aditya Ramesh
** Date:	07/18/2013
** Contact:	_@adityaramesh.com
**
** The `apply` function applies a template template parameter `Function` to a
** parameter pack `Ts...`. This is tricker than it sounds, because `Function`
** can either be a template alias or a template struct.
*/

#ifndef Z3C81EB73_0D6C_4245_9C56_DDAD0D891205
#define Z3C81EB73_0D6C_4245_9C56_DDAD0D891205

#include <type_traits>
#include <mpl/sequence.hpp>

namespace mpl {

/*
** The given template template parameter may either be a struct or a template
** alias. In the first case, the struct must define a type called `type`. In the
** second case, the result is obtained directly by instantiating the template
** alias. Since these two kinds have different semantics, we need to write a
** function that determines whether a given template template parameter is a
** template alias or not.
*/

template <class T>
struct check : std::true_type {};

template <
	template <class...> class Function,
	class                     S,
	class                     Check = void
>
struct is_alias : std::true_type {};

template <
	template <class...> class Function,
	class...                  Ts
>
struct is_alias<
	Function,
	sequence<Ts...>,
	typename std::enable_if<
		check<typename Function<Ts...>::type>::value
	>::type
> : std::false_type {};

template <
	bool                      IsAlias,
	template <class...> class Function,
	class                     S
>
struct apply_impl;

template <template <class...> class Function, class... Ts>
struct apply_impl<true, Function, sequence<Ts...>>
{
	using type = Function<Ts...>;
};

template <template <class...> class Function, class... Ts>
struct apply_impl<false, Function, sequence<Ts...>>
{
	using type = typename Function<Ts...>::type;
};

template <template <class...> class Function, class... Args>
using apply = typename apply_impl<
	is_alias<Function, sequence<Args...>>::value,
	Function,
	sequence<Args...>
>::type;

template <template <class...> class Function, class S>
struct apply_sequence_impl;

template <template <class...> class Function, class... Args>
struct apply_sequence_impl<Function, sequence<Args...>>
{
	using type = apply<Function, Args...>;
};

template <template <class...> class Function, class S>
using apply_sequence = typename apply_sequence_impl<Function, S>::type;

}

#endif
