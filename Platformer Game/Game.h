#pragma once
//#include "SFML/Graphics.hpp"
#include "PhysicsGameObject.h"
#include "TextGameObject.h"
#include "Player.h"
#include <vector>
#include "SpriteBatch.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary> Game logic happens in here, should be called every frame </summary>
	/// <param name="deltaTime"> Time since last frame </param>
	void update(const float deltaTime);
	// Draw things on screen, should be called every frame
	void render(DirectX::SpriteBatch& spriteBatch);
private:
	Player mPlayer;
	std::vector<PhysicsGameObject> mTerrain;
	//sf::Texture mPlayerIdleTexture;
	//sf::Texture mWallTexture;
	// **DEBUG
	//TextGameObject mDebugText;
	//sf::Font mDebugFont;
};

