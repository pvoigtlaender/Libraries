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
/// @brief Class thor::Arrow

#ifndef THOR_ARROW_HPP
#define THOR_ARROW_HPP

#include <Thor/Config.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>


namespace thor
{

/// @addtogroup Multimedia
/// @{

/// @brief Drawable arrow class, inherits sf::Drawable
/// @details Arrows behave very similar to sf::Shape lines. They can be used to visualize vectors.
class THOR_API Arrow : public sf::Drawable
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public static member functions
	public:
		/// @brief Specifies the zero length tolerance.
		/// @details All arrows shorter than @a tolerance are represented as zero vectors
		///  (i.e. by circles).
		static void					SetZeroVectorTolerance(float tolerance);
		
		/// @brief Returns the zero length tolerance.
		/// @details The tolerance is the bound, below which a vector is considered a zero vector. 
		static float				GetZeroVectorTolerance();


	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief (Default) constructor
		/// @param position Starting point of the arrow.
		/// @param direction Direction of the arrow (the vector you want to represent).
		/// @param color The line and triangle color.
		/// @param thickness The line thickness.
		explicit					Arrow(sf::Vector2f position = sf::Vector2f(), sf::Vector2f direction = sf::Vector2f(),
										const sf::Color& color = sf::Color::White, float thickness = 3.f);

		/// @brief Aligns the arrow so that it points to the given direction.
		///
		void						SetDirection(sf::Vector2f direction);
		
		/// @brief Aligns the arrow so that it points to the given direction.
		///
		void						SetDirection(float dirX, float dirY);
		
		/// @brief Returns the arrow's direction.
		///
		sf::Vector2f				GetDirection() const;

		/// @brief Sets the arrow's thickness (3.f by default).
		///
		void						SetThickness(float thickness);
		
		/// @brief Returns the arrow's thickness.
		///
		float						GetThickness() const;
		

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private member functions
	private:
		float						GetTriangleHeight() const;
		void						AdaptLine() const;
		void						AdaptTriangle() const;
		void						Render(sf::RenderTarget& target, sf::Renderer& renderer) const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		float						mThickness;
		float						mLength;
		sf::Vector2f				mDirection;
	
		mutable bool				mNeedsShapeUpdate;
		mutable sf::Shape			mLine;
		mutable sf::Shape			mTriangle;
		
		static float				zeroVectorTolerance;
		
};

/// @}

} // namespace thor

#endif // THOR_ARROW_HPP
