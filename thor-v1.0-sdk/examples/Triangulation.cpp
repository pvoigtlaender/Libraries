
#include <Thor/Math/Triangulation.hpp>
#include <Thor/Tools/ForEach.hpp>
#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <SFML/Graphics.hpp>
#include <iterator>

// Typedefs for simplicity. Instead of thor::Vertex, you may also use a class derived from
// thor::Vertex to store more information than just the position. Just replace the types.
typedef std::vector<thor::Vertex>					VertexContainer;
typedef std::vector<thor::Triangle<thor::Vertex> >	TriangleContainer;

// Declarations of functions
VertexContainer::const_iterator FindVertex(const VertexContainer& vertices, sf::Vector2f position);
bool VertexClick(sf::Event::MouseButtonEvent mouseEvent, VertexContainer& vertices);
bool HandleEvents(sf::RenderWindow& window, VertexContainer& vertices, TriangleContainer& triangles);

int main()
{
	// Create render window
	sf::RenderWindow window(sf::VideoMode(640, 480), "Thor Triangulation");
	window.SetFramerateLimit(20);

	// Create containers in which we store the vertices and the computed triangles
	VertexContainer		vertices;
	TriangleContainer	triangles;

	// Description with instructions
	sf::Text instructions(
		"Left click to add point\n"
		"Right click to remove point\n"
		"C key to clear everything");
	instructions.SetCharacterSize(12);
		
	// Main loop
	for (;;)
	{
		// Event handling, possible quit
		if (!HandleEvents(window, vertices, triangles))
			return 0;
	
		// Clear background
		window.Clear();
		
		// Draw all triangles
		THOR_CONST_FOREACH(TriangleContainer, triangles, itr)
		{
			sf::Shape triangle;
			
			for (unsigned int i = 0; i < 3; ++i)
				triangle.AddPoint((*itr)[i].GetPosition(), sf::Color(0,150,255,100), sf::Color::Blue);
			
			triangle.SetOutlineThickness(1.f);
			window.Draw(triangle);
		}
		
		// Draw all points
		THOR_CONST_FOREACH(VertexContainer, vertices, itr)
		{
			sf::Shape circle = sf::Shape::Circle(itr->GetPosition(), 6.f, sf::Color(255, 0, 150));
			window.Draw(circle);
		}
		
		// Draw description
		window.Draw(instructions);
		
		// Update screen
		window.Display();
	}
}

// Finds out whether a vertex is near a given position.
VertexContainer::iterator FindVertex(VertexContainer& vertices, sf::Vector2f position)
{
	// Find out which point was clicked on (tolerance radius is 6 pixels, as big as the circle's radius)
	THOR_FOREACH(VertexContainer, vertices, itr)
	{
		if (thor::SquaredLength(position - itr->GetPosition()) <= 36.f)
			return itr;
	}
	
	return vertices.end();
}

// Handles clicks on a vertex. Returns true if a new triangulation is required.
bool VertexClick(sf::Event::MouseButtonEvent mouseEvent, VertexContainer& vertices)
{
	sf::Vector2f clickPos(static_cast<float>(mouseEvent.X), static_cast<float>(mouseEvent.Y));
	
	// Add point when left-clicking
	if (mouseEvent.Button == sf::Mouse::Left)
	{
		// Don't insert the same point twice
		THOR_CONST_FOREACH(VertexContainer, vertices, itr)
		{
			if (itr->GetPosition() == clickPos)
				return false;
		}
		
		// If not contained yet, insert point
		vertices.push_back(thor::Vertex(clickPos));
		return true;
	}
	
	// Remove point when right-clicking
	else if (mouseEvent.Button == sf::Mouse::Right)
	{
		VertexContainer::iterator vertexItr = FindVertex(vertices, clickPos);
		if (vertexItr != vertices.end())
		{
			vertices.erase(vertexItr);
			return true;
		}
	}
	
	return false;
}

// Handles SFML events. Returns false if the application should be quit.
bool HandleEvents(sf::RenderWindow& window, VertexContainer& vertices, TriangleContainer& triangles)
{
	sf::Event event;
	while (window.PollEvent(event))
	{
		switch (event.Type)
		{
			// Mouse buttons: Add or remove vertex
			case sf::Event::MouseButtonPressed:
				{
					// Compute new triangulation for points if necessary
					if (VertexClick(event.MouseButton, vertices))
					{
						triangles.clear();
						thor::Triangulate(vertices.begin(), vertices.end(), std::back_inserter(triangles));
					}
				} break;

			// Keys (C -> Clear, Escape -> Quit)
			case sf::Event::KeyPressed:
				{
					switch (event.Key.Code)
					{
						case sf::Key::Escape:
							return false;

						case sf::Key::C:
							vertices.clear();
							triangles.clear();
					}
				} break;

			// [X] clicked
			case sf::Event::Closed:
				return false;
		}
	}

	return true;
}
