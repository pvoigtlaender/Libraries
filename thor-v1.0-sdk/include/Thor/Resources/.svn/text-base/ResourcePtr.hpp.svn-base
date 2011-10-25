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
/// @brief Class template thor::ResourcePtr

#ifndef THOR_RESOURCEPTR_HPP
#define THOR_RESOURCEPTR_HPP

#include <Thor/Detail/ResourceSlotBase.hpp>
#include <Thor/Detail/SafeBoolIdiom.hpp>
#include <Thor/Detail/Metaprogramming.hpp>
#include <Thor/Config.hpp>

#include THOR_TR1_HEADER(type_traits)
#include <algorithm>
#include <cassert>


namespace thor
{

/// @addtogroup Resources
/// @{

/// @brief Shared ownership smart pointer allowing safe access to resources.
/// @details Objects of this class are returned from ResourceManager, when you acquire new or search for existing resources.
///  You should keep a %ResourcePtr instance everywhere you need access to a resource.
/// @n@n The %ResourcePtr has the semantics of a <i>strong reference</i>. That is, as long as it points to a resource,
///  the referenced resource cannot be released. This ensures that program parts that currently use the resource do not suddenly
///  lose access to it. The only exception is the ResourceManager's destructor, which releases all stored resources and
///  sets all ResourcePtrs in use to @a NULL.
/// @tparam Resource The resource class you want to access. If @a Resource is const-qualified, you cannot modify
///  the resource object through this smart pointer. The type @a Resource can be incomplete as long as you don't 
///  dereference the pointer.
template <class Resource>
class ResourcePtr
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:
		// Resource without const qualifier
		typedef typename std::tr1::remove_const<Resource>::type			MutableResource;

		// ResourceSlot with the same const qualification as Resource
		typedef typename detail::Conditional<
			std::tr1::is_const<Resource>::value,
			const detail::ResourceSlotBase<MutableResource>, 
			detail::ResourceSlotBase<MutableResource> >::Type			ResourceSlot;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Default constructor
		/// @details Initializes the object with a null pointer.
								ResourcePtr();
	
		/// @brief Copy constructor
		/// @details Increments the reference counter (if the resource is not @a NULL).
								ResourcePtr(const ResourcePtr& origin);
								
		/// @brief Template constructor from less const-qualified %ResourcePtr
		/// @details Allows conversion from <i>ResourcePtr<Resource></i> to <i>ResourcePtr<const Resource></i>.
		template <class Resource2>
								ResourcePtr(const ResourcePtr<Resource2>& origin);

		/// @brief Copy assignment operator
		/// @details Decrements the old reference counter, and increments the new one (if the pointer is not @a NULL).
		ResourcePtr&			operator= (const ResourcePtr& origin);


		/// @brief Template assignment operator from less const-qualified %ResourcePtr
		/// @details Allows conversion from <i>ResourcePtr<Resource></i> to <i>ResourcePtr<const Resource></i>.
		template <class Resource2>
		ResourcePtr&			operator= (const ResourcePtr<Resource2>& origin);

		/// @brief Destructor
		/// @details Decrements the reference counter. If it reaches zero (i.e. this is the last %ResourcePtr pointing to the
		///  resource) and if the corresponding ResourceManager uses the @a AutoRelease strategy, then the resource is released.
								~ResourcePtr();

		/// @brief Exchanges the contents of two instances.
		/// @details Note that this operation is for once not terribly efficient, since it involves updates of the
		///  resource-managing entities which keep track of the shared ResourcePtrs.
		void					Swap(ResourcePtr& other);

		/// @brief Resets the internal pointer to @a NULL.
		/// @details Decrements the reference counter. If it reaches zero (i.e. this is the last %ResourcePtr pointing to the
		///  resource) and if the corresponding ResourceManager uses the @a AutoRelease strategy, then the resource is released.
		void					Reset();
		
		/// @brief Checks whether the %ResourcePtr references a valid resource or points to @a NULL.
		/// @details This allows you to write statements of the form <i>if(ptr)</i> or <i>if(!ptr)</i> in a type-safe way
		///  (@a ptr is a %ResourcePtr instance). The actual return type is implementation-defined.
		/// @return bool-like value that behaves in conditional expressions like true, if the pointer is valid; 
		///  and like false, if it points to @a NULL.
								operator THOR_DETAIL SafeBool() const;

		/// @brief Dereferences the pointer.
		/// @pre The %ResourcePtr must be non-empty.
		Resource&				operator* () const;
		
		/// @brief Dereferences the pointer for member access.
		/// @pre The %ResourcePtr must be non-empty.
		Resource*				operator-> () const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Implementation details
	public:
		// Constructor from resource slot, internally used by ResourceManager
		explicit				ResourcePtr(ResourceSlot& slot);

	
	// ---------------------------------------------------------------------------------------------------------------------------
	// Private member functions
	private:		// Increases the reference counter, if required.
		void					IncRef();
		
		// Decreases the reference counter, if required.	
		void					DecRef();
		
		// Sets the internal pointer to NULL without affecting the reference counter.
		void					Invalidate();
		

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		ResourceSlot*			mSlot;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Friends
	/// @cond FriendsAreAnImplementationDetail
	template <class Resource1, class Resource2>
	friend bool operator== (const ResourcePtr<Resource1>& lhs, const ResourcePtr<Resource2>& rhs);
	
	template <class Resource2>
	friend class ResourcePtr;
	
	friend class detail::ResourceSlotBase<MutableResource>;
	/// @endcond
};

/// @relates ResourcePtr
/// @brief Swaps both %ResourcePtr objects.
template <class Resource>
void swap(ResourcePtr<Resource>& lhs, ResourcePtr<Resource>& rhs);

/// @relates ResourcePtr
/// @brief Equality comparison operator
/// @details Returns true when @a lhs and @a rhs share the same resource or are both @a NULL, and false otherwise.
///  @a Resource1 and @a Resource2 may only differ in const-qualification, apart from that the types must be the same.
template <class Resource1, class Resource2>
bool operator== (const ResourcePtr<Resource1>& lhs, const ResourcePtr<Resource2>& rhs);

/// @relates ResourcePtr
/// @brief Inequality comparison operator
/// @details Returns false when @a lhs and @a rhs share the same resource or are both @a NULL, and true otherwise.
///  @a Resource1 and @a Resource2 may only differ in const-qualification, apart from that the types must be the same.
template <class Resource1, class Resource2>
bool operator!= (const ResourcePtr<Resource1>& lhs, const ResourcePtr<Resource2>& rhs);

/// @}

} // namespace thor

#include <Thor/Detail/ResourcePtr.inl>
#endif // THOR_RESOURCEPTR_HPP
