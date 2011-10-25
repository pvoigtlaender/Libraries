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
/// @brief Factory functions that create different shapes (concave and convex)

#ifndef THOR_SHAPES_HPP
#define THOR_SHAPES_HPP

#include <Thor/Multimedia/ConcaveShape.hpp>
#include <Thor/Config.hpp>


namespace thor
{

/// @addtogroup Multimedia
/// @{

/// @brief Namespace for predefined shapes
/// @details This namespace contains some functions to create predefined shapes like stars or rounded rectangles.
///  The namespace Shapes can be considered an extension to the sf::Shape's static factory functions.
namespace Shapes
{

	/// @brief Creates a rectangle with radiused corners.
	/// @param leftUpperPosition The left-upper position (of a virtual surrounding rectangle with sharp corners).
	/// @param size Width and height of the rectangle.
	/// @param cornerRadius The radius of the circle at the corners.
	/// @param fillColor The rounded rectangle's fill color.
	/// @param outlineThickness The thickness of the outline.
	/// @param outlineColor Color used for the outline.
	/// @return A sf::Shape copy containing the rounded rectangle.
	sf::Shape THOR_API			RoundedRect(sf::Vector2f leftUpperPosition, sf::Vector2f size, float cornerRadius,
									const sf::Color& fillColor, float outlineThickness = 0.f, const sf::Color& outlineColor = sf::Color(0,0,0));

	/// @brief Creates a rectangle with radiused corners.
	/// @param left,top The left-upper position (of a virtual surrounding rectangle with sharp corners).
	/// @param width,height Width and height of the rectangle.
	/// @param cornerRadius the radius of the circle at the corners.
	/// @param fillColor The rounded rectangle's fill color.
	/// @param outlineThickness The thickness of the outline.
	/// @param outlineColor Color used for the outline.
	/// @return A sf::Shape copy containing the rounded rectangle.
	sf::Shape THOR_API			RoundedRect(float left, float top, float width, float height, float cornerRadius,
									const sf::Color& fillColor, float outlineThickness = 0.f, const sf::Color& outlineColor = sf::Color(0,0,0));

	/// @brief Creates a regular, convex polygon shape.
	/// @param nbPoints The number of polygon points (the smallest possible value is 3 for a triangle).
	/// @param center The position of the star's center.
	/// @param radius The distance from the center to the points (> 0.f).
	/// @param fillColor The color which is used to fill the inside of the polygon.
	/// @param outlineThickness The thickness of the outline.
	/// @param outlineColor The color used for the outline.
	/// @return A sf::Shape copy representing the regular polygon.
	sf::Shape THOR_API			Polygon(unsigned int nbPoints, sf::Vector2f center, float radius, const sf::Color& fillColor,
									float outlineThickness = 0.f, const sf::Color& outlineColor = sf::Color(0,0,0));

	/// @brief Creates a regular star shape.
	/// @param nbStarPoints The number of points (the smallest possible is a 3-pointed star).
	/// @param center The position of the star's center.
	/// @param innerRadius The distance from the center to the inner points (> 0.f).
	/// @param outerRadius The distance from the inner points to the outer points  (> 0.f).
	/// @param fillColor The color which is used to fill the star.
	/// @param outlineThickness The thickness of the outline.
	/// @param outlineColor The color used for the outline.
	/// @return A ConcaveShape instance representing the star.
	ConcaveShape THOR_API		Star(unsigned int nbStarPoints, sf::Vector2f center, float innerRadius, float outerRadius, const sf::Color& fillColor,
									float outlineThickness = 0.f, const sf::Color& outlineColor = sf::Color(0,0,0));

	/// @brief Creates a pie (a sector of a circle).
	/// @param center The position of the circle's center.
	/// @param radius Radius of the circle.
	/// @param filledAngle The part of the circle which is filled (angle in degrees). The value doesn't have to be inside [0,360[.
	/// @param fillColor The color which is used to fill the star.
	/// @param outlineThickness The thickness of the outline.
	/// @param outlineColor The color used for the outline.
	/// @return A ConcaveShape instance representing the pie.
	ConcaveShape THOR_API		Pie(sf::Vector2f center, float radius, float filledAngle, const sf::Color& fillColor,	float outlineThickness = 0.f,
									const sf::Color& outlineColor = sf::Color(0,0,0));	

} // namespace Shapes

/// @}

} // namespace thor

#endif // THOR_SHAPES_HPP
