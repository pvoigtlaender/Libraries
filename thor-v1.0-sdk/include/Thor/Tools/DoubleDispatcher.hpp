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

/// @file
/// @brief Class template thor::DoubleDispatcher

#ifndef THOR_DOUBLEDISPATCHER_HPP
#define THOR_DOUBLEDISPATCHER_HPP

#include <Thor/Tools/NonCopyable.hpp>
#include <Thor/Tools/ForEach.hpp>
#include <Thor/Tools/Exceptions.hpp>
#include <Thor/Detail/BinaryFunction.hpp>
#include <Thor/Detail/AssociativeHelpers.hpp>
#include <Thor/Detail/Metaprogramming.hpp>
#include <Thor/Detail/TypeInfo.hpp>
#include <Thor/Config.hpp>

#include <vector>
#include <algorithm>
#include <cassert>


namespace thor
{

/// @addtogroup Tools
/// @{

/// @brief Class that is able to perform dynamic dispatch on multiple functions with two parameters.
/// @details Sometimes you encounter the situation where you need to implement polymorphic behavior to dispatch
///  dynamically on more than one type. Like overloading functions with two parameters at compile time, this class
///  allows you to perform a dispatch on two arguments at runtime. At invocation time, all you need is the static
///  type of the base class, the %DoubleDispatcher figures out which dynamic types match which function.
/// @tparam B Reference or pointer to polymorphic base class. This is the base class of every dispatched function's
///  parameter type. When it is a pointer, the arguments of the dispatched functions shall be pointers too (the
///  same applies to references).
///  the dispatched functions shall have arguments of type pointer or reference to const, too.
/// @tparam R Return type of the dispatched functions.
template <class B, typename R = void>
class DoubleDispatcher : private NonCopyable
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Static assertions
	
	// Make sure that B is either T* or T&, where T is a polymorphic base class (containing virtual functions).
	THOR_STATIC_ASSERT( 
		std::tr1::is_pointer<B>::value && std::tr1::is_polymorphic< typename std::tr1::remove_pointer<B>::type >::value
	 || std::tr1::is_reference<B>::value && std::tr1::is_polymorphic< typename std::tr1::remove_reference<B>::type >::value )


	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Constructor
		/// @param symmetric Is true if the calls <b>fn(a,b)</b> and <b>fn(b,a)</b> are equivalent and it's enough
		///  to register one of both variants. Otherwise, both calls have to be registered separately and are resolved
		///  to different functions.
		explicit					DoubleDispatcher(bool symmetric = true);

		/// @brief Destructor
		/// 
									~DoubleDispatcher();

		/// @brief Registers a global function.
		/// @tparam D1 Type of the derived class for the first parameter. Must be explicitly specified.
		/// @tparam D2 Type of the derived class for the second parameter. Must be explicitly specified.
		/// @param globalFunction Pointer to function to register.
		/// @details Note that # is a placeholder for either & or *. The types D1# and D2# have the same attributes as B
		/// (pointer, reference, const-qualification): For instance, <b>B=const Base&</b> implies <b>D1#=const Derived1&</b>.
		/// @n Example (class hierarchy and dispatcher declaration missing):
		/// @code 
		/// // Overloaded global or namespace-level functions
		/// void Func(Derived1&, Derived1&);
		/// void Func(Derived1&, Derived2&);
		/// void Func(Derived2&, Derived2&);
		///
		/// // Register functions
		/// dispatcher.Register<Derived1, Derived1>(&Func);
		/// dispatcher.Register<Derived1, Derived2>(&Func);
		/// dispatcher.Register<Derived2, Derived2>(&Func);
		/// @endcode
		/// @pre A function taking two arguments of dynamic type D1 and D2 is not registered yet.
		template <class D1, class D2>
		void						Register(R (*globalFunction)( THOR_REPLICATE(B,D1), THOR_REPLICATE(B,D2) ));

