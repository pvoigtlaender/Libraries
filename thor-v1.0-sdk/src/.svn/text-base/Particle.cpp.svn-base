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

#include <Thor/Particles/Particle.hpp>

#include <SFML/OpenGL.hpp>


namespace thor
{

Particle::Particle(float totalLifetime)
: Position()
, Velocity()
, Rotation()
, RotationSpeed()
, Scale(1.f, 1.f)
, Color(255, 255, 255)
, PassedLifetime(0.f)
, TotalLifetime(totalLifetime)
{
}

float GetPassedLifetime(const Particle& particle)
{
	return particle.PassedLifetime;
}

float GetTotalLifetime(const Particle& particle)
{
	return particle.TotalLifetime;
}

float GetRemainingLifetime(const Particle& particle)
{
	return GetTotalLifetime(particle) - GetPassedLifetime(particle);
}

float GetPassedRatio(const Particle& particle)
{
	return GetPassedLifetime(particle) / GetTotalLifetime(particle);
}

float GetRemainingRatio(const Particle& particle)
{
	return GetRemainingLifetime(particle) / GetTotalLifetime(particle);
}

} // namespace thor
