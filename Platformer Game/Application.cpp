#include "Application.h"
#include "GameConstants.h"
#include "Constants.h"

Application::Application()
{
	mWindow.create(sf::VideoMode(GameConstants::SCREEN_RES_X, GameConstants::SCREEN_RES_Y), GameConstants::WINDOW_NAME);
}


Application::~Application()
{
}

void Application::run() {
	// Start the game loop 
	sf::Clock clock;
	while (mWindow.isOpen())
	{
		// Process events
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				mWindow.close();
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < Constants::ASCII_RANGE)
				{
					if (static_cast<char>(event.text.unicode) == Constants::ESCAPE_KEY)
						mWindow.close();
				}
			}
		}

		// Clear screen
		mWindow.clear();

		mGame.update(clock.restart());
		mGame.render(mWindow);

		// Update the window
		mWindow.display();
	}
}
