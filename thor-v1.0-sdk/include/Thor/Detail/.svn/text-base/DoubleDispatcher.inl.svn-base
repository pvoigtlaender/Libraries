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
DoubleDispatcher<B, R>::DoubleDispatcher(bool symmetric)
: mMap()
, mSymmetric(symmetric)
{
}

template <class B, typename R>
DoubleDispatcher<B, R>::~DoubleDispatcher()
{
	THOR_FOREACH(typename FnMap, mMap, itr)
		delete itr->value;
}

template <class B, typename R>
template <class D1, class D2>
void DoubleDispatcher<B, R>::Register(R (*globalFunction)( THOR_REPLICATE(B,D1), THOR_REPLICATE(B,D2) ))
{
	InternalRegister(typeid(D1), typeid(D2),
		new detail::BinaryGlobalFunction<B, THOR_REPLICATE(B,D1), THOR_REPLICATE(B,D2), R>(globalFunction));
}

template <class B, typename R>
template <class D1, class D2, class C>
void DoubleDispatcher<B, R>::Register(R (C::*memberFunction)( THOR_REPLICATE(B,D1), THOR_REPLICATE(B,D2) ), C& object)
{
	InternalRegister(typeid(D1), typeid(D2),
		new detail::BinaryMemberFunction<B, THOR_REPLICATE(B,D1), THOR_REPLICATE(B,D2), R, C>(memberFunction, object));
}

template <class B, typename R>
template <class D1, class D2, typename Fn>
void DoubleDispatcher<B, R>::Register(const Fn& functionObject)
{
	InternalRegister(typeid(D1), typeid(D2),
		new detail::BinaryGlobalFunction<B, THOR_REPLICATE(B,D1), THOR_REPLICATE(B,D2), R, Fn>(functionObject));
}

template <class B, typename R>
R DoubleDispatcher<B, R>::Call(B arg1, B arg2) const
{
	typename FnMap::const_iterator itr = Find(detail::DerefTypeid(arg1), detail::DerefTypeid(arg2));
	if (itr == mMap.end())
	{
		throw FunctionCallException(std::string("DoubleDispatcher::Call() - function with parameters \"")
			+ detail::DerefTypeid(arg1).GetName() +  "\" and \"" + detail::DerefTypeid(arg2).GetName() + "\" not registered");
	}

	return itr->value->Call(arg1, arg2);
}

template <class B, typename R>
void DoubleDispatcher<B, R>::InternalRegister(detail::TypeInfo key1, detail::TypeInfo key2, Value value)
{
	// Note: When we accepted already registered functions, we would have to delete value.
	Pair pair(MakeArgumentPair(key1, key2), value);
	assert(!std::binary_search(mMap.begin(), mMap.end(), pair));

	mMap.push_back(pair);
	std::sort(mMap.begin(), mMap.end());
}

template <class B, typename R>
typename DoubleDispatcher<B, R>::FnMap::const_iterator DoubleDispatcher<B, R>::Find(detail::TypeInfo key1, detail::TypeInfo key2) const
{
	// Note: We only compare keys anyway, that's why we can pass a null pointer as value
	Key key = MakeArgumentPair(key1, key2);
	return detail::BinarySearch(mMap.begin(), mMap.end(), Pair(key, NULL));
}

template <class B, typename R>
typename DoubleDispatcher<B, R>::Key DoubleDispatcher<B, R>::MakeArgumentPair(detail::TypeInfo key1, detail::TypeInfo key2) const
{
	// When symmetric, (key1,key2) and (key2,key1) are the same -> sort so that we always have (key1,key2)
	if (mSymmetric && key2 < key1)
		std::swap(key1, key2);

	return Key(key1, key2);
}

} // namespace thor
