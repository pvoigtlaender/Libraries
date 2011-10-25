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

#include <Thor/Time/Timer.hpp>

#include <algorithm>
#include <cassert>


namespace thor
{

Timer::Timer()
: mStopWatch()
, mLimit(0.f)
{
}

Timer::Timer(float timeLimit, bool initiallyRunning)
: mStopWatch(initiallyRunning)
, mLimit(timeLimit)
{
	assert(timeLimit > 0.f);
}

Timer::~Timer()
{
}

float Timer::GetRemainingTime() const
{
	return std::max(mLimit - mStopWatch.GetElapsedTime(), 0.f);
}

bool Timer::IsRunning() const
{
	return mStopWatch.IsRunning() && !IsExpired();
}

bool Timer::IsExpired() const
{
	return mStopWatch.GetElapsedTime() >= mLimit;
}

void Timer::Start()
{
	mStopWatch.Start();
}

void Timer::Stop()
{
	mStopWatch.Stop();
}

void Timer::Reset(float timeLimit, bool continueRunning)
{
	assert(timeLimit > 0.f);

	mLimit = timeLimit;
	mStopWatch.Reset(continueRunning);
}

} // namespace thor