		/// @brief Registers a member function.
		/// @tparam D1 Type of the derived class for the first parameter. Must be explicitly specified.
		/// @tparam D2 Type of the derived class for the second parameter. Must be explicitly specified.
		/// @tparam C Class that holds the member function.
		/// @param memberFunction Pointer to member function to register.
		/// @param object Reference to object on which the member function is invoked.
		/// @details Note that # is a placeholder for either & or *. The types D1# and D2# have the same attributes as B
		/// (pointer, reference, const-qualification): For instance, <b>B=const Base&</b> implies <b>D1#=const Derived1&</b>.
		/// @n Example (class hierarchy and dispatcher declaration missing):
		/// @code 
		/// // Class with overloaded member functions
		/// struct MyClass
		/// {
		///     void MemFunc(Derived1&, Derived1&);
		///     void MemFunc(Derived1&, Derived2&);
		///     void MemFunc(Derived2&, Derived2&);
		/// } obj;
		///
		/// // Register member functions
		/// dispatcher.Register<Derived1, Derived1>(&MyClass::MemFunc, obj);
		/// dispatcher.Register<Derived1, Derived2>(&MyClass::MemFunc, obj);
		/// dispatcher.Register<Derived2, Derived2>(&MyClass::MemFunc, obj);
		/// @endcode
		/// @pre A function taking two arguments of dynamic type D1 and D2 is not registered yet.
		template <class D1, class D2, class C>
		void						Register(R (C::*memberFunction)( THOR_REPLICATE(B,D1), THOR_REPLICATE(B,D2) ), C& object);

		/// @brief Registers a function object.
		/// @tparam D1 Type of the derived class for the first parameter. Must be explicitly specified.
		/// @tparam D2 Type of the derived class for the second parameter. Must be explicitly specified.
		/// @tparam Fn Type of the function object. Can be deduced from the argument.
		/// @param functionObject Functor to register.
		/// @details Incomplete example using a function object (you can also have separate functors for each function):
		/// @code
		/// // Class for function objects
		/// struct Functor
		/// {
		/// 	void operator() (Derived1&, Derived1&);
		/// 	void operator() (Derived1&, Derived2&);
		/// 	void operator() (Derived2&, Derived2&);
		/// };
		///
		/// // Register functor
		/// dispatcher.Register<Derived1, Derived1>(Functor());
		/// dispatcher.Register<Derived1, Derived2>(Functor());
		/// dispatcher.Register<Derived2, Derived2>(Functor());
		/// @endcode
		/// @pre A function taking two arguments of dynamic type D1 and D2 is not registered yet.
		template <class D1, class D2, typename Fn>
		void						Register(const Fn& functionObject);

		/// @brief Dispatches the dynamic types of @a arg1 and @a arg2 and invokes the corresponding function.
		/// @param arg1 First function argument. Note that the argument's dynamic type must match @b exactly
		///  with the registered type, derived-to-base conversions are not supported.
		/// @param arg2 Second function argument. Note that the argument's dynamic type must match @b exactly
		///  with the registered type, derived-to-base conversions are not supported.
		/// @return The return value of the dispatched function, if any.
		/// @throw FunctionCallException when no corresponding function is found.
		R							Call(B arg1, B arg2) const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:
		typedef std::pair<detail::TypeInfo, detail::TypeInfo>	Key;
		typedef detail::BinaryFunctionBase<B, R>*				Value;
		typedef detail::KeyValuePair<Key, Value>				Pair;
		typedef std::vector<Pair>								FnMap;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private member functions
	private:
		// Registers the type-id key with its associated function value.
		void							InternalRegister(detail::TypeInfo key1, detail::TypeInfo key2, Value value);

		// Finds the key in the map. Returns end() if not found.
		typename FnMap::const_iterator	Find(detail::TypeInfo key1, detail::TypeInfo key2) const;

		// Makes sure that the keys are sorted in case we use symmetric argument dispatching.
		Key								MakeArgumentPair(detail::TypeInfo key1, detail::TypeInfo key2) const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		FnMap						mMap;
		bool						mSymmetric;
};

/// @class DoubleDispatcher
/// @code
/// // Example class hierarchy
/// class Base { public: virtual ~Base() {} };
/// class Derived1 : public Base {};
/// class Derived2 : public Base {};
///
/// // Free functions for the derived types
/// void Func(Derived1* lhs, Derived1* rhs);
/// void Func(Derived1* lhs, Derived2* rhs);
/// void Func(Derived2* lhs, Derived2* rhs);
///
/// // Create dispatcher and register functions
/// thor::DoubleDispatcher<Base*> dispatcher;
/// dispatcher.Register<Derived1, Derived1>(&Func);
/// dispatcher.Register<Derived1, Derived2>(&Func);
/// dispatcher.Register<Derived2, Derived2>(&Func);
///
/// // Invoke functions on base class pointer
/// Base* ptr = new Derived1;
/// dispatcher.Call(ptr, ptr); // Invokes void Func(Derived1* lhs, Derived1* rhs);
/// delete ptr;
/// @endcode

/// @}

} // namespace thor

#include <Thor/Detail/DoubleDispatcher.inl>
#endif // THOR_DOUBLEDISPATCHER_HPP
