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
ScopedPtr<T>::ScopedPtr()
: mImpl()
{ // Initialize with dummy functions to avoid dependency on T, in case the actual objects are never accessed
}

template <typename T>
ScopedPtr<T>::ScopedPtr(T* pointer)
: mImpl(pointer)
{
}

template <typename T>
ScopedPtr<T>::~ScopedPtr()
{
	// mImpl destroys and deallocates the pointer
}

template <typename T>
void ScopedPtr<T>::Swap(ScopedPtr<T>& other)
{
	detail::swap(mImpl, other.mImpl);
}

template <typename T>
void ScopedPtr<T>::Reset()
{
	ScopedPtr tmp;
	Swap(tmp);
}

template <typename T>
void ScopedPtr<T>::Reset(T* pointer)
{
	ScopedPtr tmp(pointer);
	Swap(tmp);
}

template <typename T>
T* ScopedPtr<T>::Release()
{
	return mImpl.Release();
}

template <typename T>
ScopedPtr<T>::operator detail::SafeBool() const
{
	return detail::ToSafeBool(!mImpl.IsNull());
}

template <typename T>
T& ScopedPtr<T>::operator* () const
{
	return mImpl.operator*();
}

template <typename T>
T* ScopedPtr<T>::operator-> () const
{
	return mImpl.operator->();
}

template <typename T>
T* ScopedPtr<T>::Get() const
{
	return mImpl.Get();
}


// ---------------------------------------------------------------------------------------------------------------------------

template <typename T>
void swap(ScopedPtr<T>& lhs, ScopedPtr<T>& rhs)
{
	lhs.Swap(rhs);
}

template <typename T>
bool operator== (const ScopedPtr<T>&, const ScopedPtr<T>&)
{
	// Error: Comparison is not allowed (because every ScopedPtr is unique).
	// The operator must still exist to prevent conversion to SafeBool. 
	THOR_STATIC_ASSERT(sizeof(T) == 0);
}

template <typename T>
bool operator!= (const ScopedPtr<T>&, const ScopedPtr<T>&)
{
	// Error: Comparison is not allowed (because every ScopedPtr is unique).
	// The operator must still exist to prevent conversion to SafeBool. 
	THOR_STATIC_ASSERT(sizeof(T) == 0);
}

} // namespace thor
