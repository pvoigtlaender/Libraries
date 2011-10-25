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
T Length(const sf::Vector2<T>& vector)
{
	return TrigonometricTraits<T>::Sqrt(SquaredLength(vector));
}

template <typename T>
T SquaredLength(const sf::Vector2<T>& vector)
{
	return DotProduct(vector, vector);
}

template <typename T>
void SetLength(sf::Vector2<T>& vector, T newLength)
{
	assert(vector != sf::Vector2<T>());
	vector *= newLength / Length(vector);
}

template <typename T>
sf::Vector2<T> UnitVector(const sf::Vector2<T>& vector)
{
	assert(vector != sf::Vector2<T>());
	return vector / Length(vector);
}

template <typename T>
T PolarAngle(const sf::Vector2<T>& vector)
{
	assert(vector != sf::Vector2<T>());
	return TrigonometricTraits<T>::ArcTan2(vector.y, vector.x);
}

template <typename T>
void SetPolarAngle(sf::Vector2<T>& vector, T newAngle)
{
	// No assert here, because turning a zero vector is well-defined (yields always zero vector)

	T length = Length(vector);

	vector.x = length * TrigonometricTraits<T>::Cos(newAngle);
	vector.y = length * TrigonometricTraits<T>::Sin(newAngle);
}

template <typename T>
void Rotate(sf::Vector2<T>& vector, T angle)
{
	// No assert here, because turning a zero vector is well-defined (yields always zero vector)

	T cos = TrigonometricTraits<T>::Cos(angle);
	T sin = TrigonometricTraits<T>::Sin(angle);

	// Don't manipulate x and y separately, otherwise they're overwritten too early
	vector = sf::Vector2<T>( 
		cos * vector.x - sin * vector.y,
		sin * vector.x + cos * vector.y);
}

template <typename T>
sf::Vector2<T> RotatedVector(const sf::Vector2<T>& vector, T angle)
{
	// No assert here, because turning a zero vector is well-defined (yields always zero vector)

	sf::Vector2<T> copy = vector;
	Rotate(copy, angle);
	return copy;
}

template <typename T>
sf::Vector2<T> PerpendicularVector(const sf::Vector2<T>& vector)
{
	return sf::Vector2<T>(-vector.y, vector.x);
}

// ---------------------------------------------------------------------------------------------------------------------------


template <typename T>
T Angle(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	assert(lhs != sf::Vector2<T>() && rhs != sf::Vector2<T>());
	return TrigonometricTraits<T>::ArcTan2(CrossProduct(lhs, rhs).z, DotProduct(lhs, rhs));
}

template <typename T>
T DotProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T>
sf::Vector3<T> CrossProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	return sf::Vector3<T>( 
		0,
		0,
		lhs.x * rhs.y - lhs.y * rhs.x);
}

template <typename T>
sf::Vector2<T> ComponentwiseProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	return sf::Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <typename T>
sf::Vector2<T> ComponentwiseQuotient(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	assert(rhs.x != 0 && rhs.y != 0);
	return sf::Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

// ---------------------------------------------------------------------------------------------------------------------------


template <typename DestType, typename SourceType>
sf::Vector2<DestType> ConvertVector(const sf::Vector2<SourceType>& vector)
{
	return sf::Vector2<DestType>(
		static_cast<DestType>(vector.x),
		static_cast<DestType>(vector.y));
}

} // namespace thor
