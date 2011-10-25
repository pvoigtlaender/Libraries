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

#ifndef THOR_RESOURCESLOT_HPP
#define THOR_RESOURCESLOT_HPP

#include <Thor/Detail/ResourceSlotBase.hpp>
#include <Thor/SmartPtr/MovedPtr.hpp>
#include <Thor/Tools/ForEach.hpp>

#include <set>
#include <cassert>


namespace thor
{

template <class Resource, class ResourceKey>
class ResourceManager;


namespace detail
{

	// Concrete resource slot class, contains mainly the following data:
	// - resource
	// - iterator to resource (to remove it)
	// - pointers to all ResourcePtr objects that share the resource
	template <class Resource, class ResourceKey>
	class ResourceSlot : public ResourceSlotBase<Resource>
	{
		private:
			// Note: The combination of the using and typename keywords is buggy on g++
			typedef typename ResourceSlotBase<Resource>::Ptr		Ptr;
			typedef typename ResourceSlotBase<Resource>::ConstPtr	ConstPtr;
			typedef ResourceManager<Resource, ResourceKey>			Manager;
			typedef typename Manager::SlotIterator					SlotIterator;
		

		public:
			// Constructor, link to concrete ResourceManager instantiation
			explicit ResourceSlot(MovedPtr<Resource> resource, bool autoRelease)
			: ResourceSlotBase<Resource>(resource.Get())
			, mResource(resource)
			, mAutoRelease(autoRelease)
			, mManager(NULL)
			, mIterator()
			, mPtrSet()
			, mConstPtrSet()
			{
			}

			// Virtual destructor: Invalidates all ResourcePtr objects to this resource
			virtual ~ResourceSlot()
			{
				// Let all ResourcePtrs pointing to the slot become NULL.
				THOR_FOREACH(typename std::set<Ptr*>, mPtrSet, itr)
					InvalidatePtr(**itr);
			
				THOR_FOREACH(typename std::set<ConstPtr*>, mConstPtrSet, itr)
					InvalidatePtr(**itr);
			}

			// Post-initialization, since the object doesn't know its iterator before map insertion
			void SetEnvironment(Manager& manager, SlotIterator iterator)
			{
				mManager = &manager;
				mIterator = iterator;
			}

			// From now on, the resource is released as soon as it is unused.
			void SetAutoReleaseFlag()
			{
				mAutoRelease = true;
			}
	
			virtual void IncRef(Ptr* pointer) const
			{
				assert(mPtrSet.find(pointer) == mPtrSet.end());

				mPtrSet.insert(pointer);
			}
		
			virtual void IncRef(ConstPtr* pointer) const
			{
				assert(mConstPtrSet.find(pointer) == mConstPtrSet.end());

				mConstPtrSet.insert(pointer);
			}

			virtual void DecRef(Ptr* pointer) const
			{
				std::size_t erased = mPtrSet.erase(pointer);
				assert(erased == 1);

				// If no more pointers share this resource, release it
				if (IsUnused() && mAutoRelease)
					Destroy();
			}
	
			virtual void DecRef(ConstPtr* pointer) const
			{
				std::size_t erased = mConstPtrSet.erase(pointer);
				assert(erased == 1);

				// If no more pointers share this resource, release it
				if (IsUnused() && mAutoRelease)
					Destroy();
			}

			virtual bool IsUnused() const
			{
				return mPtrSet.empty() && mConstPtrSet.empty();
			}


		private:
			// Removes this object from the ResourceManager map
			void Destroy() const
			{
				mManager->RemoveResource(mIterator);
			}


		private:
			MovedPtr<Resource>			mResource;
			bool						mAutoRelease;
	
			Manager*					mManager;
			SlotIterator				mIterator;
		
			mutable std::set<Ptr*>		mPtrSet;
			mutable std::set<ConstPtr*> mConstPtrSet;
	};

} // namespace detail
} // namespace thor

#endif // THOR_RESOURCESLOT_HPP
