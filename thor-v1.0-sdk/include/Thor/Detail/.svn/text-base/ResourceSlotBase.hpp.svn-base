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

#ifndef THOR_RESOURCESLOTBASE_HPP
#define THOR_RESOURCESLOTBASE_HPP

#include <Thor/Tools/NonCopyable.hpp>


namespace thor
{

template <class Resource>
class ResourcePtr;


namespace detail
{

	// Polymorphic base class for resource slots
	template <class Resource>
	class ResourceSlotBase : private NonCopyable
	{
		protected:
			typedef ResourcePtr<Resource>			Ptr;
			typedef ResourcePtr<const Resource>		ConstPtr;


		public:
			// Constructor
			explicit ResourceSlotBase(Resource* resourcePointer)
			: mResourcePointer(resourcePointer)
			{
			}
		
			// Virtual destructor
			virtual ~ResourceSlotBase()
			{
			}
			
			// Indirection because only this class is a friend of ResourcePtr
			void InvalidatePtr(Ptr& ptr)
			{
				ptr.Invalidate();
			}

			// Indirection because only this class is a friend of ResourcePtr
			void InvalidatePtr(ConstPtr& ptr)
			{
				ptr.Invalidate();
			}

			// Gives access to the resource.
			Resource* GetResourcePointer()
			{
				return mResourcePointer;
			}
		
			// Gives read-only access to the resource.
			const Resource* GetResourcePointer() const
			{
				return mResourcePointer;
			}

			// Increases the reference counter for resource pointers.
			virtual void IncRef(Ptr* pointer) const = 0;

			// Increases the reference counter for const resource pointers.		
			virtual void IncRef(ConstPtr* pointer) const = 0;

			// Decreases the reference counter for resource pointers.
			// If zero, the "unused resource" action is performed.
			virtual void DecRef(Ptr* pointer) const = 0;
		
			// Decreases the reference counter for const resource pointers.
			// If zero, the "unused resource" action is performed.
			virtual void DecRef(ConstPtr* pointer) const = 0;

			// Returns true if no ResourcePtr points to this resource slot.
			virtual bool IsUnused() const = 0;


		private:
			Resource* mResourcePointer;	// direct pointer to resource

	};

} // namespace detail
} // namespace thor

#endif // THOR_RESOURCESLOTBASE_HPP
