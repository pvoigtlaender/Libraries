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

#include <Thor/Particles/ParticleSystem.hpp>
#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <Thor/Tools/ForEach.hpp>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>

#include <algorithm>
#include <cmath>


namespace thor
{
namespace detail
{

	// Function to setup the OpenGL view according to the passed parameter
	void SetupOpenGL2DView(const sf::View& view)
	{
		sf::Vector2f size = view.GetSize();
		sf::Vector2f center = view.GetCenter();
		sf::Vector2f position = center - size / 2.f;
	
		// Edit the OpenGL projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	
		// Setup translation (according to left-upper corner) and scale
		glOrtho(0., size.x, size.y, 0., -1., 1.);
		glTranslatef(-position.x, -position.y, 0.f);
	
		// Setup rotation 
		glTranslatef(center.x, center.y, 0.f);
		glRotatef(view.GetRotation(), 0.f, 0.f, -1.f);
		glTranslatef(-center.x, -center.y, 0.f);
	}

	// RAII Texture class
	struct Texture : private NonCopyable
	{
		explicit Texture(const sf::Image& particleImage, const sf::IntRect& particleRect = sf::IntRect())
		{
			// Copy the sub-rectangle to the image (in case of empty rects, copy whole image)
			if (particleRect.Width == 0 && particleRect.Height == 0)
				image = particleImage;
			else
				image.Copy(particleImage, 0, 0, particleRect);
		
			// Allocate the OpenGL texture
			glGenTextures(1, &id);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, id);
	
			glTexImage2D(GL_TEXTURE_2D, 0, 4, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelsPtr());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		~Texture()
		{
			// Deallocate the OpenGL texture
			glDeleteTextures(1, &id);
		}

		GLuint		id;
		sf::Image	image;
	};

	// Returns the image size as a float vector
	sf::Vector2f ImageSize(const sf::Image& image)
	{
		return sf::Vector2f(static_cast<float>(image.GetWidth()), static_cast<float>(image.GetHeight()));
	}

} // namespace detail

// ---------------------------------------------------------------------------------------------------------------------------


ParticleSystem::ParticleSystem(const sf::Image& particleImage, const sf::IntRect& particleRect)
: mParticles()
, mAffectors()
, mEmitters()
, mTexture(new detail::Texture(particleImage, particleRect))
, mGlow(false)
{
}

ParticleSystem::ParticleSystem(const sf::Image& particleImage)
: mParticles()
, mAffectors()
, mEmitters()
, mTexture(new detail::Texture(particleImage))
, mGlow(false)
{
}

void ParticleSystem::Swap(ParticleSystem& other)
{
	// Use ADL
	using std::swap;

	swap(mParticles, other.mParticles);
	swap(mAffectors, other.mAffectors);
	swap(mEmitters,  other.mEmitters);
	swap(mTexture,	 other.mTexture); 
	swap(mGlow,      other.mGlow);
}

void ParticleSystem::AddAffector(Affector::Ptr affector)
{
	assert(affector);
	assert(!ContainsAffector(affector));

	mAffectors.push_back(affector);
}

void ParticleSystem::RemoveAffector(Affector::Ptr affector)
{
	AffectorContainer::iterator itr = std::find(mAffectors.begin(), mAffectors.end(), affector);
	assert(itr != mAffectors.end());

	mAffectors.erase(itr);
}

void ParticleSystem::ClearAffectors()
{
	mAffectors.clear();
}

bool ParticleSystem::ContainsAffector(Affector::Ptr affector) const
{
	return std::find(mAffectors.begin(), mAffectors.end(), affector) != mAffectors.end();
}

void ParticleSystem::AddEmitter(Emitter::Ptr emitter)
{
	assert(emitter);
	assert(!ContainsEmitter(emitter));

	mEmitters.push_back(emitter);
}

void ParticleSystem::RemoveEmitter(Emitter::Ptr emitter)
{
	EmitterContainer::iterator itr = std::find(mEmitters.begin(), mEmitters.end(), emitter);
	assert(itr != mEmitters.end());

	mEmitters.erase(itr);
}

void ParticleSystem::ClearEmitters()
{
	mEmitters.clear();
}

bool ParticleSystem::ContainsEmitter(Emitter::Ptr emitter) const
{
	return std::find(mEmitters.begin(), mEmitters.end(), emitter) != mEmitters.end();
}

void ParticleSystem::AddParticle(const Particle& particle)
{
	mParticles.push_back(particle);
}

void ParticleSystem::Update(float dt)
{
	// Emit new particles
	THOR_FOREACH(EmitterContainer, mEmitters, itr)
		(*itr)->Emit(*this, dt);

	// Affect existing particles
	ParticleContainer::iterator writer = mParticles.begin();
	for (ParticleContainer::iterator reader = mParticles.begin(); reader != mParticles.end(); ++reader)
	{
		// Apply movement and decrease lifetime
		UpdateParticle(*reader, dt);
		
		// If current particle is not dead
		if (reader->PassedLifetime < reader->TotalLifetime)
		{
			// Only apply affectors to living particles
			THOR_FOREACH(AffectorContainer, mAffectors, itr2)
				(*itr2)->Affect(*reader, dt);

			// Go ahead
			*writer++ = *reader;
		}
	}

	// Remove particles dying this frame
	mParticles.erase(writer, mParticles.end());
}

void ParticleSystem::Draw(sf::RenderWindow& target) const
{
	PushOpenGLStates(target);

	THOR_CONST_FOREACH(ParticleContainer, mParticles, itr)
		DrawParticle(*itr);

	PopOpenGLStates(target);
}

void ParticleSystem::ClearParticles()
{
	mParticles.clear();
}

void ParticleSystem::SetGlowing(bool glow)
{
	mGlow = glow;
}

bool ParticleSystem::IsGlowing() const
{
	return mGlow;
}

void ParticleSystem::PushOpenGLStates(sf::RenderWindow& target) const
{
	// Switch to manual OpenGL handling, save SFML's state
	target.SaveGLStates();
	target.SetActive();

	// Switch blend mode, depending on glow effect	
	if (mGlow)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	else
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Store attributes and assign them
	glPushAttrib(GL_DEPTH_BITS | GL_TEXTURE_BIT);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture->id);

