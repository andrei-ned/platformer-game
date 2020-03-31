#pragma once
#include "SpriteBatch.h"
#include "D3DHandler.h"
#include "Camera.h"
#include "StateMachine.h"

class Game
{
public:
	Game(D3DHandler& d3d, DirectX::SpriteBatch& spriteBatch);
	~Game();
	/// <summary> Game logic happens in here, should be called every frame </summary>
	/// <param name="deltaTime"> Time since last frame </param>
	void update(const float deltaTime);
	// Draw things on screen, should be called every frame
	void render();
private:
	Camera mCamera;
	StateMachine mStateMachine;
};

