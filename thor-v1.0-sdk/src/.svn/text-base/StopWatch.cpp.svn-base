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

#include <Thor/Time/StopWatch.hpp>


namespace thor
{

StopWatch::StopWatch(bool initiallyRunning)
: mClock()
, mTimeBuffer(0.f)
, mRunning(initiallyRunning)
{
}

float StopWatch::GetElapsedTime() const
{
	if (mRunning)
		return mTimeBuffer + mClock.GetElapsedTime();
	else
		return mTimeBuffer;
}

bool StopWatch::IsRunning() const
{
	return mRunning;
}

void StopWatch::Start()
{
	if (!mRunning)
	{
		mRunning = true;
		mClock.Reset();
	}		
}

void StopWatch::Stop()
{
	if (mRunning)
	{
		mRunning = false;
		mTimeBuffer += mClock.GetElapsedTime();
	}
}

void StopWatch::Reset(bool continueRunning)
{
	mTimeBuffer = 0.f;
	mRunning = continueRunning;
	mClock.Reset();
}

} // namespace thor
