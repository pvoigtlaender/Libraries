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
/// @brief Class template thor::TrigonometricTraits and some trigonometry-related functions and constants.

#ifndef THOR_TRIGONOMETRY_HPP
#define THOR_TRIGONOMETRY_HPP

#include <cmath>


namespace thor
{

/// @addtogroup Math
/// @{

/// @struct thor::TrigonometricTraits
/// @brief Trigonometric traits template
/// @details This template can be specialized in order to implement trigonometric constants and functions
///  for arbitrary types. Some of the definitions are required by the vector algebra functions. @n@n
/// To define your own traits, specialize the template inside namespace @a thor. The full specialization
/// shall contain the following public static methods. You don't have to define all of them, depending on
/// the functionality you need. For example, computing the vector length requires Sqrt(), and for
/// angle-related functionality, you need ArcTan2(). @n
/// @arg T Sin(T deg)
///	@arg T Cos(T deg)
///	@arg T Tan(T deg)
///	@arg T ArcSin(T value)
///	@arg T ArcCos(T value)
///	@arg T ArcTan2(T valY, T valX)
///	@arg T Sqrt(T value)
///	@arg T %Pi()
///	@arg T RadToDeg(T rad)
///	@arg T DegToRad(T deg)
///
/// @attention All trigonometric functions take and return degrees, @b NOT radians.
template <typename T>
struct TrigonometricTraits;

/// @brief Trigonometric traits: Specialization for float
///
template <>
struct TrigonometricTraits<float>
{
	typedef float Type;

	static Type Sin(Type deg)					{ return std::sin(DegToRad(deg));			}
	static Type Cos(Type deg)					{ return std::cos(DegToRad(deg));			}
	static Type Tan(Type deg)					{ return std::tan(DegToRad(deg));			}
	static Type ArcSin(Type value)				{ return RadToDeg(std::asin(value));		}
	static Type ArcCos(Type value)				{ return RadToDeg(std::acos(value));		}
	static Type ArcTan2(Type valY, Type valX)	{ return RadToDeg(std::atan2(valY, valX));	}
	static Type Sqrt(Type value)				{ return std::sqrt(value);					}
	
	static Type Pi()							{ return 3.14159265f;						}
	static Type RadToDeg(Type rad)				{ return 180 / 3.14159265f * rad;			}
	static Type DegToRad(Type deg)				{ return 3.14159265f / 180 * deg;			}
};

/// @brief Trigonometric traits: Specialization for double
///
template <>
struct TrigonometricTraits<double>
{
	typedef double Type;
	
	static Type Sin(Type deg)					{ return std::sin(DegToRad(deg));			}
	static Type Cos(Type deg)					{ return std::cos(DegToRad(deg));			}
	static Type Tan(Type deg)					{ return std::tan(DegToRad(deg));			}
	static Type ArcSin(Type value)				{ return RadToDeg(std::asin(value));		}
	static Type ArcCos(Type value)				{ return RadToDeg(std::acos(value));		}
	static Type ArcTan2(Type valY, Type valX)	{ return RadToDeg(std::atan2(valY, valX));	}
	static Type Sqrt(Type value)				{ return std::sqrt(value);					}
	
	static Type Pi()							{ return 3.14159265;						}
	static Type RadToDeg(Type rad)				{ return 180 / 3.14159265 * rad;			}
	static Type DegToRad(Type deg)				{ return 3.14159265 / 180 * deg;			}
};

/// @brief Trigonometric traits: Specialization for long double
///
template <>
struct TrigonometricTraits<long double>
{
	typedef long double Type;
	
	static Type Sin(Type deg)					{ return std::sin(DegToRad(deg));			}
	static Type Cos(Type deg)					{ return std::cos(DegToRad(deg));			}
	static Type Tan(Type deg)					{ return std::tan(DegToRad(deg));			}
	static Type ArcSin(Type value)				{ return RadToDeg(std::asin(value));		}
	static Type ArcCos(Type value)				{ return RadToDeg(std::acos(value));		}
	static Type ArcTan2(Type valY, Type valX)	{ return RadToDeg(std::atan2(valY, valX));	}
	static Type Sqrt(Type value)				{ return std::sqrt(value);					}
	
	static Type Pi()							{ return 3.14159265l;						}
	static Type RadToDeg(Type rad)				{ return 180 / 3.14159265l * rad;			}
	static Type DegToRad(Type deg)				{ return 3.14159265l / 180 * deg;			}
};

/// @brief Converts radians to degrees.
///
template <typename T>
T ToDegree(T radian)
{
	return TrigonometricTraits<T>::RadToDeg(radian);
}

/// @brief Converts degrees to radians.
///
template <typename T>
T ToRadian(T degree)
{
	return TrigonometricTraits<T>::DegToRad(degree);
}

/// @brief The number %Pi (3.1415...)
/// @details Pi has the same value as TrigonometricTraits<float>::Pi().
extern const float Pi;

/// @}

} // namespace thor

#endif // THOR_TRIGONOMETRY_HPP
