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

#include <Thor/Multimedia/Arrow.hpp>
#include <Thor/Vectors/VectorAlgebra2D.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>


namespace thor
{

float Arrow::zeroVectorTolerance = 0.5f;

Arrow::Arrow(sf::Vector2f position, sf::Vector2f direction, const sf::Color& color, float thickness)
: Drawable(position, sf::Vector2f(1.f, 1.f), 0.f, color)
, mThickness(thickness)
, mLength(thor::Length(direction))
, mDirection(direction)
, mNeedsShapeUpdate(true)
, mLine()
, mTriangle()
{
	assert(thickness > 0.f);
}

void Arrow::SetDirection(sf::Vector2f direction)
{
	mDirection = direction;
	mLength = thor::Length(direction);
	mNeedsShapeUpdate = true;
}

void Arrow::SetDirection(float dirX, float dirY)
{
	SetDirection(sf::Vector2f(dirX, dirY));
}

sf::Vector2f Arrow::GetDirection() const
{
	return mDirection;
}

void Arrow::SetThickness(float thickness)
{
	assert(thickness > 0.f);

	mThickness = thickness;
	mNeedsShapeUpdate = true;
}		

float Arrow::GetThickness() const
{
	return mThickness;
}
 
float Arrow::GetTriangleHeight() const
{
	return 4.f * mThickness;
}

void Arrow::AdaptLine() const
{
	// Use circle to represent zero vector (every vector shorter than zeroVectorTolerance
	// is considered a zero vector)
	if (mLength < zeroVectorTolerance)
	{
		mLine = sf::Shape::Circle(sf::Vector2f(), 3.f, sf::Color(0, 0, 0, 0), mThickness, GetColor());
	}
	
	// If the line length is shorter than the triangle height, don't draw the line
	else if (mLength < GetTriangleHeight())
	{
		mLine = sf::Shape();
	}
	
	// Normal arrow
	else
	{
		sf::Vector2f arrowDirection = (mLength - GetTriangleHeight()) * thor::UnitVector(mDirection);
		mLine = sf::Shape::Line(sf::Vector2f(), arrowDirection, GetThickness(), GetColor());
	}
}

void Arrow::AdaptTriangle() const
{
	// Don't draw triangle when arrow is too short
	if (mLength < zeroVectorTolerance)
	{
		mTriangle = sf::Shape();
	}
	
	// Draw normal triangle
	else
	{
		float triangleHeight = std::max(mLength, GetTriangleHeight());

		mTriangle = sf::Shape();
		mTriangle.AddPoint(triangleHeight, 0.f, GetColor());
		
		triangleHeight -= GetTriangleHeight();
		mTriangle.AddPoint(triangleHeight,  1.5f * mThickness, GetColor());
		mTriangle.AddPoint(triangleHeight, -1.5f * mThickness, GetColor());
		
		mTriangle.SetRotation(PolarAngle(mDirection));
	}
}

void Arrow::Render(sf::RenderTarget& target, sf::Renderer&) const
{
	if (mNeedsShapeUpdate)
	{
		AdaptLine();
		AdaptTriangle();
		mNeedsShapeUpdate = false;
	}

	target.Draw(mLine);
	target.Draw(mTriangle);
}

float Arrow::GetZeroVectorTolerance()
{
	return zeroVectorTolerance;
}

void Arrow::SetZeroVectorTolerance(float tolerance)
{
	assert(tolerance >= 0.f);
	zeroVectorTolerance = tolerance;
}

} // namespace thor
