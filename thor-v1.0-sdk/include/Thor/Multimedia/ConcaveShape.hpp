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
/// @brief Class thor::ConcaveShape

#ifndef THOR_CONCAVESHAPE_HPP
#define THOR_CONCAVESHAPE_HPP

#include <Thor/Math/TriangulationFigures.hpp>
#include <Thor/Detail/Swap.hpp>
#include <Thor/Config.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <vector>


namespace thor
{

/// @addtogroup Multimedia
/// @{

/// @brief Concave shape class
/// @details This class has the same interface and functionality as sf::Shape, but is additionally able to work
///  with shapes that are concave.
class THOR_API ConcaveShape : public sf::Drawable
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Creates an empty shape.
		/// @details You can use AddPoint() to build your own concave shape.
									ConcaveShape();
							
		/// @brief Implicit constructor that adapts an existing sf::Shape.
		/// @details The concave shape should look as similar as possible to the original sf::Shape, however there may occur
		///  small deviations.
									ConcaveShape(const sf::Shape& shape);

		/// @brief Exchanges the content of two instances in O(1).
		///
		void						Swap(ConcaveShape& other);
		
		/// @brief Adds a point to the concave shape.
		/// @param x,y Point position.
		/// @param color Point color (color in area between points is interpolated).
		/// @param outlineColor Color of the shape's outline (color in line between points is interpolated).
		void						AddPoint(float x, float y, const sf::Color& color, const sf::Color& outlineColor = sf::Color(0,0,0));
								
		/// @brief Adds a point to the concave shape.
		/// @param position Point position.
		/// @param color Point color (color in area between points is interpolated).
		/// @param outlineColor Color of the shape's outline (color in line between points is interpolated).
		void						AddPoint(sf::Vector2f position, const sf::Color& color,	const sf::Color& outlineColor = sf::Color(0,0,0));

		/// @brief Sets the thickness of the shape's outline (0.f by default).
		/// @details @a outlineThickness must be greater or equal to zero. If it is zero, no outline is visible.
		void						SetOutlineThickness(float outlineThickness);
		
		/// @brief Returns the shape's outline thickness.
		///
		float						GetOutlineThickness() const;
		

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:	 
		struct Point : Vertex
		{
										Point(sf::Vector2f position, const sf::Color& fillColor, const sf::Color& outlineColor);

			sf::Color					fillColor;
			sf::Color					outlineColor;
		};
		
		// Container typedefs
		typedef std::vector<sf::Shape>		ShapeContainer;
		typedef std::vector<Point>			PointContainer;
		typedef std::vector< Edge<Point> >	EdgeContainer;

		struct TriangleGenerator;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private member functions
	private:
		// Renders the shape to target.
		virtual void				Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
		
		// Computes how the shape can be split up into convex triangles.
		void						Decompose() const;
				
		// Forms the outline out of the given edges.
		void						FormOutline() const;
				

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		PointContainer				mPoints;
		float						mOutlineThickness;

		mutable EdgeContainer		mEdges;
		mutable ShapeContainer		mTriangleShapes;
		mutable ShapeContainer		mEdgeShapes;
		mutable bool				mNeedsTriangleUpdate;
		mutable bool				mNeedsEdgeUpdate;
};

/// @relates ConcaveShape
/// @brief Exchanges the contents of two concave shapes.
THOR_GLOBAL_SWAP(ConcaveShape)

/// @}

} // namespace thor

#endif // THOR_CONCAVESHAPE_HPP
