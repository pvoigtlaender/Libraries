
#include <Thor/Events.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Import namespaces for simplicity
using namespace std::tr1::placeholders;
namespace tr1 = std::tr1;

// Displays the ASCII character of pressed key
void WriteKey(sf::Event event)
{
	std::cout << "Text entered: ";
    std::cout << static_cast<char>(event.Text.Unicode) << std::endl;
}

// Moves the shape to the position where the mouse was clicked
void ReadMousePosition(sf::Event event, sf::Shape* shape)
{
	float x = static_cast<float>(event.MouseButton.X);
	float y = static_cast<float>(event.MouseButton.Y);

	shape->SetPosition(x, y);
}

// Closes the window upon request
struct WindowCloser
{
	explicit WindowCloser(sf::Window& window)
	: window(window)
	{
	}

	void operator() (sf::Event)
	{
		window.Close();
	}

	sf::Window& window;
};

int main()
{
	// Initialize window and a shape that tells us where we clicked last
	sf::RenderWindow window(sf::VideoMode(300, 200), "Thor Events");
	sf::Shape shape = sf::Shape::Circle(0.f, 0.f, 7.f, sf::Color::Magenta);

	// Create event system and connect different functions to different event types
	// First we use a function pointer, then two functors: WindowCloser and the result of tr1::bind()
	thor::SfmlEventSystem system(window);
	system.Connect(sf::Event::TextEntered,        &WriteKey);
	system.Connect(sf::Event::Closed,             WindowCloser(window));
	system.Connect(sf::Event::MouseButtonPressed, tr1::bind(&ReadMousePosition, _1, &shape));

	// Main loop
	while (window.IsOpened())
	{
		// Handle SFML events
		system.PollEvents();

		// Draw window
		window.Clear();
		window.Draw(shape);
		window.Display();
	}
}