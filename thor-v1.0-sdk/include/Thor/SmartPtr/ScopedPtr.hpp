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
/// @brief Class template thor::ScopedPtr

#ifndef THOR_SCOPEDPTR_HPP
#define THOR_SCOPEDPTR_HPP

#include <Thor/Tools/NonCopyable.hpp>
#include <Thor/Detail/SmartPtrImpl.hpp>
#include <Thor/Config.hpp>

#include <algorithm>
#include <cassert>


namespace thor
{

/// @addtogroup SmartPtr
/// @{

/// @brief Noncopyable smart pointer that destroys objects going out of scope.
/// @tparam T The pointee type
/// @details Copy constructor and assignment operators can't be called using this smart pointer. This implementation
///  is useful for local RAII smart pointers that don't need to share or copy ownership and that prevent you from
///  accidentally doing it. 
template <typename T>
class ScopedPtr : private NonCopyable
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Default constructor
		/// @details Initializes the smart pointer with a null pointer. This operation doesn't require T to be defined.
									ScopedPtr();

		/// @brief Constructor from raw pointer
		/// @param pointer The initial pointer value, either pointing to an object allocated by the @a new operator or to
		///  @a NULL. If the dynamic type of @a pointer is a class derived from T, then T must have a virtual destructor.
		explicit					ScopedPtr(T* pointer);
							
		/// @brief Destructor
		/// @details Destroys the object and deallocates the corresponding memory. For null pointers, nothing happens.
									~ScopedPtr();

		/// @brief Swaps the pointers of @a *this and @a other.
		/// @details Swap() doesn't operate on the object itself, only on the pointer. T may be incomplete at invocation.
		void						Swap(ScopedPtr& other);
		
		/// @brief Resets the internal pointer to @a NULL.
		/// @details Destroys the current object, and sets the internal pointer to @a NULL.  This operation doesn't require T to
		///  be defined.
		void						Reset();
			
		/// @brief Resets the internal pointer to the passed value.
		/// @details Destroys the current object, and re-assigns the pointer.
		/// @param pointer The new pointer value, either pointing to an object allocated by the @a new operator or to
		///  @a NULL. If the dynamic type of @a pointer is a class derived from T, then T must have a virtual destructor.
		void						Reset(T* pointer);
		
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
		/// @return Internally used pointer, use it wisely not to upset the ScopedPtr's memory management.
		T*							Get() const;
		

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		detail::SmartPtrImpl<T>		mImpl;
		
	
	// ---------------------------------------------------------------------------------------------------------------------------
	// Friends
	friend detail::SmartPtrImpl<T>& detail::GetImpl<T, ScopedPtr>(ScopedPtr& smartPointer);
};

/// @relates ScopedPtr
/// @brief Swaps two ScopedPtr<T> instances.
///
template <typename T>
void swap(ScopedPtr<T>& lhs, ScopedPtr<T>& rhs);

/// @}

} // namespace thor

#include <Thor/Detail/ScopedPtr.inl>
#endif // THOR_SCOPEDPTR_HPP
