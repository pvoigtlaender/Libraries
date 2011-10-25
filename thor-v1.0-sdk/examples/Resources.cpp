
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	// Create image and sound manager
	thor::ResourceManager<sf::Image> imageMgr;
	thor::ResourceManager<sf::SoundBuffer> soundMgr;

	// Import names for simplicity
	using thor::Resources::ImageKey;
	using thor::Resources::SoundBufferKey;

	// Create keys to load resources
	ImageKey imageKey1      = ImageKey::FromSize(529, 100, sf::Color(130, 70, 0));
	ImageKey imageKey2      = ImageKey::FromFile("Media/image.jpg");
	SoundBufferKey soundKey = SoundBufferKey::FromFile("Media/click.wav");

	// Create resource pointers to access the resources
	thor::ResourcePtr<sf::Image>       image1, image2;
	thor::ResourcePtr<sf::SoundBuffer> soundBuffer;

	// Actually load resources, store them in resource pointers and react to loading errors
	try
	{
		image1      = imageMgr.Acquire(imageKey1);
		image2      = imageMgr.Acquire(imageKey2);
		soundBuffer = soundMgr.Acquire(soundKey);
	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	// Create instances that use the resources
	sf::Sprite sprite1(*image1);
	sf::Sprite sprite2(*image2);
	sf::Sound  sound(*soundBuffer);

	// Move second sprite so that the sprites don't overlap
	sprite2.Move( 0.f, static_cast<float>(image1->GetHeight()) );

	// Create instruction text
	sf::Text instructions("Press return to play sound, escape to quit");
	instructions.SetCharacterSize(12);

	// Create render window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Thor Resources");
	window.EnableVerticalSync(true);

	for (;;)
	{
		// Handle events
		sf::Event event;
		while (window.PollEvent(event))
		{
			if (event.Type == sf::Event::Closed)
			{
				return 0;
			}
			else if (event.Type == sf::Event::KeyPressed)
			{
				switch (event.Key.Code)
				{
					case sf::Key::Escape:
						return 0;

					case sf::Key::Return:
						sound.Play();
						break;
				}
			}
		}

		// Draw sprites of the loaded images
		window.Clear();
		window.Draw(sprite1);
		window.Draw(sprite2);
		window.Draw(instructions);
		window.Display();
	}
}