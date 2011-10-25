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
/// @brief Definition of Thor exception classes

#ifndef THOR_EXCEPTIONS_HPP
#define THOR_EXCEPTIONS_HPP

#include <Thor/Config.hpp>

#include <stdexcept>
#include <string>


namespace thor
{

/// @addtogroup Tools
/// @{

// MSVC: Disable DLL warning because we derive from std::runtime_error
#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable: 4275)
#endif

/// @brief %Exception base class.
/// @details All exceptions thrown by the Thor Library are derived from this class. Exception inherits from
///  std::runtime_error, hence all Thor exceptions contain a (here undocumented) virtual function what().
class THOR_API Exception : public std::runtime_error
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Constructor
		/// @param message The exception message (how the error occurred).
		explicit					Exception(const std::string& message);
};


/// @brief %Exception class for failed function calls.
/// @details Is used inside thor::SingleDispatcher and thor::DoubleDispatcher.
class THOR_API FunctionCallException : public Exception
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Constructor
		/// @param message The exception message (how the error occurred).
		explicit					FunctionCallException(const std::string& message);
};


/// @brief %Exception class for failed resource allocation.
/// @details Is thrown by thor::ResourceManager in case of resources that couldn't be loaded.
class THOR_API ResourceLoadingException : public Exception
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Constructor
		/// @param message The exception message (how the error occurred).
		explicit					ResourceLoadingException(const std::string& message);
};

#ifdef _MSC_VER
	#pragma warning(pop)
#endif

/// @}

} // namespace thor

#endif // THOR_EXCEPTIONS_HPP
