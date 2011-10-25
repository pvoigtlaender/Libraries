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

#include <Thor/Multimedia/Shapes.hpp>
#include <Thor/Vectors/PolarVector.hpp>

#include <cassert>


namespace thor
{
namespace Shapes
{

	sf::Shape RoundedRect(sf::Vector2f leftUpperPosition, sf::Vector2f size, float cornerRadius,
		const sf::Color& fillColor, float outlineThickness, const sf::Color& outlineColor)
	{
		return RoundedRect(leftUpperPosition.x, leftUpperPosition.y, size.x, size.y, cornerRadius,
			fillColor, outlineThickness, outlineColor);
	}

	sf::Shape RoundedRect(float left, float top, float width, float height, float cornerRadius,
		const sf::Color& fillColor, float outlineThickness, const sf::Color& outlineColor)
	{
		assert(outlineThickness >= 0.f);

		// Compute inner, rectangular rect and reach the outline by a radius vector.
		sf::Shape roundedRect;
		roundedRect.SetOutlineThickness(outlineThickness);

		const float right = left + width;
		const float bottom = top + height;

		sf::Vector2f	currentCorner(right - cornerRadius, bottom - cornerRadius);
		PolarVector2f	radialVec(cornerRadius, 0.f);

		const unsigned int nbSegmentsPerCorner = 20;
		const float difference = 90.f / nbSegmentsPerCorner;
	
		// right lower rounded corner
		for (; radialVec.phi < 90.f; radialVec.phi += difference)
			roundedRect.AddPoint(currentCorner + sf::Vector2f(radialVec), fillColor, outlineColor);
	
		// left lower rounded corner
		currentCorner.x = left + cornerRadius;
		for (radialVec.phi = 90.f; radialVec.phi < 180.f; radialVec.phi += difference)
			roundedRect.AddPoint(currentCorner + sf::Vector2f(radialVec), fillColor, outlineColor);
	
		// left upper rounded corner
		currentCorner.y = top + cornerRadius;
		for (radialVec.phi = 180.f; radialVec.phi < 270.f; radialVec.phi += difference)
			roundedRect.AddPoint(currentCorner + sf::Vector2f(radialVec), fillColor, outlineColor);
	
		// right upper rounded corner
		currentCorner.x = right - cornerRadius;
		for (radialVec.phi = 270.f; radialVec.phi < 360.f; radialVec.phi += difference)
			roundedRect.AddPoint(currentCorner + sf::Vector2f(radialVec), fillColor, outlineColor);
				
		return roundedRect;
	}

	sf::Shape Polygon(unsigned int nbPoints, sf::Vector2f center, float radius, const sf::Color& fillColor,
		float outlineThickness, const sf::Color& outlineColor)
	{
		assert(radius > 0.f);
		assert(outlineThickness >= 0.f);

		// Calculate points of the inner, regular polygon and the outer star points
		PolarVector2f vector(radius, 0.f);
	
		sf::Shape shape;
		shape.SetOutlineThickness(outlineThickness);	
	
		// Step around and alternately add inner and outer points
		for (unsigned int points = 0; points < nbPoints; ++points)
		{
			vector.phi = 360.f * points / nbPoints;
		
			shape.AddPoint(center + sf::Vector2f(vector), fillColor, outlineColor);
		}

		return shape;
	}
	
	ConcaveShape Star(unsigned int nbStarPoints, sf::Vector2f center, float innerRadius, float outerRadius,
		const sf::Color& fillColor, float outlineThickness, const sf::Color& outlineColor)
	{
		assert(innerRadius > 0.f);
		assert(outerRadius > 0.f);
		assert(outlineThickness >= 0.f);

		// Calculate points of the inner, regular polygon and the outer star points
		PolarVector2f inner(innerRadius, 0.f);
		PolarVector2f outer(innerRadius + outerRadius, 0.f);
	
		ConcaveShape shape;
		shape.SetOutlineThickness(outlineThickness);	
	
		// Step around and alternately add inner and outer points
		for (unsigned int points = 0; points < nbStarPoints; ++points)
		{
			inner.phi = 360.f * points / nbStarPoints;
			outer.phi = inner.phi + 180.f / nbStarPoints;
		
			shape.AddPoint(center + sf::Vector2f(inner), fillColor, outlineColor);
			shape.AddPoint(center + sf::Vector2f(outer), fillColor, outlineColor);
		}

		return shape;
	}

	ConcaveShape Pie(sf::Vector2f center, float radius, float filledAngle, const sf::Color& fillColor,
		float outlineThickness, const sf::Color& outlineColor)
	{
		assert(radius > 0.f);
	
		ConcaveShape shape;
		shape.SetOutlineThickness(outlineThickness);	
	
		filledAngle = std::fmod(filledAngle, 360.f);

		// Add center point, unless the pie is full
		if (filledAngle != 0.f)
			shape.AddPoint(center, fillColor, outlineColor);
	
		// nbTotalPoints = the points that would be there at a full circle; nbActualPoints = the actual points
		const unsigned int nbTotalPoints = 40;
		const unsigned int nbActualPoints = static_cast<unsigned int>(filledAngle / 360.f * nbTotalPoints);
	
		PolarVector2f vector(radius, 0.f);
		for (unsigned int i = 0; i <= nbActualPoints; ++i)
		{
			vector.phi = 360.f * i / nbTotalPoints;
		
			shape.AddPoint(center + sf::Vector2f(vector), fillColor, outlineColor);
		}
	
		return shape;
	}

} // namespace Shapes
} // namespace thor
