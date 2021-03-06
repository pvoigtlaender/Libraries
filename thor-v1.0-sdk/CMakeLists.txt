#################################################################################
##
## Thor C++ Library
## Copyright (c) 2011 Jan Haller
## 
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the authors be held liable for any damages
## arising from the use of this software.
## 
## Permission is granted to anyone to use this software for any purpose,
## including commercial applications, and to alter it and redistribute it
## freely, subject to the following restrictions:
## 
## 1. The origin of this software must not be misrepresented; you must not
##    claim that you wrote the original software. If you use this software
##    in a product, an acknowledgment in the product documentation would be
##    appreciated but is not required.
## 
## 2. Altered source versions must be plainly marked as such, and must not be
##    misrepresented as being the original software.
## 
## 3. This notice may not be removed or altered from any source distribution.
##
#################################################################################

# Directory Thor


cmake_minimum_required(VERSION 2.8)

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

project(thor)


# Global preprocessor and include options
add_definitions(-DTHOR_EXPORTS)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Predefined configuration options
set(THOR_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries")
set(THOR_BUILD_EXAMPLES FALSE CACHE BOOL "Build example projects")

# Variable for install directory
if(UNIX)
	set(THOR_MISC_INSTALL_DIR share/Thor)
else()
	set(THOR_MISC_INSTALL_DIR .)
endif()


# Find SFML
if(NOT THOR_SHARED_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2 COMPONENTS system window graphics audio)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFMLDIR "" CACHE PATH "SFML top-level directory")
	message(FATAL_ERROR "SFML directory not found. Set SFMLDIR to SFML's top-level path (containing \"include\" and \"lib\" directories).")
endif()


# Find OpenGL
find_package(OpenGL REQUIRED)
message(STATUS "SFML and OpenGL found.")


# Macro for easy linkage of SFML and OpenGL
macro(thor_link_sfml_opengl THOR_TARGET)
	target_link_libraries(${THOR_TARGET} ${SFML_LIBRARIES})
	target_link_libraries(${THOR_TARGET} ${OPENGL_gl_LIBRARY})
endmacro()


# Macro for easy linkage of Thor (for examples)
macro(thor_link_thor THOR_TARGET)
	target_link_libraries(${THOR_TARGET} thor)
	if(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
		set_target_properties(${THOR_TARGET} PROPERTIES LINK_FLAGS "-static-libgcc")
	endif()
endmacro()


# C++ source code
add_subdirectory(src)

if(THOR_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()


# Install include directory and license file
install(DIRECTORY include
		DESTINATION .
		REGEX "\\.svn|_svn" EXCLUDE)

install(FILES license.txt
		DESTINATION ${THOR_MISC_INSTALL_DIR})
