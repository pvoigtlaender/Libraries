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

#include <Thor/Resources/AudioKeys.hpp>
#include <Thor/Detail/ResourceKeyHelpers.hpp>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>


namespace thor
{
namespace Resources
{

	SoundBufferKey::SoundBufferKey()
	{
	}

	SoundBufferKey SoundBufferKey::FromFile(const std::string& fileName, const std::string& tag)
	{
		SoundBufferKey tmp;
		tmp.mLoader =	tr1::bind(&sf::SoundBuffer::LoadFromFile, _1, fileName);
		tmp.mKey =		detail::Tagger("File") << fileName << tag;
		return tmp;
	}

	SoundBufferKey SoundBufferKey::FromMemory(const void* data, std::size_t size, const std::string& tag)
	{
		SoundBufferKey tmp;
		tmp.mLoader =	tr1::bind(&sf::SoundBuffer::LoadFromMemory, _1, data, size);
		tmp.mKey =		detail::Tagger("Memory") << data << size << tag;
		return tmp;
	}

	SoundBufferKey SoundBufferKey::FromSamples(const sf::Int16* samples, std::size_t samplesCount, unsigned int channelsCount,
		unsigned int sampleRate, const std::string& tag)
	{
		SoundBufferKey tmp;
		tmp.mLoader =	tr1::bind(&sf::SoundBuffer::LoadFromSamples, _1, samples, samplesCount, channelsCount, sampleRate);
		tmp.mKey =		detail::Tagger("Samples") << samples << samplesCount << channelsCount << sampleRate << tag;
		return tmp;
	}

	MovedPtr<sf::SoundBuffer> SoundBufferKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void SoundBufferKey::Swap(SoundBufferKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const SoundBufferKey& lhs, const SoundBufferKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	MusicKey::MusicKey()
	{
	}

	MusicKey MusicKey::FromFile(const std::string& fileName, const std::string& tag)
	{
		MusicKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Music::OpenFromFile, _1, fileName);
		tmp.mKey =		detail::Tagger("File") << fileName << tag;
		return tmp;
	}

	MusicKey MusicKey::FromMemory(const void* data, std::size_t size, const std::string& tag)
	{
		MusicKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Music::OpenFromMemory, _1, data, size);
		tmp.mKey =		detail::Tagger("Memory") << data << size << tag;
		return tmp;
	}

	MovedPtr<sf::Music> MusicKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void MusicKey::Swap(MusicKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const MusicKey& lhs, const MusicKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

} // namespace Resources
} // namespace thor
