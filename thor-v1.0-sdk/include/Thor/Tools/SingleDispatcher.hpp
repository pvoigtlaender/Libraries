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
/// @brief Class template thor::SingleDispatcher

#ifndef THOR_SINGLEDISPATCHER_HPP
#define THOR_SINGLEDISPATCHER_HPP

#include <Thor/Tools/NonCopyable.hpp>
#include <Thor/Tools/ForEach.hpp>
#include <Thor/Tools/Exceptions.hpp>
#include <Thor/Detail/UnaryFunction.hpp>
#include <Thor/Detail/AssociativeHelpers.hpp>
#include <Thor/Detail/Metaprogramming.hpp>
#include <Thor/Detail/TypeInfo.hpp>

#include <vector>
#include <algorithm>
#include <cassert>


namespace thor
{

/// @addtogroup Tools
/// @{

/// @brief Class that is able to perform dynamic dispatch on multiple functions with one parameter.
/// @details Sometimes you encounter the situation where you need to implement polymorphic behavior, but you cannot
///  or don't want to add a virtual function to an existing class hierarchy. Here comes dynamic dispatch into play:
///  You define free functions, which can be treated by the dispatcher like virtual functions.
/// @tparam B Reference or pointer to polymorphic class, which is the base class of every dispatched function's
///  parameter type. When @a B is a pointer, the arguments of the dispatched functions shall be pointers too (the
///  same applies to references).
///  If @a B is a pointer or reference to const, the dispatched functions cannot modify their arguments. In this case,
///  the dispatched functions shall have arguments of type pointer or reference to const, too.
/// @tparam R Return type of the dispatched functions.
template <class B, typename R = void>
class SingleDispatcher : private NonCopyable
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
		/// @brief Default constructor
		///
									SingleDispatcher();

		/// @brief Destructor
		/// 
									~SingleDispatcher();

		/// @brief Registers a global function.
		/// @tparam D Type of the derived class. Must be explicitly specified.
		/// @param globalFunction Pointer to function to register.
		/// @details Note that # is a placeholder for either & or *. The type D# has the same attributes as B
		/// (pointer, reference, const-qualification): For instance, <b>B=const Base&</b> implies <b>D#=const Derived1&</b>.
		/// @n Example (class hierarchy and dispatcher declaration missing):
		/// @code 
		/// // Overloaded global or namespace-level functions
		/// void Func(Derived1&);
		/// void Func(Derived2&);
		///
		/// // Register functions
		/// dispatcher.Register<Derived1>(&Func);
		/// dispatcher.Register<Derived2>(&Func);
		/// @endcode
		/// @pre A function taking an argument of dynamic type D is not registered yet.
		template <class D>
		void						Register(R (*globalFunction)( THOR_REPLICATE(B,D) ));

		/// @brief Registers a member function.
		/// @tparam D Type of the derived class. Must be explicitly specified.
		/// @tparam C Class that holds the member function.
		/// @param memberFunction Pointer to member function to register.
		/// @param object Reference to the object on which the member function is invoked.
		/// @details Note that # is a placeholder for either & or *. The type D# has the same attributes as B
		/// (pointer, reference, const-qualification): For instance, <b>B=const Base&</b> implies <b>D#=const Derived1&</b>.
		/// @n Example (class hierarchy and dispatcher declaration missing):
		/// @code 
		/// // Class with member functions
		/// struct MyClass
		/// {
		///     void MemFunc(Derived1&);
		///     void MemFunc(Derived2&);
		/// } obj;
		///
		/// // Register overloaded functions
		/// dispatcher.Register<Derived1>(&MyClass::MemFunc, obj);
		/// dispatcher.Register<Derived2>(&MyClass::MemFunc, obj);
		/// @endcode
		/// @pre A function taking an argument of dynamic type D is not registered yet.
		template <class D, class C>
		void						Register(R (C::*memberFunction)( THOR_REPLICATE(B,D) ), C& object);

		/// @brief Registers a function object.
		/// @tparam D Type of the derived class. Must be explicitly specified.
		/// @tparam Fn Type of the function object. Can be deduced from the argument.
		/// @param functionObject Functor to register. 
		/// @details Incomplete example using a function object (you can also have separate functors for each function):
		/// @code
		/// // Class for function objects
		/// struct Functor
		/// {
		/// 	void operator() (Derived1&);
		/// 	void operator() (Derived2&);
		/// };
		///
		/// // Register functor
		/// dispatcher.Register<Derived1>(Functor());
		/// dispatcher.Register<Derived2>(Functor());
		/// @endcode
		/// @pre A function taking an argument of dynamic type D is not registered yet.
		template <class D, typename Fn>
		void						Register(const Fn& functionObject);

		/// @brief Dispatches the dynamic type of @a arg and invokes the corresponding function.
		/// @param arg Function argument as a reference to the base class. Note that the argument's dynamic type must
		///  match @b exactly with the registered type, derived-to-base conversions are not supported.
		/// @return The return value of the dispatched function, if any.
		/// @throw FunctionCallException when no corresponding function is found.
		R							Call(B arg) const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:
		typedef detail::TypeInfo					Key;
		typedef detail::UnaryFunctionBase<B, R>*	Value;
		typedef detail::KeyValuePair<Key, Value>	Pair;
		typedef std::vector<Pair>					FnMap;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private member functions
	private:
		// Registers the type-id key with its associated function value
		void							InternalRegister(Key key, Value value);

		// Finds the key in the map. Returns end() if not found.
		typename FnMap::const_iterator	Find(Key key) const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		FnMap						mMap;
};

/// @class SingleDispatcher
/// @code
/// // Example class hierarchy
/// class Base { public: virtual ~Base() {} };
/// class Derived1 : public Base {};
/// class Derived2 : public Base {};
///
/// // Free functions for the derived types
/// void Func(Derived1* d);
/// void Func(Derived2* d);
///
/// // Create dispatcher and register functions
/// thor::SingleDispatcher<Base*> dispatcher;
/// dispatcher.Register<Derived1>(&Func);
/// dispatcher.Register<Derived2>(&Func);
///
/// // Invoke functions on base class pointer
/// Base* ptr = new Derived1;
/// dispatcher.Call(ptr); // Invokes void Func(Derived1* d);
/// delete ptr;
/// @endcode

/// @}

} // namespace thor

#include <Thor/Detail/SingleDispatcher.inl>
#endif // THOR_SINGLEDISPATCHER_HPP
