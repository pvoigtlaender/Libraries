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

#include <Thor/Particles/ParticleInterfaces.hpp>
#include <Thor/Particles/Particle.hpp>
#include <Thor/Geometry/Point.hpp>
#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <Thor/Math/Random.hpp>

#include <cassert>


namespace thor
{
	
Affector::~Affector()
{
}

// ---------------------------------------------------------------------------------------------------------------------------


Emitter::Emitter(float particlesPerSecond, float particleLifetime)
: mEmissionZone(new Point(sf::Vector2f()))
, mEmissionRate(particlesPerSecond)
, mEmissionDifference(0.f)
, mParticleLifetime(particleLifetime)
, mParticleScale(1.f, 1.f)
, mParticleColor(sf::Color::White)
{
	assert(particlesPerSecond > 0.f);
	assert(particleLifetime > 0.f);
}

Emitter::~Emitter()
{
}
//
//void Emitter::Emit(Adder& system, float dt)
//{
//	// Note: This method is pure virtual. It can be called from derived classes to avoid code
//	// duplication. It itself invokes RandomOffset() which should be overridden in this case.
//
//}

void Emitter::SetEmissionZone(MovedPtr<Zone> zone)
{
	mEmissionZone.Reset(zone.Release());
}

Zone& Emitter::GetEmissionZone()
{
	return *mEmissionZone;
}

const Zone& Emitter::GetEmissionZone() const
{
	return *mEmissionZone;
}

void Emitter::SetEmissionRate(float particlesPerSecond)
{
	assert(particlesPerSecond > 0.f);
	mEmissionRate = particlesPerSecond;
}

float Emitter::GetEmissionRate() const
{
	return mEmissionRate;
}

void Emitter::SetParticleScale(sf::Vector2f scale)
{
	mParticleScale = scale;
}

sf::Vector2f Emitter::GetParticleScale() const
{
	return mParticleScale;
}

void Emitter::SetParticleColor(const sf::Color& color)
{
	mParticleColor = color;
}

const sf::Color& Emitter::GetParticleColor() const
{
	return mParticleColor;
}

void Emitter::SetParticleLifetime(float lifetime)
{
	assert(lifetime > 0.f);
	mParticleLifetime = lifetime;
}

float Emitter::GetParticleLifetime() const
{
	return mParticleLifetime;
}

unsigned int Emitter::ComputeNbParticles(float dt)
{
	// We want to fulfill the desired particle rate as exact as possible. Since the amount of emitted particles per frame is
	// integral, we have to emit sometimes more and sometimes less. mParticleDifference takes care of the deviation each frame.
	float particleAmount = mEmissionRate * dt + mEmissionDifference;
	unsigned int nbParticles = static_cast<unsigned int>(particleAmount);

	// Compute difference for next frame, return current amount
	mEmissionDifference = particleAmount - nbParticles;
	return nbParticles;
}

Particle Emitter::CreateParticlePrototype() const
{
	Particle particle(mParticleLifetime);
	particle.Position = mEmissionZone->GetRandomPoint();
	particle.Rotation = mEmissionZone->GetRotation();
	particle.Scale    = mParticleScale;
	particle.Color    = mParticleColor;

	return particle;
}

} // namespace thor
