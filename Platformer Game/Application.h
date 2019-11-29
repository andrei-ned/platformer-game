#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

// Boilerplate setup for handling the game
class Application
{
public:
	Application();
	~Application();
	void run();
private:
	Game mGame;
	sf::RenderWindow mWindow;
};

