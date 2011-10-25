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
/// @brief Class template thor::CopiedPtr

#ifndef THOR_COPIEDPTR_HPP
#define THOR_COPIEDPTR_HPP

#include <Thor/SmartPtr/CopiedPtrPolicies.hpp>
#include <Thor/Detail/SmartPtrImpl.hpp>
#include <Thor/Config.hpp>

#include <algorithm>
#include <cassert>


namespace thor
{

/// @addtogroup SmartPtr
/// @{

/// @brief Generic smart pointer class that supports several deep copy ownership policies.
/// @tparam T The pointee type @n
/// @tparam OwnershipPolicy Template used for copy and destruction semantics. The policies StaticCopy, DynamicCopy and 
///  VirtualClone are shipped with the library, but you can also specify your own. A user-defined copy policy must be a class
///  template with T as template type-parameter. It has to support the following public functions (by the way, they can be
///  function templates themselves to recognize a pointer type different from T*, namely U* - the same as used in CopiedPtr(U*)
///  and Reset(U*)).
///  - <i>static T* Copy(const T* originPtr);</i>
///  @n The function performing a deep copy. Note that the @a Copy() function is never passed a null pointer. In case an
///  empty smart pointer (pointing to @a NULL) is copied, @a Copy() isn't invoked - i.e., both smart pointers are
///  empty after the operation. It might be of advantage if your copy mechanism checks pre- and postconditions with @a assert.
///  @n@n
///  - <i>static void Destroy(T* pointer);</i>
///  @n The function used to destroy and deallocate the held object. The three provided policies just use the delete operator.
template <typename T, template <typename> class OwnershipPolicy>
class CopiedPtr
{
	// --------------------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Default constructor
		/// @details Initializes the smart pointer with a null pointer. This operation doesn't require T to be defined.
									CopiedPtr();

		/// @brief Constructor from raw pointer
		/// @param pointer The initial pointer value, either pointing to an object allocated by the @a new operator or to @a NULL.
		///  In case you use this CopiedPtr with the DynamicCopy policy, ensure that the static and dynamic type of the passed 
		///  pointer are equal (therefore, don't pass base class pointers that actually refer to derived classes).
		/// @tparam U Type of the assigned object, where U* is implicitly convertible to T*.
		template <typename U>
		explicit					CopiedPtr(U* pointer);
							
		/// @brief Copy constructor
		/// @details Deep copy: If @a origin is empty, this instance becomes empty as well. Otherwise, @a OwnershipPolicy::Copy()
		///  is invoked, passing the raw pointer of @a origin as argument. After this operation, both CopiedPtr instances are
		///  either empty, or hold two independent, equal objects.
									CopiedPtr(const CopiedPtr& origin);

		/// @brief Destructor
		/// @details Invokes @a OwnershipPolicy::Destroy() with the pointer as argument. For the three default policies, the
		///  behavior is equivalent to deleting the pointer.
									~CopiedPtr();
		
		/// @brief Copy assignment operator
		/// @details Deep copy: Implemented by copy and swap, calls the copy constructor. After this operation, both CopiedPtr
		///  instances are either empty, or hold an independent, equal object.
		CopiedPtr&					operator= (const CopiedPtr& origin);

		/// @brief Swaps the pointers of @a *this and @a other.
		/// @details Swap() doesn't operate on the object itself, only on the pointer. T may be incomplete at invocation.
		void						Swap(CopiedPtr& other);
		
		/// @brief Resets the internal pointer to @a NULL.
		/// @details Destroys the current object, and sets the internal pointer to @a NULL.  This operation doesn't require T to
		///  be defined.
		void						Reset();
			
		/// @brief Resets the internal pointer to the passed value.
		/// @details Destroys the current object, and re-assigns the pointer.
		/// @param pointer The new pointer value, either pointing to an object allocated by the @a new operator or to @a NULL.
		///  In case you use this CopiedPtr with the DynamicCopy policy, ensure that the static and dynamic type of the pointer
		///  are equal (therefore, don't pass base class pointers that actually refer to derived classes).
		/// @tparam U Type of the assigned object, where U* is implicitly convertible to T*.
		template <typename U>
		void						Reset(U* pointer);
		
		/// @brief Transfers ownership of the held object to the caller. 
		/// @details Upon invoking Release(), the caller becomes responsible for the memory management of the
		///  returned pointer. This instance points to null after the operation.
		T*							Release();
			
		/// @brief Checks whether the pointer currently points to @a NULL.
		/// @details This allows you to write statements of the form <i>if(ptr)</i> or <i>if(!ptr)</i> in a type-safe way
		///  (@a ptr refers to a smart-pointer instance). The actual return type is implementation-defined.
		/// @return bool-like value that behaves in conditional expressions like true, if the pointer is valid; 
		///  and like false, if it points to @a NULL.
									operator THOR_DETAIL SafeBool() const;

		/// @brief Dereferences the pointer.
		/// @pre The smart pointer must be non-empty.
		T&							operator* () const;
		
		/// @brief Dereferences the pointer for member access.
		/// @pre The smart pointer must be non-empty.
		T*							operator-> () const;
		
		/// @brief Permits access to the internal pointer. Designed for rare use.
		/// @return Internally used pointer, use it wisely not to upset the CopiedPtr's memory management.
		T*							Get() const;
		

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		detail::SmartPtrImpl<T>		mImpl;
		T*							(*mCopyFn)(const T*);
	
		
	// ---------------------------------------------------------------------------------------------------------------------------
	// Friends
	friend detail::SmartPtrImpl<T>& detail::GetImpl<T, CopiedPtr>(CopiedPtr& smartPointer);
};

/// @relates CopiedPtr
/// @brief Swaps two CopiedPtr<T, OwnershipPolicy> instances.
template <typename T, template <typename> class OwnershipPolicy>
void swap(CopiedPtr<T, OwnershipPolicy>& lhs, CopiedPtr<T, OwnershipPolicy>& rhs);

/// @}

} // namespace thor

#include <Thor/Detail/CopiedPtr.inl>
#endif // THOR_COPIEDPTR_HPP
