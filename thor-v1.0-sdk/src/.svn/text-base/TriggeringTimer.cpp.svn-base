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

#include <Thor/Time/TriggeringTimer.hpp>


namespace thor
{

TriggeringTimer::TriggeringTimer()
: Timer()
, mListeners()
, mJustExpired(true) // Don't call listeners at beginning when default-constructed
{
}

TriggeringTimer::TriggeringTimer(float timeLimit, bool initiallyRunning)
: Timer(timeLimit, initiallyRunning)
, mListeners()
, mJustExpired(false) // When constructed with initial time limit, call listeners at expiration time
{
}

void TriggeringTimer::Reset(float timeLimit, bool continueRunning)
{
	Timer::Reset(timeLimit, continueRunning);

	mJustExpired = false;
}

void TriggeringTimer::Update()
{
	// When not flagged as "just expired" yet, do it now, and call listeners
	if (IsExpired() && !mJustExpired)
	{
		mJustExpired = true;
		mListeners.Call(*this);
	}
}

Connection TriggeringTimer::Connect(const Listener& listener)
{
	return mListeners.Add(listener);
}

void TriggeringTimer::ClearConnections()
{
	mListeners.Clear();
}

} // namespace thor
