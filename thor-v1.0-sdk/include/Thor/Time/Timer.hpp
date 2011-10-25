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
/// @brief Class thor::Timer

#ifndef THOR_TIMER_HPP
#define THOR_TIMER_HPP

#include <Thor/Time/StopWatch.hpp>
#include <Thor/Config.hpp>


namespace thor
{

/// @addtogroup Time
/// @{

/// @brief Clock class that has the semantics of a timer.
/// @details You can initialize an instance with a time limit and it will automatically count
///  down, until the time reaches zero.
class THOR_API Timer
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Default constructor: Creates a timer that is initially expired.
		/// @details You have to call Reset() before you can use the countdown functionality.
									Timer();

		/// @brief Virtual destructor
		///
		virtual						~Timer();
	
		/// @brief Constructor: Sets up a new timer with the given time limit.
		/// @param timeLimit The initial time (must be greater than zero).
		/// @param initiallyRunning Indicates whether the timer is immediately being started.
		explicit					Timer(float timeLimit, bool initiallyRunning = false);
		
		/// @brief Returns the remaining time.
		/// @details If the timer has expired, 0.f is returned.
		float						GetRemainingTime() const;
		
		/// @brief Checks if the timer is currently running.
		/// @details As soon as the timer expires, it stops running until Reset() is called.
		bool						IsRunning() const;
		
		/// @brief Checks if the timer has expired yet.
		/// @details Timers expire when their remaining time reaches zero.
		bool						IsExpired() const;
		
		/// @brief Starts or continues the timer.
		/// @details If it is already running, nothing happens.
		void						Start();
		
		/// @brief Pauses the timer.
		/// @details If it is already paused, nothing happens.
		void						Stop();
		
		/// @brief Resets the timer's countdown to the given time limit.
		/// @param timeLimit The new time (must be greater than zero).
		/// @param continueRunning Indicates whether the timer directly continues.
		virtual void				Reset(float timeLimit, bool continueRunning = false);
		

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		StopWatch					mStopWatch;
		float						mLimit;
};

/// @}

} // namespace thor

#endif // THOR_TIMER_HPP
