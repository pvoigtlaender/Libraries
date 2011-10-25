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
/// @brief Contains macros that simplify the syntax of container iteration.

#ifndef THOR_FOREACH_HPP
#define THOR_FOREACH_HPP

/// @addtogroup Tools
/// @{

/// @brief Macro to iterate forward on a mutable sequence.
/// @hideinitializer
#define THOR_FOREACH(ContainerType, containerVar, iteratorVar)							\
	for (ContainerType::iterator iteratorVar = containerVar.begin(),					\
	thorForeachEnd = containerVar.end();												\
	iteratorVar != thorForeachEnd; ++iteratorVar)

/// @brief Macro to iterate forward on a constant sequence.
/// @hideinitializer
#define THOR_CONST_FOREACH(ContainerType, containerVar, iteratorVar)					\
	for (ContainerType::const_iterator iteratorVar = containerVar.begin(),				\
	thorForeachEnd = containerVar.end();												\
	iteratorVar != thorForeachEnd; ++iteratorVar)

/// @}

#endif // THOR_FOREACH_HPP
