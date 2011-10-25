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
/// @brief Resource keys for SFML Graphics module

#ifndef THOR_GRAPHICSKEYS_HPP
#define THOR_GRAPHICSKEYS_HPP

#include <Thor/Resources/ResourceKeyTraits.hpp>
#include <Thor/Detail/Swap.hpp>
#include <Thor/Config.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Config.hpp>

#include THOR_TR1_HEADER(functional)
#include <string>


namespace thor
{

/// @addtogroup Resources
/// @{

/// @brief Namespace for resource-specific functionality
/// @details Contains resource-related functionality that is a bit more specific than ResourceManager and ResourcePtr.
namespace Resources
{

	/// @brief Predefined key class for sf::Image resources
	/// @details You can use this class to specifiy the access and loading of sf::Image resources in a ResourceManager.
	class THOR_API ImageKey
	{
		// ---------------------------------------------------------------------------------------------------------------------------
		// Public member functions
		public:
			/// @brief Load sf::Image from size and fill color
			/// @param width,height The size of the image.
			/// @param fillColor The color used to fill the image.
			/// @param tag If an existing key has the same loading parameters, you can use this ID to create a distinct key.
			/// @see sf::Image::Create()
			static ImageKey				FromSize(unsigned int width, unsigned int height, const sf::Color& fillColor = sf::Color(0, 0, 0),
											const std::string& tag = "");

			/// @brief Load sf::Image from file name
			/// @param fileName The name of the file from which you want to load the sf::Image.
			/// @param tag If an existing key has the same loading parameters, you can use this ID to create a distinct key.
			/// @see sf::Image::LoadFromFile()
			static ImageKey				FromFile(const std::string& fileName, const std::string& tag = "");

			/// @brief Load sf::Image from file in memory
			/// @param data Pointer to the file data in memory.
			/// @param size Size of the data to load, in bytes. 
			/// @param tag If an existing key has the same loading parameters, you can use this ID to create a distinct key.
			/// @see sf::Image::LoadFromMemory()
			static ImageKey				FromMemory(const void* data, std::size_t size, const std::string& tag = "");

			/// @brief Load sf::Image from array of pixels
			/// @param width,height The size of the image.
			/// @param pixels Pointer to the pixels in memory.
			/// @param tag If an existing key has the same loading parameters, you can use this ID to create a distinct key.
			/// @see sf::Image::LoadFromPixels()
			static ImageKey				FromPixels(unsigned int width, unsigned int height, const sf::Uint8* pixels,
											const std::string& tag = "");

			/// @brief Loads the image as specified by the static functions.
			/// @return Movable smart pointer to the allocated sf::Image, or null pointer at loading failure.
			MovedPtr<sf::Image>			Load() const;

			/// @brief Exchanges the contents of @a *this with @a other.
			///
			void						Swap(ImageKey& other);


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private member functions
		private:
			// Make default constructor private
										ImageKey();

		
		// ---------------------------------------------------------------------------------------------------------------------------
		// Private variables
		private:
			std::tr1::function<bool(sf::Image&)>	mLoader;
			std::string								mKey;

	
		// ---------------------------------------------------------------------------------------------------------------------------
		// Friends
		friend struct detail::KeyInfoAccessor<true>;
	};


	/// @brief Predefined key class for sf::Font resources
	/// @details You can use this class to specifiy the access and loading of sf::Font resources in a ResourceManager.
	class THOR_API FontKey
	{
		// ---------------------------------------------------------------------------------------------------------------------------
		// Public member functions
		public:
			/// @brief Load sf::Font from file name
			/// @param fileName The name of the file from which you want to load the sf::Font.
			/// @param tag If an existing key has the same loading parameters, you can use this ID to create a distinct key.
			/// @see sf::Font::LoadFromFile()
			static FontKey				FromFile(const std::string& fileName, const std::string& tag = "");

