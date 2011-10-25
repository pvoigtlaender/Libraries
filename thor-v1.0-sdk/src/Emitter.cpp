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

#include <Thor/Particles/Emitter.hpp>
#include <Thor/Math/Random.hpp>

#include <cmath>
#include <cassert>


namespace thor
{

DirectionalEmitter::Ptr DirectionalEmitter::Create(float particlesPerSecond, float particleLifetime)
{
	return Ptr(new DirectionalEmitter(particlesPerSecond, particleLifetime));
}

DirectionalEmitter::DirectionalEmitter(float particlesPerSecond, float particleLifetime)
: Emitter(particlesPerSecond, particleLifetime)
, mEmissionAngle(0.f)
, mParticleVelocity()
{
}

void DirectionalEmitter::Emit(Adder& system, float dt)
{
	const unsigned int nbParticles = ComputeNbParticles(dt);

	for (unsigned int i = 0; i < nbParticles; ++i)
	{
		// Create particle and specify parameters
		Particle particle = CreateParticlePrototype();
		particle.Velocity = mParticleVelocity;

		// Influence of emission angle
		float var = RandomDev(0.f, GetEmissionAngle() / 2.f);
		Rotate(particle.Velocity, var);

		system.AddParticle(particle);
	}
}

void DirectionalEmitter::SetEmissionAngle(float emissionAngle)
{
	mEmissionAngle = emissionAngle;
}

float DirectionalEmitter::GetEmissionAngle() const
{
	return mEmissionAngle;
}

void DirectionalEmitter::SetParticleVelocity(sf::Vector2f velocity)
{
	mParticleVelocity = velocity;
}

sf::Vector2f DirectionalEmitter::GetParticleVelocity() const
{
	return mParticleVelocity;
}

// ---------------------------------------------------------------------------------------------------------------------------


TargetEmitter::Ptr TargetEmitter::Create(float particlesPerSecond, float particleLifetime)
{
	return Ptr(new TargetEmitter(particlesPerSecond, particleLifetime));
}

TargetEmitter::TargetEmitter(float particlesPerSecond, float particleLifetime)
: Emitter(particlesPerSecond, particleLifetime)
, mTargetZone(GetEmissionZone().Clone())
, mParticleSpeed(0.f)
{
}

void TargetEmitter::Emit(Adder& system, float dt)
{
	const unsigned int nbParticles = ComputeNbParticles(dt);

	for (unsigned int i = 0; i < nbParticles; ++i)
	{
		// Create particle and specify parameters
		Particle particle = CreateParticlePrototype();

		// Compute vector from emission to target zone and scale it (unless it is zero)
		sf::Vector2f direction = mTargetZone->GetRandomPoint() - particle.Position;
		if (direction != sf::Vector2f())
			particle.Velocity = mParticleSpeed * UnitVector(direction);

		system.AddParticle(particle);
	}
}

void TargetEmitter::SetTargetZone(MovedPtr<Zone> zone)
{
	mTargetZone.Reset(zone.Release());
}

Zone& TargetEmitter::GetTargetZone()
{
	return *mTargetZone;
}

const Zone& TargetEmitter::GetTargetZone() const
{
	return *mTargetZone;
}

void TargetEmitter::SetParticleSpeed(float speed)
{
	mParticleSpeed = speed;
}

float TargetEmitter::GetParticleSpeed() const
{
	return mParticleSpeed;
}

} // namespace thor
