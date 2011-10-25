
#include <Thor/Multimedia.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	// Create render window
	sf::RenderWindow window(sf::VideoMode(600, 500), "Thor Multimedia", sf::Style::Close);
	window.EnableVerticalSync(true);
	
	// Create a concave shape by directly inserting the polygon points
	thor::ConcaveShape concaveShape;
	concaveShape.AddPoint(50,  50,  sf::Color(0, 150, 0, 100),   sf::Color(0, 150, 0));
	concaveShape.AddPoint(100, 100, sf::Color(0, 100, 50, 100),  sf::Color(0, 100, 50));
	concaveShape.AddPoint(150, 50,  sf::Color(0, 50, 100, 100),  sf::Color(0, 50, 100));
	concaveShape.AddPoint(150, 200, sf::Color(255, 255, 0, 100), sf::Color(255, 255, 0));
	concaveShape.AddPoint(50,  150, sf::Color(255, 0, 0, 100),   sf::Color(255, 0, 0));
	concaveShape.SetOutlineThickness(5.f);
	
	// Create thor::ConcaveShape shape from sf::Shape
	thor::ConcaveShape circle = sf::Shape::Circle(100.f, 400.f, 60.f, sf::Color(0, 200, 0));	

	// Create a few predefined concave shapes
	thor::ConcaveShape pie     = thor::Shapes::Pie(sf::Vector2f(100.f, 400.f), 60.f, 135.f, sf::Color::Green);
	thor::ConcaveShape polygon = thor::Shapes::Polygon(5, sf::Vector2f(), 60.f, sf::Color(175, 40, 250));
	thor::ConcaveShape star    = thor::Shapes::Star(7, sf::Vector2f(), 40.f, 20.f, sf::Color(255, 225, 10), 5.f, sf::Color(250, 190, 20));
	
	// Move star and polygon shapes
	star.Move(500.f, 100.f);
	polygon.Move(500.f, 400.f);
	
	// Create an arrow pointing towards the mouse cursor
	thor::Arrow arrow(sf::Vector2f(window.GetWidth() / 2.f, window.GetHeight() / 2.f), sf::Vector2f(), sf::Color(0, 150, 200));
	
	// Main loop
	for (;;)
	{
		// Event handling
		sf::Event event;
		while (window.PollEvent(event))
		{
			switch (event.Type)
			{
				case sf::Event::Closed:
					return 0;
				case sf::Event::KeyPressed:
					return 0;
				case sf::Event::MouseMoved:
					arrow.SetDirection(event.MouseMove.X / 2.f - window.GetWidth() / 4.f, event.MouseMove.Y / 2.f - window.GetHeight() / 4.f);
					break;
			}
		}

		// Rotate polygon and star
		polygon.Rotate(-20.f * window.GetFrameTime());
		star.Rotate(45.f * window.GetFrameTime());
	
		// Draw everything
		window.Clear();
		window.Draw(concaveShape);
		window.Draw(circle);
		window.Draw(pie);
		window.Draw(polygon);
		window.Draw(star);
		window.Draw(arrow);
		window.Display();	
	}
}
