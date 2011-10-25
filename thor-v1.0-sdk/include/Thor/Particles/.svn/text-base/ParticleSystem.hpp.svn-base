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
/// @brief Class thor::ParticleSystem

#ifndef THOR_PARTICLESYSTEM_HPP
#define THOR_PARTICLESYSTEM_HPP

#include <Thor/Particles/ParticleInterfaces.hpp>
#include <Thor/Particles/Particle.hpp>
#include <Thor/SmartPtr/ScopedPtr.hpp>
#include <Thor/Tools/NonCopyable.hpp>
#include <Thor/Detail/Swap.hpp>
#include <Thor/Config.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>


namespace sf
{

	class RenderWindow;
	class Image;

} // namespace sf


namespace thor
{
namespace detail
{

	struct Texture;

} // namespace detail


/// @addtogroup Particles
/// @{

/// @brief Class for simple particle systems.
/// @details Like sprites, particles are represented as sub-rectangles of sf::Image. During their
///  lifetime, the particles can be affected in translation, rotation, scale and coloring.
/// @n@n This class is noncopyable.
class THOR_API ParticleSystem : private NonCopyable, private Emitter::Adder
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:
		// Container typedefs
		typedef std::vector<Particle>			ParticleContainer;
		typedef std::vector<Affector::Ptr>		AffectorContainer;
		typedef std::vector<Emitter::Ptr>		EmitterContainer;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Constructor: Takes a part of an image for a particle
		/// @param particleImage Source image used for the particle (the sf::Image is copied).
		/// @param particleRect Source rectangle of particleImage that marks the texture bounds.
									ParticleSystem(const sf::Image& particleImage, 
										const sf::IntRect& particleRect);
		
		/// @brief Constructor: Takes a whole image for a particle
		/// @param particleImage Image used for the particle (the sf::Image is copied).
		explicit					ParticleSystem(const sf::Image& particleImage);

		/// @brief Swaps the contents of two instances in constant time.
		///
		void						Swap(ParticleSystem& other);
				
		/// @brief Adds a particle affector to the system.
		/// @details Be aware that multiple affectors can interfere with each other. The affectors are applied in the order they were
		///  added to the system, therefore affectors at the end may overwrite particle states set by earlier affectors. To completely
		///  avoid the issue, only add orthogonal affectors (e.g. one for color, one for acceleration...).
		/// @param affector Shared pointer to a derivate of Affector (non-empty).
		/// @pre @a affector has not been added yet.
		void						AddAffector(Affector::Ptr affector);

		/// @brief Removes a particle affector from the system.
		/// @param affector Shared pointer to a derivate of Affector (non-empty).
		/// @pre @a affector is currently stored in the particle system.
		void						RemoveAffector(Affector::Ptr affector);

		/// @brief Removes all Affector instances from the system.
		/// @details All particles lose the influence of any extern affectors. Movement and lifetime
		///  is still computed.
		void						ClearAffectors();

		/// @brief Checks whether an affector is currently stored in the particle system.
		/// @return true if affector is used by this particle system, false otherwise.
		bool						ContainsAffector(Affector::Ptr affector) const;

		/// @brief Adds a particle emitter to the system.
		/// @param emitter Shared pointer to a derivate of Emitter (non-empty).
		/// @pre @a emitter has not been added yet.
		void						AddEmitter(Emitter::Ptr emitter);

		/// @brief Removes a particle emitter from the system.
		/// @param emitter Shared pointer to a derivate of Emitter (non-empty).
		/// @pre @a emitter is currently stored in the particle system.
		void						RemoveEmitter(Emitter::Ptr emitter);

		/// @brief Removes all Emitter instances from the system.
		/// @details Particles that are currently in the system are still processed, but no new ones
		///  are emitted until you add another emitter.
		void						ClearEmitters();
		
		/// @brief Checks whether an emitter is currently stored in the particle system.
		/// @return true if emitter is used by this particle system, false otherwise.
		bool						ContainsEmitter(Emitter::Ptr emitter) const;

		/// @brief Updates all particles in the system.
		/// @details Invokes all emitters and applies all affectors. The lifetime of every particle is decreased,
		///  dead particles are removed.
		/// @param dt Frame duration.
		void						Update(float dt);
		
		/// @brief Draws all particles in the system.
		/// @param target The render window on which the particles are drawn.
		void						Draw(sf::RenderWindow& target) const;
		
		/// @brief Removes all particles that are currently in the system.
		///
		void						ClearParticles();
		
		/// @brief Enables/disables glow effect.
		/// @details Specifies whether particles should be drawn with a glow effect.
		///  Glowing particles are especially visible on dark backgrounds.
		void						SetGlowing(bool glow);
		
		/// @brief Returns whether particles are currently drawn with a glow effect.
		///
		bool						IsGlowing() const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private member functions
	private:
		/// @brief Adds a particle to the system.
		/// @param particle Particle to add.
		void						AddParticle(const Particle& particle);
				
		// Prepares OpenGL to draw the particles.
		void						PushOpenGLStates(sf::RenderWindow& target) const;
		
		// Does some work to reset the OpenGL state.
		void						PopOpenGLStates(sf::RenderWindow& target) const;
			
		// Updates a single particle.
		void						UpdateParticle(Particle& particle, float dt);

		// Draws a single particle.
		void						DrawParticle(const Particle& particle) const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		ParticleContainer			mParticles;
		AffectorContainer			mAffectors;
		EmitterContainer			mEmitters;

		ScopedPtr<detail::Texture>	mTexture;
		bool						mGlow;
};

/// @relates ParticleSystem
/// @brief Exchanges the contents of two ParticleSystem instances.
THOR_GLOBAL_SWAP(ParticleSystem)

/// @}

} // namespace thor

#endif // THOR_PARTICLESYSTEM_HPP
