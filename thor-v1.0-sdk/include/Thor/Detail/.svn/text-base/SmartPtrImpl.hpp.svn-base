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

#ifndef THOR_SMARTPTRIMPL_HPP
#define THOR_SMARTPTRIMPL_HPP

#include <Thor/Tools/NonCopyable.hpp>
#include <Thor/Detail/Metaprogramming.hpp>
#include <Thor/Detail/SafeBoolIdiom.hpp>

#include <cstddef>		// NULL
#include <algorithm>
#include <cassert>


namespace thor
{
namespace detail
{

	// Helper class for various smart-pointer implementations to reduce code duplication
	// Actual documentation: See any of the wrapping smart-pointer classes
	template <typename T>
	struct SmartPtrImpl : private NonCopyable
	{
		public:
			typedef void			(*DestroyFnType)(T*);

		public:
									SmartPtrImpl();
			explicit				SmartPtrImpl(T* pointer);
									SmartPtrImpl(T* pointer, DestroyFnType destroyFn);
									~SmartPtrImpl();
		
			void					Swap(SmartPtrImpl& rhs);
			T*						Release();
			bool					IsNull() const;
			T&						operator* () const;
			T*						operator-> () const;
			T*						Get() const;

			DestroyFnType			GetDestroyFn() const;
			
		private:
			T*						mPointer;
			DestroyFnType			mDestroyFn;
	};

	// Global swap
	template <typename T>
	void swap(SmartPtrImpl<T>& lhs, SmartPtrImpl<T>& rhs);

} // namespace detail
} // namespace thor

#include <Thor/Detail/SmartPtrImpl.inl>
#endif // THOR_SMARTPTRIMPL_HPP
