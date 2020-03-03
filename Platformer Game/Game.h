#pragma once
//#include "SFML/Graphics.hpp"
#include "PhysicsGameObject.h"
#include "TextGameObject.h"
#include "Player.h"
#include <vector>
#include "SpriteBatch.h"
#include "D3DHandler.h"
#include "Keyboard.h"

class Game
{
public:
	Game(D3DHandler& d3d);
	~Game();
	/// <summary> Game logic happens in here, should be called every frame </summary>
	/// <param name="deltaTime"> Time since last frame </param>
	void update(const float deltaTime);
	// Draw things on screen, should be called every frame
	void render(DirectX::SpriteBatch& spriteBatch);
private:
	D3DHandler* mpD3D;
	Player mPlayer;
	std::vector<PhysicsGameObject> mTerrain;
	//sf::Texture mPlayerIdleTexture;
	//sf::Texture mWallTexture;
	// **DEBUG
	TextGameObject mDebugText;
	//sf::Font mDebugFont;
	//Keyboard mKeyboard;
};

