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

#include <Thor/Multimedia/ConcaveShape.hpp>
#include <Thor/Math/Triangulation.hpp>
#include <Thor/Vectors/PolarVector.hpp>
#include <Thor/Tools/ForEach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>


namespace thor
{
namespace
{

	// Helper function like sf::Shape::Line(), but supplies the line with a color gradient.
	sf::Shape ColoredLine(sf::Vector2f startPos, sf::Vector2f endPos, const sf::Color& startColor, const sf::Color& endColor, float thickness)
	{
		sf::Vector2f perpendicular = UnitVector(PerpendicularVector(endPos - startPos)) * thickness;

		sf::Shape line;
		line.AddPoint(startPos - perpendicular, startColor);
		line.AddPoint(startPos + perpendicular, startColor);
		line.AddPoint(endPos + perpendicular, endColor);
		line.AddPoint(endPos - perpendicular, endColor);

		return line;
	}

} // namespace

// ---------------------------------------------------------------------------------------------------------------------------


ConcaveShape::Point::Point(sf::Vector2f position, const sf::Color& fillColor, const sf::Color& outlineColor)
: Vertex(position)
, fillColor(fillColor)
, outlineColor(outlineColor)
{
}

struct ConcaveShape::TriangleGenerator
{
	TriangleGenerator(ShapeContainer& triangles, float outlineThickness)
	: triangles(triangles)
	, outlineThickness(outlineThickness)
	{
		triangles.clear();
	}

	// Fake dereferencing
	TriangleGenerator& operator* ()
	{
		return *this;
	}
	
	// Fake pre-increment
	TriangleGenerator& operator++ ()
	{
		return *this;
	}
	
	// Fake post-increment
	TriangleGenerator& operator++ (int)
	{
		return *this;
	}
	
	// Assignment from triangle
	TriangleGenerator& operator= (const Triangle<ConcaveShape::Point>& triangle)
	{
		sf::Shape shape;
		
		for (unsigned int i = 0; i < 3; ++i)
			shape.AddPoint(triangle[i].GetPosition(), triangle[i].fillColor);
		
		triangles.push_back(shape);
		return *this;	
	}

	ShapeContainer&	triangles;
	float			outlineThickness;
};

// ---------------------------------------------------------------------------------------------------------------------------


ConcaveShape::ConcaveShape()
: sf::Drawable()
, mPoints()
, mOutlineThickness(0.f)
, mEdges()
, mTriangleShapes()
, mEdgeShapes()
, mNeedsTriangleUpdate(false)
, mNeedsEdgeUpdate(false)
{
}

ConcaveShape::ConcaveShape(const sf::Shape& shape)
: sf::Drawable(shape)
, mPoints()
, mOutlineThickness(shape.GetOutlineThickness())
, mEdges()
, mTriangleShapes(1, shape)
, mEdgeShapes()
, mNeedsTriangleUpdate(true)
, mNeedsEdgeUpdate(true)
{
	// Don't use shape directly because the concave shape's fill color distribution looks slightly different.
	// It might confuse users if the same ConcaveShape looks different when directly constructed from sf::Shape.
	for (unsigned int i = 0; i < shape.GetPointsCount(); ++i)
		AddPoint(shape.GetPointPosition(i), shape.GetPointColor(i), shape.GetPointOutlineColor(i));
}

void ConcaveShape::AddPoint(float x, float y, const sf::Color& color, const sf::Color& outlineColor)
{
	AddPoint(sf::Vector2f(x, y), color, outlineColor);
}
					
void ConcaveShape::AddPoint(sf::Vector2f position, const sf::Color& color, const sf::Color& outlineColor)
{
	mPoints.push_back( Point(position, color, outlineColor) );
	
	mNeedsTriangleUpdate = true;
	mNeedsEdgeUpdate = true;
}

void ConcaveShape::SetOutlineThickness(float outlineThickness)
{
	assert(outlineThickness >= 0.f);
	mOutlineThickness = outlineThickness;
	
	mNeedsEdgeUpdate = true;
}
		
float ConcaveShape::GetOutlineThickness() const
{
	return mOutlineThickness;
}

void ConcaveShape::Swap(ConcaveShape& other)
{
	std::swap(mPoints,              other.mPoints);
	std::swap(mOutlineThickness,    other.mOutlineThickness);
	std::swap(mEdges,               other.mEdges);
	std::swap(mTriangleShapes,      other.mTriangleShapes);
	std::swap(mEdgeShapes,          other.mEdgeShapes);
	std::swap(mNeedsTriangleUpdate, other.mNeedsTriangleUpdate);
	std::swap(mNeedsEdgeUpdate,     other.mNeedsEdgeUpdate);
}

void ConcaveShape::Render(sf::RenderTarget& target, sf::Renderer&) const
{
	// One or zero points aren't rendered
	if (mPoints.size() <= 1)
		return;
	
	// Batch logics
	if (mNeedsEdgeUpdate || mNeedsTriangleUpdate)
	{		
		if (mNeedsTriangleUpdate)
			Decompose();

		if (mNeedsEdgeUpdate)
			FormOutline();

		mNeedsEdgeUpdate = false;
		mNeedsTriangleUpdate = false;
	}
	
	// Draw all points
	THOR_CONST_FOREACH(ShapeContainer, mTriangleShapes, itr)
		target.Draw(*itr);
	
	// Draw all edges at the boundary
	THOR_CONST_FOREACH(ShapeContainer, mEdgeShapes, itr)
		target.Draw(*itr);
}

void ConcaveShape::Decompose() const
{
	mEdges.clear();

	// Split the concave polygon into convex triangles that can be represented by sf::Shape
	TriangulatePolygon(mPoints.begin(), mPoints.end(), TriangleGenerator(mTriangleShapes, mOutlineThickness), std::back_inserter(mEdges));
}

void ConcaveShape::FormOutline() const
{
	// If no outline is visible, don't create one
	if (mOutlineThickness == 0.f)
		return;

	// Create graphic edges	
	THOR_CONST_FOREACH(EdgeContainer, mEdges, itr)
	{
		const Point& first = (*itr)[0];
		const Point& second = (*itr)[1];
	
		// Insert circles at the polygon points to round the outline off
		mEdgeShapes.push_back( sf::Shape::Circle(first.GetPosition(), mOutlineThickness / 2.f, first.outlineColor) );

		// Create lines representing the edges
		mEdgeShapes.push_back( ColoredLine(first.GetPosition(), second.GetPosition(), first.outlineColor, second.outlineColor, mOutlineThickness / 2.f) );		
	}
}

} // namespace thor
