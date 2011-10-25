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

/// @file
/// @brief String representation of basic SFML types

#ifndef THOR_TOSTRING_HPP
#define THOR_TOSTRING_HPP

// Note: Don't include specific headers to avoid unneeded dependencies. If one wants to
// output a certain object, he/she has already included the corresponding header anyway.

#include <Thor/Config.hpp>

#include <sstream>


namespace sf
{

	class Color;

	template <typename T>
	class Vector2;

	template <typename T>
	class Vector3;

	template <typename T>
	class Rect;

} // namespace sf


namespace thor
{

template <typename T>
struct PolarVector2;

/// @addtogroup Multimedia
/// @{

/// @brief Returns a std::string representation of sf::Color.
/// @details Format: (r,g,b,a)
std::string THOR_API		ToString(const sf::Color& color);

/// @brief Returns a std::string representation of sf::Vector2<T>.
/// @details Format: (x,y)
template <typename T>
std::string					ToString(const sf::Vector2<T>& vector);

/// @brief Returns a std::string representation of sf::Vector3<T>.
/// @details Format: (x,y,z)
template <typename T>
std::string					ToString(const sf::Vector3<T>& vector);

/// @brief Returns a std::string representation of sf::Rect<T>.
/// @details Format: (Left,Top;Width,Height)
template <typename T>
std::string					ToString(const sf::Rect<T>& rect);

/// @brief Returns the string representation of thor::PolarVector<T>.
/// @details Format: (r,phi�) - � represents the degree symbol (small circle)
template <typename T>
std::string					ToString(const PolarVector2<T>& vector);

/// @}

} // namespace thor

#include <Thor/Detail/ToString.inl>
#endif // THOR_TOSTRING_HPP
