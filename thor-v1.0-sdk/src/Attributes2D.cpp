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

#include <Thor/Geometry/Attributes2D.hpp>


namespace thor
{

Positionable::Positionable(sf::Vector2f position)
: mPosition(position)
{
}

void Positionable::SetPosition(sf::Vector2f position)
{
	SetPosition(position.x, position.y);
}
	 
void Positionable::SetPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
}
	 
void Positionable::Move(sf::Vector2f offset)
{
	Move(offset.x, offset.y);
}
	 
void Positionable::Move(float offsetX, float offsetY)
{
	mPosition.x += offsetX;
	mPosition.y += offsetY;
}

sf::Vector2f Positionable::GetPosition() const
{
	return mPosition;
}

// ---------------------------------------------------------------------------------------------------------------------------


Rotatable::Rotatable(float rotation)
: mRotation(rotation)
{
}

void Rotatable::SetRotation(float rotation)
{
	mRotation = rotation;
}
	 
void Rotatable::Rotate(float angle)
{
	mRotation += angle;
}
	 
float Rotatable::GetRotation() const
{
	return mRotation;
}

// ---------------------------------------------------------------------------------------------------------------------------


Scalable::Scalable(sf::Vector2f scale)
: mScale(scale)
{
}

void Scalable::SetScale(sf::Vector2f scale)
{
	SetScale(scale.x, scale.y);
}

void Scalable::SetScale(float scaleX, float scaleY)
{
	mScale.x = scaleX;
	mScale.y = scaleY;
}

void Scalable::Scale(sf::Vector2f factor)
{
	Scale(factor.x, factor.y);
}

void Scalable::Scale(float factorX, float factorY)
{
	mScale.x *= factorX;
	mScale.y *= factorY;
}

sf::Vector2f Scalable::GetScale() const
{
	return mScale;
}

} // namespace thor
