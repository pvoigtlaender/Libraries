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

template <class B, typename R>
SingleDispatcher<B, R>::SingleDispatcher()
: mMap()
{
}

template <class B, typename R>
SingleDispatcher<B, R>::~SingleDispatcher()
{
	THOR_FOREACH(typename FnMap, mMap, itr)
		delete itr->value;
}

template <class B, typename R>
template <class D>
void SingleDispatcher<B, R>::Register(R (*globalFunction)( THOR_REPLICATE(B,D) ))
{
	InternalRegister(typeid(D),
		new detail::UnaryGlobalFunction<B, THOR_REPLICATE(B,D), R>(globalFunction));
}

template <class B, typename R>
template <class D, class C>
void SingleDispatcher<B, R>::Register(R (C::*memberFunction)( THOR_REPLICATE(B,D) ), C& object)
{
	InternalRegister(typeid(D),
		new detail::UnaryMemberFunction<B, THOR_REPLICATE(B,D), R, C>(memberFunction, object));
}

template <class B, typename R>
template <class D, typename Fn>
void SingleDispatcher<B, R>::Register(const Fn& functionObject)
{
	InternalRegister(typeid(D),
		new detail::UnaryGlobalFunction<B, THOR_REPLICATE(B,D), R, Fn>(functionObject));
}

template <class B, typename R>
R SingleDispatcher<B, R>::Call(B arg) const
{
	typename FnMap::const_iterator itr = Find(detail::DerefTypeid(arg));
	if (itr == mMap.end())
		throw FunctionCallException(std::string("SingleDispatcher::Call() - function with parameter \"") + detail::DerefTypeid(arg).GetName() +  "\" not registered");

	return itr->value->Call(arg);
}

template <class B, typename R>
void SingleDispatcher<B, R>::InternalRegister(Key key, Value value)
{
	// Note: When we accepted already registered functions, we would have to delete value.
	Pair pair(key, value);
	assert(!std::binary_search(mMap.begin(), mMap.end(), pair));

	mMap.push_back(pair);
	std::sort(mMap.begin(), mMap.end());
}

template <class B, typename R>
typename SingleDispatcher<B, R>::FnMap::const_iterator SingleDispatcher<B, R>::Find(Key key) const
{
	// Note: We only compare keys anyway, that's why we can pass a null pointer as value	
	return detail::BinarySearch(mMap.begin(), mMap.end(), Pair(key, NULL));
}

} // namespace thor
