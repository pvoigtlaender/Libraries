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
namespace detail
{

// T: Static object type (examples: Base, int)
// U: Dynamic object type, is normally the same as T (examples: Derived, int)
template <typename T, typename U, template <typename> class OwnershipPolicy>
T* ForwardCopy(const T* pointer)
{
	// Ensure fully defined type
	sizeof(U);
	
	// Cast to U*: If Copy() is a function template parametrized with its parameter, the exact type U is 
	// recognized. Otherwise, the implicit U* -> T* conversion is automatically applied, undoing static_cast.
	return OwnershipPolicy<T>::Copy( static_cast<const U*>(pointer) );
}

// T: Static object type (examples: Base, int)
// U: Dynamic object type, is normally the same as T (examples: Derived, int)
template <typename T, typename U, template <typename> class OwnershipPolicy>
void ForwardDestroy(T* pointer)
{
	// Ensure fully defined type
	sizeof(U);
	
	// Cast to U*: If Destroy() is a function template parametrized with its pointer type, the exact type U is 
	// recognized. Otherwise, the implicit U* -> T* conversion is automatically applied, undoing static_cast.
	OwnershipPolicy<T>::Destroy( static_cast<U*>(pointer) );
}

// No-Op function to assign to function pointer
template <typename T>
T* ReturnNull(const T*)
{
	return NULL;
}

} // namespace detail


// ---------------------------------------------------------------------------------------------------------------------------

template <typename T, template <typename> class OwnershipPolicy>
CopiedPtr<T, OwnershipPolicy>::CopiedPtr()
: mImpl()
, mCopyFn(&detail::ReturnNull<T>)
{ // Initialize with dummy functions to avoid dependency on T, in case the actual objects are never accessed
}

template <typename T, template <typename> class OwnershipPolicy>
template <typename U>
CopiedPtr<T, OwnershipPolicy>::CopiedPtr(U* pointer)
: mImpl(pointer, &detail::ForwardDestroy<T, U, OwnershipPolicy>)
, mCopyFn(&detail::ForwardCopy<T, U, OwnershipPolicy>)
{
}

template <typename T, template <typename> class OwnershipPolicy>
CopiedPtr<T, OwnershipPolicy>::CopiedPtr(const CopiedPtr<T, OwnershipPolicy>& origin)
: mImpl(
	origin.mImpl.IsNull() ? NULL : origin.mCopyFn(origin.mImpl.Get()),
	origin.mImpl.GetDestroyFn())
, mCopyFn(origin.mCopyFn)
{
	// If origin is NULL, this becomes NULL as well;
	// otherwise, the object is copied.
}

template <typename T, template <typename> class OwnershipPolicy>
CopiedPtr<T, OwnershipPolicy>::~CopiedPtr()
{
	// mImpl destroys and deallocates the pointer
}

template <typename T, template <typename> class OwnershipPolicy>
CopiedPtr<T, OwnershipPolicy>& CopiedPtr<T, OwnershipPolicy>::operator= (const CopiedPtr<T, OwnershipPolicy>& origin)
{
	CopiedPtr tmp(origin);
	Swap(tmp);
	return *this;
}

template <typename T, template <typename> class OwnershipPolicy>
void CopiedPtr<T, OwnershipPolicy>::Swap(CopiedPtr<T, OwnershipPolicy>& other)
{
	detail::swap(mImpl, other.mImpl);
	std::swap(mCopyFn,	other.mCopyFn);
}

template <typename T, template <typename> class OwnershipPolicy>
void CopiedPtr<T, OwnershipPolicy>::Reset()
{
	CopiedPtr tmp;
	Swap(tmp);
}

template <typename T, template <typename> class OwnershipPolicy>
template <typename U>
void CopiedPtr<T, OwnershipPolicy>::Reset(U* pointer)
{
	CopiedPtr tmp(pointer);
	Swap(tmp);
}

template <typename T, template <typename> class OwnershipPolicy>
T* CopiedPtr<T, OwnershipPolicy>::Release()
{
	return mImpl.Release();
}

template <typename T, template <typename> class OwnershipPolicy>
CopiedPtr<T, OwnershipPolicy>::operator detail::SafeBool() const
{
	return detail::ToSafeBool(!mImpl.IsNull());
}

template <typename T, template <typename> class OwnershipPolicy>
T& CopiedPtr<T, OwnershipPolicy>::operator* () const
{
	return mImpl.operator*();
}

template <typename T, template <typename> class OwnershipPolicy>
T* CopiedPtr<T, OwnershipPolicy>::operator-> () const
{
	return mImpl.operator->();
}

template <typename T, template <typename> class OwnershipPolicy>
T* CopiedPtr<T, OwnershipPolicy>::Get() const
{
	return mImpl.Get();
}


// ---------------------------------------------------------------------------------------------------------------------------

template <typename T, template <typename> class OwnershipPolicy>
void swap(CopiedPtr<T, OwnershipPolicy>& lhs, CopiedPtr<T, OwnershipPolicy>& rhs)
{
	lhs.Swap(rhs);
}

template <typename T, template <typename> class OwnershipPolicy>
bool operator== (const CopiedPtr<T, OwnershipPolicy>&, const CopiedPtr<T, OwnershipPolicy>&)
{
	// Error: Comparison is not allowed (because every CopiedPtr is unique).
	// The operator must still exist to prevent conversion to SafeBool. 
	THOR_STATIC_ASSERT(sizeof(T) == 0);
}

template <typename T, template <typename> class OwnershipPolicy>
bool operator!= (const CopiedPtr<T, OwnershipPolicy>&, const CopiedPtr<T, OwnershipPolicy>&)
{
	// Error: Comparison is not allowed (because every CopiedPtr is unique).
	// The operator must still exist to prevent conversion to SafeBool. 
	THOR_STATIC_ASSERT(sizeof(T) == 0);
}

} // namespace thor
