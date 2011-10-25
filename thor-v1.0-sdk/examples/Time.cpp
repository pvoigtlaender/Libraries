
#include <Thor/Time.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

// Converts a float to a string with two decimal places
std::string ToString(float value)
{
	std::stringstream stream;
	stream.setf(std::ios_base::fixed);
	stream.precision(2);
	stream << value;
	return stream.str();
}

int main() 
{
	// Create SFML window
	sf::RenderWindow window(sf::VideoMode(300, 200), "Thor Time", sf::Style::Close);
	window.EnableVerticalSync(true);

	// Create stopwatch and timer
	const float initialTime = 4.f;
	thor::StopWatch stopWatch;
	thor::TriggeringTimer timer(initialTime);

	// Create texts that display instructions and current time
	sf::Text instructions(
		"S      Start/pause stopwatch\n"
		"T      Start/pause timer\n"
		"R      Reset stopwatch and timer\n"
		"Esc  Quit");
	instructions.SetCharacterSize(12);

	sf::Text stopWatchMeasurement;
	stopWatchMeasurement.SetCharacterSize(20);
	stopWatchMeasurement.SetPosition(70.f, 120.f);
	stopWatchMeasurement.SetColor(sf::Color(0, 190, 140));
	
	sf::Text timerMeasurement;
	timerMeasurement.SetCharacterSize(20);
	timerMeasurement.SetPosition(70.f, 150.f);
	timerMeasurement.SetColor(sf::Color(0, 140, 190));
	
	// Connect timer with callback (colorize yellow) invoked at expiration time
	timer.Connect(std::tr1::bind(&sf::Text::SetColor, &timerMeasurement, sf::Color::Yellow));

	// Main loop
	while (window.IsOpened())
	{
		// Event handling
		sf::Event event;
		while (window.PollEvent(event))
		{
			// [X]: Quit
			if (event.Type == sf::Event::Closed)
			{
				return 0;
			}

			// Key pressed
			else if (event.Type == sf::Event::KeyPressed)
			{
				switch (event.Key.Code)
				{
					// Esc: Quit
					case sf::Key::Escape:
						return 0;

					// S: Start/pause stopwatch
					case sf::Key::S:
						if (stopWatch.IsRunning())
							stopWatch.Stop();
						else
							stopWatch.Start();
						break;

					// T: Start/pause timer
					case sf::Key::T:
						if (timer.IsRunning())
							timer.Stop();
						else
							timer.Start();
						break;

					// R: Reset both stopwatch and timer
					case sf::Key::R:
						stopWatch.Reset();
						timer.Reset(initialTime);
						timerMeasurement.SetColor(sf::Color(0, 140, 190));
						break;
				}
			}
		}

		// Adapt texts for stopwatch and timer according to elapsed/remaining time
		stopWatchMeasurement.SetString("Stopwatch:  " + ToString(stopWatch.GetElapsedTime()));
		timerMeasurement.SetString("Timer:  " + ToString(timer.GetRemainingTime()));

		// Update TriggeringTimer that allows the callback to be invoked
		timer.Update();

		// Draw everything
		window.Clear();
		window.Draw(instructions);
		window.Draw(stopWatchMeasurement);
		window.Draw(timerMeasurement);
		window.Display();
	}	
}