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

#ifndef THOR_MOVEDPTRREF_HPP
#define THOR_MOVEDPTRREF_HPP

#include <Thor/Detail/SmartPtrImpl.hpp>


namespace thor
{

template <typename T>
class MovedPtr;


namespace detail
{
	// Helper class that allows passing and returning MovedPtr to and from functions.
	// This is achieved by an indirect conversion MovedPtr -> MovedPtrRef -> MovedPtr.
	template <typename T>
	class MovedPtrRef
	{
		private:
			typedef typename detail::SmartPtrImpl<T>::DestroyFnType DestroyFnType;

		public:
			MovedPtrRef(T* pointer, DestroyFnType destroyFn)
			: mPointer(pointer)
			, mDestroyFn(destroyFn)
			{
			}

		private:
			T*				mPointer;
			DestroyFnType	mDestroyFn;

		friend class thor::MovedPtr<T>;
	};

} // namespace detail
} // namespace thor

#endif // THOR_MOVEDPTRREF_HPP
