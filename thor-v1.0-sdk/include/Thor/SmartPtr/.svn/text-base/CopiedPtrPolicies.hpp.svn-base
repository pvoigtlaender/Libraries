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
/// @brief Policy classes for thor::CopiedPtr

#ifndef THOR_COPIEDPTRPOLICIES_HPP
#define THOR_COPIEDPTRPOLICIES_HPP

#include <typeinfo>
#include <cassert>


namespace thor
{
namespace detail
{

	// Suppresses warnings at some compilers because the variable seems to be unused (although it is needed as typeid operand)
	inline void SuppressUnusedWarning(const void*)
	{
	}
	
	// Returns true when the dynamic types of *lhs and *rhs are equal
	template <typename T>
	bool SameDynamicPointerType(const T* lhs, const T* rhs)
	{
		SuppressUnusedWarning(lhs);
		SuppressUnusedWarning(rhs);
	
		return typeid(*lhs) == typeid(*rhs);
	}
	
	// Returns true when the dynamic types of Lhs and *rhs are equal
	template <typename Lhs>
	bool SameDynamicPointerType(const Lhs* rhs)
	{
		SuppressUnusedWarning(rhs);
			
		return typeid(Lhs) == typeid(*rhs);
	}
	
} // namespace detail

// ---------------------------------------------------------------------------------------------------------------------------


/// @addtogroup SmartPtr
/// @{

/// @brief %CopiedPtr policy that performs a deep value copy.
/// @details If the pointee shall be copied every time the owning CopiedPtr is copied, you can use this template.
///  Note that it can't handle polymorphic copies. If T* actually points to an other type than T,
///  the object is sliced. For correct behavior with polymorphism, use either DynamicCopy or VirtualClone.
template <typename T>
struct StaticCopy
{
	static T* Copy(const T* originPtr)
	{
		T* copiedPtr = new T(*originPtr);
		
		// Prevent slicing
		assert( detail::SameDynamicPointerType<T>(copiedPtr, originPtr) );
		
		return copiedPtr;
	}
	
	static void Destroy(T* pointer)
	{
		// Check if it's safe to delete pointer and if we don't slice a base object
		assert( !pointer || detail::SameDynamicPointerType<T>(pointer) );
		
		delete pointer;
	}
};

/// @brief %CopiedPtr policy that performs a deep copy depending on the object's dynamic type.
/// @details If the pointee shall be copied every time the smart pointer is copied, you can use this template.
///  This performs a dynamic copy, the called copy constructor isn't necessarily <i>T::T(const T&)</i>.
///  The prerequisite to allow this wizardry is that you pass a pointer to the actual dynamic type when invoking
///  the CopiedPtr::CopiedPtr(U*) constructor or the CopiedPtr::Reset(U*) member function. @n
template <typename T>
struct DynamicCopy
{
	template <class DynamicType> 
	static T* Copy(const DynamicType* originPtr)
	{
		T* copiedPtr = new DynamicType(*originPtr);
		
		// Make sure we called the actual dynamic type's copy constructor and prevent slicing.
		// In case this assertion fails, you didn't pass a pointer to the object's actual type at SmartPtr(U*) or Reset(U*).
		// If U is not polymorphic (which is allowed), typeid can't access the dynamic types, therefore it only compares the static
		// types, which are of course equal. In this case, the assertion is useless, but not problematic.
		// Ignore const-qualification for comparison
		assert( detail::SameDynamicPointerType<T>(copiedPtr, originPtr) );
		
		// Return pointer to deeply copied instance
		return copiedPtr;
	}
	
	template <class DynamicType> 
	static void Destroy(DynamicType* pointer)
	{	
		// Check if it's safe to delete pointer and if we don't slice a base object
		assert( !pointer || detail::SameDynamicPointerType<DynamicType>(pointer) );
		
		delete pointer;
	}
};

/// @brief %CopiedPtr policy that calls a virtual Clone() function.
/// @details Clones an instance through a polymorphic pointer. The object must support a virtual function with signature T* Clone() const
///  and, of course, a virtual destructor.
template <typename T>
struct VirtualClone
{
	static T* Copy(const T* originPtr)
	{
		T* clonedPtr = originPtr->Clone();
		
		// Make sure the Clone() function is correctly implemented (one can easily forget to override it in a derived class without
		// getting any compiler error or warning). The comparison shall not fail because of CV-qualifiers, so cast it.
		assert( detail::SameDynamicPointerType<T>(clonedPtr, originPtr) );
		
		// Return pointer to cloned instance
		return clonedPtr;
	}
	
	static void Destroy(T* pointer)
	{
		delete pointer;
	}
};

/// @}

} // namespace thor

#endif // THOR_COPIEDPTRPOLICIES_HPP
