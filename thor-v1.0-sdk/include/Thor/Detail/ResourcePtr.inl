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

template <class Resource>
ResourcePtr<Resource>::ResourcePtr()
: mSlot(NULL)
{
}

template <class Resource>
ResourcePtr<Resource>::ResourcePtr(const ResourcePtr& origin)
: mSlot(origin.mSlot)
{
	IncRef();
}

template <class Resource>
template <class Resource2>
ResourcePtr<Resource>::ResourcePtr(const ResourcePtr<Resource2>& origin)
: mSlot(origin.mSlot)
{
	IncRef();
}

template <class Resource>
ResourcePtr<Resource>& ResourcePtr<Resource>::operator= (const ResourcePtr& origin)
{
	// Don't do anything when same slot (also handles self-assignment)
	if (mSlot == origin.mSlot)
		return *this;

	// Copy pointers, store temporary old pointer
	ResourceSlot* oldSlot = mSlot;
	mSlot = origin.mSlot;

	// Increment first, to prevent release in case of self assignment
	if (mSlot)		mSlot->IncRef(this);
	if (oldSlot)	oldSlot->DecRef(this);

	return *this;
}

template <class Resource>
template <class Resource2>
ResourcePtr<Resource>& ResourcePtr<Resource>::operator= (const ResourcePtr<Resource2>& origin)
{
	// Note: We can't use copy-and-swap because of different types

	// Don't do anything when same slot (also handles self-assignment)
	if (mSlot == origin.mSlot)
		return *this;

	// Copy pointers, store temporary old pointer
	ResourceSlot* oldSlot = mSlot;
	mSlot = origin.mSlot;

	// Increment first, to prevent release in case of self assignment
	if (mSlot)		mSlot->IncRef(this);
	if (oldSlot)	oldSlot->DecRef(this);

	return *this;
}

template <class Resource>
ResourcePtr<Resource>::~ResourcePtr()
{
	DecRef();
}

template <class Resource>
void ResourcePtr<Resource>::Swap(ResourcePtr& other)
{
	// When both ResourcePtrs point to the same slot, don't swap (this is not only an optimization,
	// but semantically required, because std::set can't store the same key multiple times).
	if (this->mSlot == other.mSlot)
		return;

	// Keep slot pointers to this and other updated
	// Add new targets (first, prevent unloading in case of zero refcount!)
	if (this->mSlot)	this->mSlot->IncRef(&other);
	if (other.mSlot)	other.mSlot->IncRef(this);
	
	// Remove old targets
	if (this->mSlot)	this->mSlot->DecRef(this);
	if (other.mSlot)	other.mSlot->DecRef(&other);

	// Eventually, swap slot pointers
	std::swap(mSlot, other.mSlot);
}

template <class Resource>
void ResourcePtr<Resource>::Reset()
{
	DecRef();
	mSlot = NULL;
}

template <class Resource>
ResourcePtr<Resource>::operator detail::SafeBool() const
{
	return detail::ToSafeBool(mSlot != NULL);
}

template <class Resource>
Resource& ResourcePtr<Resource>::operator* () const
{
	assert(mSlot);
	return *mSlot->GetResourcePointer();
}

template <class Resource>
Resource* ResourcePtr<Resource>::operator-> () const
{
	assert(mSlot);
	return mSlot->GetResourcePointer();
}

template <class Resource>
ResourcePtr<Resource>::ResourcePtr(ResourceSlot& slot)
: mSlot(&slot)
{
	IncRef();
}

template <class Resource>
void ResourcePtr<Resource>::IncRef()
{
	if (mSlot)
		mSlot->IncRef(this);
}

template <class Resource>
void ResourcePtr<Resource>::DecRef()
{
	if (mSlot)
		mSlot->DecRef(this);
}

template <class Resource>
void ResourcePtr<Resource>::Invalidate()
{
	mSlot = NULL;
}


// ---------------------------------------------------------------------------------------------------------------------------

template <class Resource>
void swap(ResourcePtr<Resource>& lhs, ResourcePtr<Resource>& rhs)
{
	lhs.Swap(rhs);
}

template <class Resource1, class Resource2>
bool operator== (const ResourcePtr<Resource1>& lhs, const ResourcePtr<Resource2>& rhs)
{
	// Note: Since C++ doesn't allow comparisons of pointers to different (unrelated) types, we automatically
	// get compiler errors if Resource1 and Resource2 differ in more than CV-qualification.
	return lhs.mSlot == rhs.mSlot;
}

template <class Resource1, class Resource2>
bool operator!= (const ResourcePtr<Resource1>& lhs, const ResourcePtr<Resource2>& rhs)
{
	return !(lhs == rhs);
}

} // namespace thor
