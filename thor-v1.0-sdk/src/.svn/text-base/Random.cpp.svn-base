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

#include <Thor/Math/Random.hpp>

#include <SFML/Config.hpp>

#include THOR_TR1_HEADER(random)
#include <ctime>
#include <cassert>
#include <climits>


namespace thor
{
namespace
{

#ifdef THOR_USE_TR1_RANDOMENGINE

	// Note: Don't use std::tr1::variate_generator, because it contains bugs.
	// If the distribution type is not unsigned long (like the engine's number type), a cast is performed,
	// truncating values and leading to completely wrong random numbers.

	// Use Mersenne Twister as default TR1 random engine
	typedef std::tr1::mt19937 Engine;

#else

	// 64 Bit type
	#if ULONG_MAX == 0xffffffffffffffff
		typedef unsigned long Uint64;
	#elif ULLONG_MAX == 0xffffffffffffffff
		// unsigned long long is non-standard, but supported by many compilers, especially by those who support TR1.
		// I would use <cstdint>, but its availability is likely to be even worse than unsigned long long's one.
		// In case this type is not available on your platform, you can still define THOR_USE_TR1_RANDOMENGINE when compiling Thor.
		typedef unsigned long long Uint64;
	#else 
		#error No 64 bits integer type for this platform
	#endif

	// 32 Bit type, take from SFML
	typedef sf::Uint32 Uint32;


	// Random generator engine (Multiply With Carry)
	// Thanks to Volkard Henkel for the implementation.
	class Engine
	{
		public:
			// Type definition for usage inside TR1.Random
			typedef Uint32 result_type;


		public:
			// Constructor
			explicit Engine(Uint32 seedVal)
			{
				seed(seedVal);
			}
	
			// Return random number
			Uint32 operator() ()
			{
				const Uint64 a = 1967773755;

				x = a * (x & 0xffffffff) + (x >> 32);
				return static_cast<Uint32>(x);
			}

			// Set seed (compliant to TR1.Random)
			void seed(Uint32 seedVal = 0)
			{
				x = seedVal + !seedVal;
			}

			// Return minimal value (compliant to TR1.Random)
			Uint32 min() const
			{
				return 0;
			}

			// Return maximal value (compliant to TR1.Random)
			Uint32 max() const
			{
				return 0xffffffff;
			}

		private:
			Uint64 x;
	};

#endif // THOR_USE_TR1_RANDOMENGINE

	// Function initializing the engine and its seed at startup time
	Engine CreateInitialEngine()
	{
		return Engine( static_cast<unsigned long>(std::time(NULL)) );
	}

	// Pseudo random number generator engine
	Engine globalEngine = CreateInitialEngine();


	// Uniform real distribution for type float
	// Self-implemented, because std::tr1::uniform_real<float> is buggy on g++
	class UniformFloat
	{
		public:
			// Constructor
			UniformFloat(float min, float max)
			: mMin(min)
			, mMax(max)
			{
				assert(min <= max);
			}

			// Create uniform distribution from engine
			template <class Engine>
			float operator() (Engine& e)
			{
				// Scale to [0.f, 1.f]
				const float unit = static_cast<float>(e() - e.min()) / static_cast<float>(e.max() - e.min());

				// Scale to [mMin, mMax]
				return (mMax - mMin) * unit + mMin;
			}

		private:
			float mMin;
			float mMax;
	};

} // namespace

// ---------------------------------------------------------------------------------------------------------------------------


int Random(int begin, int end)
{
	assert(begin <= end);
	std::tr1::uniform_int<int> distribution(begin, end);
	return distribution(globalEngine);
}

int RandomDev(int middle, int deviation)
{
	assert(deviation >= 0);
	return Random(middle-deviation, middle+deviation);
}

float Random(float begin, float end)
{
	assert(begin <= end);
	UniformFloat distribution(begin, end);
	return distribution(globalEngine);
}

float RandomDev(float middle, float deviation)
{
	assert(deviation >= 0.f);
	return Random(middle-deviation, middle+deviation);
}

void SetRandomSeed(unsigned long seed)
{
	globalEngine.seed(seed);
}

} // namespace thor
