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

#include <Thor/Resources/GraphicsKeys.hpp>
#include <Thor/Detail/ResourceKeyHelpers.hpp>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Font.hpp>


namespace thor
{
namespace Resources
{

	ImageKey::ImageKey()
	{
	}

	ImageKey ImageKey::FromSize(unsigned int width, unsigned int height, const sf::Color& fillColor, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Image::Create, _1, width, height, fillColor);
		tmp.mKey =		detail::Tagger("Size") << width << height << fillColor << tag;
		return tmp;
	}

	ImageKey ImageKey::FromFile(const std::string& fileName, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Image::LoadFromFile, _1, fileName);
		tmp.mKey =		detail::Tagger("File") << fileName << tag;
		return tmp;
	}

	ImageKey ImageKey::FromMemory(const void* data, std::size_t size, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Image::LoadFromMemory, _1, data, size);
		tmp.mKey =		detail::Tagger("Memory") << data << size << tag;
		return tmp;
	}

	ImageKey ImageKey::FromPixels(unsigned int width, unsigned int height, const sf::Uint8* pixels, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Image::LoadFromPixels, _1, width, height, pixels);
		tmp.mKey =		detail::Tagger("Pixels") << width << height << pixels << tag;
		return tmp;
	}

	MovedPtr<sf::Image> ImageKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void ImageKey::Swap(ImageKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const ImageKey& lhs, const ImageKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	ShaderKey::ShaderKey()
	{
	}

	ShaderKey ShaderKey::FromFile(const std::string& fileName, const std::string& tag)
	{
		ShaderKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Shader::LoadFromFile, _1, fileName);
		tmp.mKey =		detail::Tagger("File") << fileName << tag;
		return tmp;
	}

	ShaderKey ShaderKey::FromMemory(const std::string& shaderCode, const std::string& tag)
	{
		ShaderKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Shader::LoadFromMemory, _1, shaderCode);
		tmp.mKey =		detail::Tagger("Memory") << shaderCode << tag;
		return tmp;
	}

	MovedPtr<sf::Shader> ShaderKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void ShaderKey::Swap(ShaderKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const ShaderKey& lhs, const ShaderKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	FontKey::FontKey()
	{
	}

	FontKey FontKey::FromFile(const std::string& fileName, const std::string& tag)
	{
		FontKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Font::LoadFromFile, _1, fileName);
		tmp.mKey =		detail::Tagger("File") << fileName << tag;
		return tmp;
	}

	FontKey FontKey::FromMemory(const void* data, std::size_t size, const std::string& tag)
	{
		FontKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Font::LoadFromMemory, _1, data, size);
		tmp.mKey =		detail::Tagger("Memory") << data << size << tag;
		return tmp;
	}

	MovedPtr<sf::Font> FontKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void FontKey::Swap(FontKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const FontKey& lhs, const FontKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

} // namespace Resources
} // namespace thor