	// Initialize projection matrix (2D view)
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	detail::SetupOpenGL2DView(target.GetView());

	// Initialize modelview matrix (will be edited in Particle::Render())
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}

void ParticleSystem::PopOpenGLStates(sf::RenderWindow& target) const
{
	// Restore projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Restore modelview matrix
	glMatrixMode(GL_MODELVIEW); 
	glPopMatrix();

	// Restore attributes
	glPopAttrib();

	// Switch back, restore SFML's OpenGL state
	target.RestoreGLStates();
}

void ParticleSystem::UpdateParticle(Particle& particle, float dt)
{
	particle.PassedLifetime += dt;

	particle.Position += dt * particle.Velocity;
	particle.Rotation += dt * particle.RotationSpeed;
}

void ParticleSystem::DrawParticle(const Particle& particle) const
{
	// Note: At the moment, the GL_MODELVIEW matrix is being edited.

	glColor4ub(particle.Color.r, particle.Color.g, particle.Color.b, particle.Color.a);

	glLoadIdentity();
	glTranslatef(particle.Position.x, particle.Position.y, 0.f);
	glRotatef(particle.Rotation, 0.f, 0.f, 1.f);

	const sf::Vector2f halfSize = ComponentwiseProduct(particle.Scale, detail::ImageSize(mTexture->image)) / 2.f;

	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1.f, 1.f);			glVertex2f(+halfSize.x, +halfSize.y);
		glTexCoord2f(0.f, 1.f);			glVertex2f(-halfSize.x, +halfSize.y);
		glTexCoord2f(1.f, 0.f);			glVertex2f(+halfSize.x, -halfSize.y);
		glTexCoord2f(0.f, 0.f);			glVertex2f(-halfSize.x, -halfSize.y);
	glEnd();
}

} // namespace thor
