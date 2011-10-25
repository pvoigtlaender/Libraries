/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef THOR_METAPROGRAMMING_HPP
#define THOR_METAPROGRAMMING_HPP

#include <Thor/Config.hpp>

#include THOR_TR1_HEADER(type_traits)


namespace thor
{
namespace detail
{

	// Selects a type depending on a boolean condition.
	// If Condition is true, the result member Type evaluates to TrueType, otherwise to FalseType.
	template <bool Condition, typename TrueType, typename FalseType>
	struct Conditional
	{
		typedef TrueType Type;
	};

	template <typename TrueType, typename FalseType>
	struct Conditional<false, TrueType, FalseType>
	{
		typedef FalseType Type;
	};


	// Removes reference and pointer attribute from type
	template <typename T>
	struct RemoveIndirection
	{
		typedef typename std::tr1::remove_pointer<
			typename std::tr1::remove_reference<T>::type
		>::type Type;
	};


	// Removes reference, pointer and const attribute from type
	template <typename T>
	struct Decay
	{
		typedef typename std::tr1::remove_const<
			typename RemoveIndirection<T>::Type
		>::type Type;
	};


	// Adjusts New such that it has the same const, pointer, reference attributes as Origin
	template <typename Origin, typename New>
	struct Replicate
	{
		typedef typename Decay<New>::Type														New0;

		typedef typename Conditional<
			std::tr1::is_const<typename RemoveIndirection<Origin>::Type>::value,
			const New0,
			New0>::Type																			New1;

		typedef typename Conditional<std::tr1::is_pointer<Origin>::value, New1*, New1>::Type	New2;
		typedef typename Conditional<std::tr1::is_reference<Origin>::value, New2&, New2>::Type	New3;
		typedef typename Conditional<std::tr1::is_const<Origin>::value, const New3, New3>::Type	Type;
	};

	// Human-readable form
	#define THOR_REPLICATE(Origin, New) typename thor::detail::Replicate<Origin, New>::Type


	// Static assertion
	// Generates a compiler error upon false condition.
	template <bool Condition>
	struct StaticAssert
	{
	};

	template <>
	struct StaticAssert<false>;

	template <int N>
	struct StaticChecker
	{
	};

	// Macro concatenation, evaluating arguments
	#define THOR_PP_CONCAT_IMPL(a, b) a ## b
	#define THOR_PP_CONCAT(a, b) THOR_PP_CONCAT_IMPL(a, b)

	// Static assert: Use line-dependent macro to avoid name collisions with multiple static asserts in the same scope
	#define THOR_STATIC_ASSERT(condition) typedef thor::detail::StaticChecker< sizeof(thor::detail::StaticAssert<(condition)>) > \
		THOR_PP_CONCAT(thor_StaticChecker, __LINE__);

} // namespace detail
} // namespace thor

#endif // THOR_METAPROGRAMMING_HPP