			/// @brief Load sf::Font from file in memory
			/// @param data Pointer to the file data in memory.
			/// @param size Size of the data to load, in bytes. 
			/// @param tag If an existing key has the same loading parameters, you can use this ID to create a distinct key.
			/// @see sf::Font::LoadFromMemory()
			static FontKey				FromMemory(const void* data, std::size_t size, const std::string& tag = "");

			/// @brief Loads the font as specified by the static functions.
			/// @details This function is mainly provided for ResourceManager, you don't need to call it directly.
			/// @return Movable smart pointer to the allocated sf::Font, or null pointer at loading failure.
			MovedPtr<sf::Font>			Load() const;

			/// @brief Exchanges the contents of @a *this with @a other.
			///
			void						Swap(FontKey& other);


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private member functions
		private:
			// Make default constructor private
										FontKey();

		
		// ---------------------------------------------------------------------------------------------------------------------------
		// Private variables
		private:
			std::tr1::function<bool(sf::Font&)>		mLoader;
			std::string								mKey;

	
		// ---------------------------------------------------------------------------------------------------------------------------
		// Friends
		friend struct detail::KeyInfoAccessor<true>;
	};


	/// @brief Predefined key class for sf::Shader resources
	/// @details You can use this class to specifiy the access and loading of sf::Shader resources in a ResourceManager.
	class THOR_API ShaderKey
	{
		// ---------------------------------------------------------------------------------------------------------------------------
		// Public member functions
		public:
			/// @brief Load sf::Shader from file name
			/// @param fileName The name of the file from which you want to load the sf::Shader.
			/// @param tag If an existing key has the same loading parameters, you can use this ID to create a distinct key.
			/// @see sf::Shader::LoadFromFile()
			static ShaderKey			FromFile(const std::string& fileName, const std::string& tag = "");

			/// @brief Load sf::Shader from source code in memory
			/// @param shaderCode String containing the source code of the shader.
			/// @param tag If an existing key has the same loading parameters, you can use this ID to create a distinct key.
			/// @see sf::Shader::LoadFromMemory()
			static ShaderKey			FromMemory(const std::string& shaderCode, const std::string& tag = "");

			/// @brief Loads the shader as specified by the static functions.
			/// @return Movable smart pointer to the allocated sf::Shader, or null pointer at loading failure.
			MovedPtr<sf::Shader>		Load() const;

			/// @brief Exchanges the contents of @a *this with @a other.
			///
			void						Swap(ShaderKey& other);


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private member functions
		private:
			// Make default constructor private
										ShaderKey();

		
		// ---------------------------------------------------------------------------------------------------------------------------
		// Private variables
		private:
			std::tr1::function<bool(sf::Shader&)>	mLoader;
			std::string								mKey;

	
		// ---------------------------------------------------------------------------------------------------------------------------
		// Friends
		friend struct detail::KeyInfoAccessor<true>;
	};


	/// @relates ImageKey 
	/// @brief Comparison operator for strict weak ordering
	bool THOR_API				operator< (const ImageKey& lhs, const ImageKey& rhs);
	
	/// @relates FontKey 
	/// @brief Comparison operator for strict weak ordering
	bool THOR_API				operator< (const FontKey& lhs, const FontKey& rhs);

	/// @relates ShaderKey 
	/// @brief Comparison operator for strict weak ordering
	bool THOR_API				operator< (const ShaderKey& lhs, const ShaderKey& rhs);


	/// @relates ImageKey 
	/// @brief Swaps two sf::Image resource keys.
	THOR_GLOBAL_SWAP(ImageKey)

	/// @relates FontKey
	/// @brief Swaps two sf::Font resource keys.
	THOR_GLOBAL_SWAP(FontKey)

	/// @relates ShaderKey 
	/// @brief Swaps two sf::Shader resource keys.
	THOR_GLOBAL_SWAP(ShaderKey)

} // namespace Resources

/// @}

} // namespace thor

#endif // THOR_GRAPHICSKEYS_HPP
