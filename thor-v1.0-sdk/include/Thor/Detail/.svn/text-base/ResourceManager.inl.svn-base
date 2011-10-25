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

namespace thor
{

template <class Resource, class ResourceKey>
ResourceManager<Resource, ResourceKey>::ResourceManager()
: mMap()
, mReleaseStrategy(Resources::ExplicitRelease)
, mLoadingFailureStrategy(Resources::ThrowException)
{
}

template <class Resource, class ResourceKey>
ResourceManager<Resource, ResourceKey>::~ResourceManager()
{
	// Deallocate memory
	THOR_FOREACH(typename ResourceMap, mMap, itr)
		delete itr->second;
}

template <class Resource, class ResourceKey>
ResourcePtr<Resource> ResourceManager<Resource, ResourceKey>::Search(const ResourceKey& key)
{
	SlotIterator itr = mMap.find(key);
	
	// Return found resource or NULL if not found
	if (itr == mMap.end())
		return ResourcePtr<Resource>();
	else
		return ResourcePtr<Resource>(*itr->second);
}

template <class Resource, class ResourceKey>
ResourcePtr<const Resource> ResourceManager<Resource, ResourceKey>::Search(const ResourceKey& key) const
{
	SlotConstIterator itr = mMap.find(key);
	
	// Return found resource or NULL if not found
	if (itr == mMap.end())
		return ResourcePtr<const Resource>();
	else
		return ResourcePtr<const Resource>(*itr->second);
}

template <class Resource, class ResourceKey>
ResourcePtr<Resource> ResourceManager<Resource, ResourceKey>::Acquire(const ResourceKey& key)
{
	SlotIterator itr = mMap.find(key);

	// Load and insert resource, if not stored yet
	if (itr == mMap.end())
		return AddResource(itr, key);

	// If resource is already stored, return pointer to it
	return ResourcePtr<Resource>(*itr->second);
}

template <class Resource, class ResourceKey>
bool ResourceManager<Resource, ResourceKey>::Release(const ResourceKey& key)
{
	// Find corresponding map entry
	SlotIterator itr = mMap.find(key);
	assert(itr != mMap.end());
	
	// Unload and remove resource
	if (itr->second->IsUnused())
	{
		RemoveResource(itr);
		return true;
	}
	else
	{
		itr->second->SetAutoReleaseFlag();
		return false;
	}
}

template <class Resource, class ResourceKey>
void ResourceManager<Resource, ResourceKey>::SetLoadingFailureStrategy(Resources::LoadingFailureStrategy strategy)
{
	mLoadingFailureStrategy = strategy;
}

template <class Resource, class ResourceKey>
void ResourceManager<Resource, ResourceKey>::SetReleaseStrategy(Resources::ReleaseStrategy strategy)
{
	mReleaseStrategy = strategy;
}

template <class Resource, class ResourceKey>
ResourcePtr<Resource> ResourceManager<Resource, ResourceKey>::AddResource(SlotIterator itr, const ResourceKey& key) 
{
	// Try to load resource, react with strategy at failure
	MovedPtr<Resource> resource = key.Load();
	if (!resource)
	{
		switch (mLoadingFailureStrategy)
		{
			case Resources::ThrowException:
				throw ResourceLoadingException("Failed to load resource \"" + detail::GetKeyInfo(key) + "\"");
				break;

			case Resources::ReturnNullPointer:
				return ResourcePtr<Resource>();
		}
	}

	// When succeeded, create resource slot...
	MovedPtr<ResourceSlot> slot( new ResourceSlot(resource, mReleaseStrategy == Resources::AutoRelease) );
	
	// ...and insert it into the map and link iterator/resource manager
	itr = mMap.insert( std::make_pair(key, slot.Get()) ).first;
	itr->second->SetEnvironment(*this, itr);
	
	// If an exception is thrown by the key's copy constructor or map::insert(), the memory is freed
	// Otherwise, we can release ownership of the slot (the map element owns it now)
	slot.Release();

	// And finally return the pointer to the inserted element
	return ResourcePtr<Resource>(*itr->second);
}

template <class Resource, class ResourceKey>
void ResourceManager<Resource, ResourceKey>::RemoveResource(SlotIterator itr)
{
	// Deallocate and remove resource from map
	delete itr->second;
	mMap.erase(itr);
}

} // namespace thor
