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

#include <Thor/Particles/Affector.hpp>
#include <Thor/Particles/Particle.hpp>

#include <cassert>
#include <cmath>


namespace thor
{
	
ForceAffector::Ptr ForceAffector::Create(sf::Vector2f acceleration)
{
	return Ptr( new ForceAffector(acceleration) );
}

ForceAffector::ForceAffector(sf::Vector2f acceleration)
: mAcceleration(acceleration)
{
}

void ForceAffector::Affect(Particle& particle, float dt)
{
	particle.Velocity += dt * mAcceleration;
}

void ForceAffector::SetAcceleration(sf::Vector2f acceleration)
{
	mAcceleration = acceleration;
}

sf::Vector2f ForceAffector::GetAcceleration() const
{
	return mAcceleration;
}

// ---------------------------------------------------------------------------------------------------------------------------


TorqueAffector::Ptr TorqueAffector::Create(float angularAcceleration)
{
	return Ptr( new TorqueAffector(angularAcceleration) );
}

TorqueAffector::TorqueAffector(float angularAcceleration)
: mAngularAcceleration(angularAcceleration)
{
}

void TorqueAffector::Affect(Particle& particle, float dt)
{
	particle.RotationSpeed += dt * mAngularAcceleration;
}

void TorqueAffector::SetAngularAcceleration(float angularAcceleration)
{
	mAngularAcceleration = angularAcceleration;
}

float TorqueAffector::GetAngularAcceleration() const
{
	return mAngularAcceleration;
}

// ---------------------------------------------------------------------------------------------------------------------------


FadeInAffector::Ptr FadeInAffector::Create(float timeRatio)
{
	return Ptr( new FadeInAffector(timeRatio) );
}

FadeInAffector::FadeInAffector(float timeRatio)
: mTimeRatio(timeRatio)
{
	assert(0.f <= timeRatio && timeRatio <= 1.f);
}

void FadeInAffector::Affect(Particle& particle, float /*dt*/)
{
	const float passedRatio = GetPassedRatio(particle);

	if (passedRatio < mTimeRatio)
		particle.Color.a = static_cast<sf::Uint8>(256 * passedRatio / mTimeRatio);
}

void FadeInAffector::SetTimeRatio(float timeRatio)
{
	assert(0.f <= timeRatio && timeRatio <= 1.f);
	mTimeRatio = timeRatio;
}

float FadeInAffector::GetTimeRatio() const
{
	return mTimeRatio;
}

// ---------------------------------------------------------------------------------------------------------------------------


FadeOutAffector::Ptr FadeOutAffector::Create(float timeRatio)
{
	return Ptr( new FadeOutAffector(timeRatio) );
}

FadeOutAffector::FadeOutAffector(float timeRatio)
: mTimeRatio(timeRatio)
{
	assert(0.f <= timeRatio && timeRatio <= 1.f);
}

void FadeOutAffector::Affect(Particle& particle, float /*dt*/)
{
	const float remainingRatio = GetRemainingRatio(particle);

	if (remainingRatio < mTimeRatio)
		particle.Color.a = static_cast<sf::Uint8>(256 * remainingRatio / mTimeRatio);
}

void FadeOutAffector::SetTimeRatio(float timeRatio)
{
	assert(0.f <= timeRatio && timeRatio <= 1.f);
	mTimeRatio = timeRatio;
}

float FadeOutAffector::GetTimeRatio() const
{
	return mTimeRatio;
}

// ---------------------------------------------------------------------------------------------------------------------------


ColorAffector::Ptr ColorAffector::Create(const ColorGradient& gradient)
{
	return Ptr( new ColorAffector(gradient) );
}

ColorAffector::ColorAffector(const ColorGradient& gradient)
: mGradient(gradient)
{
}

void ColorAffector::Affect(Particle& particle, float /*dt*/)
{
	// Apply color gradient
	particle.Color = mGradient.GetColor(GetPassedRatio(particle));
}

void ColorAffector::SetGradient(const ColorGradient& gradient)
{
	mGradient = gradient;
}

const ColorGradient& ColorAffector::GetGradient() const
{
	return mGradient;
}

} // namespace thor
