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
/// @brief Class template thor::SfmlEventSystem

#ifndef THOR_SFMLEVENTSYSTEM_HPP
#define THOR_SFMLEVENTSYSTEM_HPP

#include <Thor/Events/EventSystem.hpp>
#include <Thor/Config.hpp>

#include <SFML/Window/Event.hpp>


namespace sf
{

	class Window;

} // namespace sf


namespace thor
{
namespace detail
{
	// Function that extracts the event type of an sf::Event
	// The namespace thor::detail is imported at the call, so this function participates in overload resolution.
	inline sf::Event::EventType ExtractEventIdentifier(const sf::Event& event)
	{
		return event.Type;
	}
}

// ---------------------------------------------------------------------------------------------------------------------------


/// @addtogroup Events
/// @{
	
/// @brief Class for object-oriented handling of SFML events.
/// @details Polls events of a window and forwards them to specific event listeners.
class THOR_API SfmlEventSystem : public EventSystem<sf::Event, sf::Event::EventType>
{	
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Constructor
		/// @param window The window from which events are going to be polled.
		explicit					SfmlEventSystem(sf::Window& window);
		
		/// @brief Polls events from the window and calls appropriate listeners.
		///
		void						PollEvents();

		/// @brief Forwards all events to a specific receiver.
		/// @details This invokes the receiver function object for every event in the queue of the sf::Window (not just
		///  events of a given type). That can be useful for things like GUI hierarchies depending on events, too.
		/// @param receiver Function object that is called upon events.
		/// @return Connection allowing to remove this receiver from the forwarded events.
		Connection					ForwardEvents(const Listener& receiver);				
		
		/// @brief Removes all connections of events that are forwarded.
		/// @details Disconnects all event connections that have been set up with ForwardEvents().
		void						ClearEventForwarders();
	

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:
		// Container type
		typedef detail::ListenerSequence<const sf::Event&>		EventForwarderCtr;

		
	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		sf::Window&					mWindow;
		EventForwarderCtr			mForwarders;
};

/// @}

} // namespace thor

#endif // THOR_SFMLEVENTSYSTEM_HPP
