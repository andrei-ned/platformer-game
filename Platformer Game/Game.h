#pragma once
#include "GameObject.h"
#include <vector>
#include "SpriteBatch.h"
#include "D3DHandler.h"
#include "Keyboard.h"
#include "PhysicsBody.h"
#include "Collider.h"
#include "Camera.h"
#include "Sprite.h"

class Game
{
public:
	Game(D3DHandler& d3d, SpriteBatch& spriteBatch);
	~Game();
	/// <summary> Game logic happens in here, should be called every frame </summary>
	/// <param name="deltaTime"> Time since last frame </param>
	void update(const float deltaTime);
	// Draw things on screen, should be called every frame
	void render();
private:
	Camera mCamera;
	D3DHandler* mpD3D;
	GameObject mPlayer;
	PhysicsBody* mpPlayerPhysics;
	std::vector<GameObject> mTerrain;
	std::vector<Collider*> mTerrainColliders;
	std::vector<GameObject> mBackgrounds;
	std::vector<Sprite*> mBackgroundSprites;
	// **DEBUG
	GameObject mDebugText;
};

