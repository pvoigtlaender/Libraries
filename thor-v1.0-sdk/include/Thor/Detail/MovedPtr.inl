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

template <typename T>
MovedPtr<T>::MovedPtr()
: mImpl()
{ // Initialize with dummy functions to avoid dependency on T, in case the actual objects are never accessed
}

template <typename T>
MovedPtr<T>::MovedPtr(T* pointer)
: mImpl(pointer)
{
}

template <typename T>
MovedPtr<T>::MovedPtr(MovedPtr& origin)
: mImpl()
{
	// Move semantics through swapping
	mImpl.Swap(origin.mImpl);
}

template <typename T>
MovedPtr<T>::~MovedPtr()
{
	// mImpl destroys and deallocates the pointer
}

template <typename T>
MovedPtr<T>& MovedPtr<T>::operator= (MovedPtr<T>& origin)
{
	MovedPtr temp(origin);
	Swap(temp);
	return *this;
}

template <typename T>
void MovedPtr<T>::Swap(MovedPtr<T>& other)
{
	detail::swap(mImpl, other.mImpl);
}

template <typename T>
void MovedPtr<T>::Reset()
{
	MovedPtr tmp;
	Swap(tmp);
}

template <typename T>
void MovedPtr<T>::Reset(T* pointer)
{
	MovedPtr tmp(pointer);
	Swap(tmp);
}

template <typename T>
T* MovedPtr<T>::Release()
{
	return mImpl.Release();
}

template <typename T>
MovedPtr<T>::operator detail::SafeBool() const
{
	return detail::ToSafeBool(!mImpl.IsNull());
}

template <typename T>
T& MovedPtr<T>::operator* () const
{
	return mImpl.operator*();
}

template <typename T>
T* MovedPtr<T>::operator-> () const
{
	return mImpl.operator->();
}

template <typename T>
T* MovedPtr<T>::Get() const
{
	return mImpl.Get();
}

template <typename T>
MovedPtr<T>::MovedPtr(detail::MovedPtrRef<T> ref)
: mImpl(ref.mPointer, ref.mDestroyFn)
{
}

template <typename T>
MovedPtr<T>& MovedPtr<T>::operator= (detail::MovedPtrRef<T> ref)
{
	MovedPtr tmp(ref);
	Swap(tmp);
	return *this;
}

template <typename T>
MovedPtr<T>::operator detail::MovedPtrRef<T> ()
{
	// Create carrier between functions
	detail::MovedPtrRef<T> ref(mImpl.Get(), mImpl.GetDestroyFn());
	
	// Let mImpl lose ownership without destroying the object
	mImpl.Release();
	
	return ref;
}


// ---------------------------------------------------------------------------------------------------------------------------

template <typename T>
void swap(MovedPtr<T>& lhs, MovedPtr<T>& rhs)
{
	lhs.Swap(rhs);
}

template <typename T>
bool operator== (const MovedPtr<T>&, const MovedPtr<T>&)
{
	// Error: Comparison is not allowed (because every MovedPtr is unique).
	// The operator must still exist to prevent conversion to SafeBool. 
	THOR_STATIC_ASSERT(sizeof(T) == 0);
}

template <typename T>
bool operator!= (const MovedPtr<T>&, const MovedPtr<T>&)
{
	// Error: Comparison is not allowed (because every MovedPtr is unique).
	// The operator must still exist to prevent conversion to SafeBool. 
	THOR_STATIC_ASSERT(sizeof(T) == 0);
}

} // namespace thor
