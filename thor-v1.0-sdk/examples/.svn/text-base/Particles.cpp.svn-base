
// Headers
#include <Thor/Particles.hpp>
#include <Thor/Geometry.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Thor Particles");
	
	// Load image and initialize sprite
	sf::Image image;
	if (!image.LoadFromFile("Media/particle.png"))
		return EXIT_FAILURE;
	
	// Create particle system, emitter and circular emission zone
	thor::ParticleSystem system(image);
	thor::DirectionalEmitter::Ptr emitter( new thor::DirectionalEmitter(50.f, 5.f) );
	thor::MovedPtr<thor::Zone> zone( new thor::Circle(sf::Vector2f(), 10.f) );

	emitter->SetEmissionAngle(10.f);
	emitter->SetEmissionZone(zone);
	system.AddEmitter(emitter);

	// Build color gradient (green -> teal -> blue)
	const thor::ColorGradient gradient = thor::CreateGradient
		(sf::Color(0, 150, 0))		(1)
		(sf::Color(0, 150, 100))	(1)
		(sf::Color(0, 0, 150));

	// Add particle affectors
	system.AddAffector( thor::ColorAffector::Create(gradient) );
	system.AddAffector( thor::FadeInAffector::Create(0.1f) );
	system.AddAffector( thor::FadeOutAffector::Create(0.1f) );
	system.AddAffector( thor::TorqueAffector::Create(100.f) );
	system.AddAffector( thor::ForceAffector::Create(sf::Vector2f(0.f, 100.f))  );

	// Attributes that influence emitter
	sf::Vector2f		position;
	thor::PolarVector2f velocity(200.f, -90.f);
	bool				paused = false;

	// Instruction text
	sf::Text instructions(
		"Left click: Enable/disable glow effect\n"
		"Right click: Pause\n"
		"Mouse wheel: Change direction\n");
	instructions.SetCharacterSize(12);

	// Main loop
	while (window.IsOpened())
	{
		// Handle events
		sf::Event event;
		while (window.PollEvent(event))
		{
			switch (event.Type)
			{
				// [X]: Quit
				case sf::Event::Closed:
					return 0;
					
				// Escape: Quit
				case sf::Event::KeyPressed:
					if (event.Key.Code == sf::Key::Escape)
						return 0;

				// Left mouse button: Enable/disable glow
				case sf::Event::MouseButtonPressed:
					if (event.MouseButton.Button == sf::Mouse::Left)
						system.SetGlowing(!system.IsGlowing());
					else if (event.MouseButton.Button == sf::Mouse::Right)
						paused = !paused;
					break;

				// Mouse wheel: Change emission direction
				case sf::Event::MouseWheelMoved:
					velocity.phi += 12.f * event.MouseWheel.Delta;
					break;
			}
		}
		
		// Get mouse position
		position.x = static_cast<float>( window.GetInput().GetMouseX() );
		position.y = static_cast<float>( window.GetInput().GetMouseY() );
		
		// Update particle system and emitter
		if (!paused)
			system.Update(window.GetFrameTime());
		emitter->GetEmissionZone().SetPosition(position);
		emitter->SetParticleVelocity(velocity);

		// Draw everything
		window.Clear(sf::Color(30, 30, 30));
		window.Draw(instructions);
		system.Draw(window);
		window.Display();
	}
}
