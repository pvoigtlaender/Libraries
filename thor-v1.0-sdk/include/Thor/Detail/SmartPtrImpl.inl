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

	// No-Op function to assign to function pointer
	template <typename T>
	void DoNothing(T*)
	{
	}

	// Deletes the passed pointer, ensures a fully defined type
	template <typename T>
	void StaticDestroy(T* pointer)
	{
		// Ensure that T is defined here (delete doesn't require that).
		sizeof(T);
		delete pointer;
	}

	// Returns the smart pointer internals (needed for move semantics)
	template <typename T, class SmartPtr>
	SmartPtrImpl<T>& GetImpl(SmartPtr& smartPointer)
	{
		return smartPointer.mImpl;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	template <typename T>
	SmartPtrImpl<T>::SmartPtrImpl()
	: mPointer(NULL)
	, mDestroyFn(&detail::DoNothing<T>)
	{
		// Initialize with dummy function to avoid dependency on T, in case the actual objects are never accessed
	}

	template <typename T>
	SmartPtrImpl<T>::SmartPtrImpl(T* pointer)
	: mPointer(pointer)
	, mDestroyFn(&StaticDestroy<T>)
	{
	}

	template <typename T>
	SmartPtrImpl<T>::SmartPtrImpl(T* pointer, DestroyFnType destroyFn)
	: mPointer(pointer)
	, mDestroyFn(destroyFn)
	{
	}

	template <typename T>
	SmartPtrImpl<T>::~SmartPtrImpl()
	{
		// Indirection via function pointer to avoid dependency on fully defined type T in class definition
		mDestroyFn(mPointer);
	}

	template <typename T>
	void SmartPtrImpl<T>::Swap(SmartPtrImpl<T>& other)
	{
		std::swap(mPointer, other.mPointer);
		std::swap(mDestroyFn, other.mDestroyFn);
	}

	template <typename T>
	T* SmartPtrImpl<T>::Release()
	{
		// Save pointer
		T* copy = mPointer;
	
		// Empty content
		mPointer = NULL;
		mDestroyFn = &detail::DoNothing;
	
		// Return saved pointer
		return copy;
	}

	template <typename T>
	bool SmartPtrImpl<T>::IsNull() const
	{
		return mPointer == NULL;
	}

	template <typename T>
	T& SmartPtrImpl<T>::operator* () const
	{
		assert(!IsNull());
		return *mPointer;
	}

	template <typename T>
	T* SmartPtrImpl<T>::operator-> () const
	{
		assert(!IsNull());
		return mPointer;
	}

	template <typename T>
	T* SmartPtrImpl<T>::Get() const
	{
		return mPointer;
	}

	template <typename T>
	typename SmartPtrImpl<T>::DestroyFnType	SmartPtrImpl<T>::GetDestroyFn() const
	{
		return mDestroyFn;
	}

	template <typename T>
	void swap(SmartPtrImpl<T>& lhs, SmartPtrImpl<T>& rhs)
	{
		lhs.Swap(rhs);
	}

} // namespace detail
} // namespace thor
