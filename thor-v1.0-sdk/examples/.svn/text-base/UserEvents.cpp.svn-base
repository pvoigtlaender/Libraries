
#include <Thor/Events/EventSystem.hpp>
#include <iostream>
#include <string>

// Enumeration for unit orders in a strategy game
namespace Command
{
	enum Type
	{
		Move,
		Attack,
		HoldPosition,
	};
}

// A user-defined event class, contains the name and command of a strategy game unit
struct UnitEvent
{
	UnitEvent(const char* unitName, Command::Type order)
	: unitName(unitName)
	, order(order)
	{
	}

	const char* unitName;
	Command::Type order;
};

// Function that returns the corresponding EventIdentifier to an Event
Command::Type ExtractEventIdentifier(const UnitEvent& event)
{
	return event.order;
}

// Callback for Command::Move
void OnMove(const UnitEvent& event)
{
	std::cout << "Unit " << event.unitName << " moves." << std::endl;
}

// Callback for Command::Attack
void OnAttack(const UnitEvent& event)
{
	std::cout << "Unit " << event.unitName << " attacks." << std::endl;
}

// Callback for Command::HoldPosition
void OnHoldPosition(const UnitEvent& event)
{
	std::cout << "Unit " << event.unitName << " holds its position." << std::endl;
}

int main()
{
	// Create event system with template parameters for Event and EventIdentifier
	thor::EventSystem<UnitEvent, Command::Type> system;

	// Connect event identifiers to the listeners
	system.Connect(Command::Move,         &OnMove);
	system.Connect(Command::Attack,       &OnAttack);
	system.Connect(Command::HoldPosition, &OnHoldPosition);

	// Create some events and fire them
	system.TriggerEvent( UnitEvent("Tank",       Command::Attack) );
	system.TriggerEvent( UnitEvent("Helicopter", Command::Move) );
	system.TriggerEvent( UnitEvent("Battleship", Command::Attack) );
	system.TriggerEvent( UnitEvent("Battleship", Command::HoldPosition) );
}
