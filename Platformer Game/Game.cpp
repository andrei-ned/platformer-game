#include "Game.h"
#include "GameConstants.h"
#include <cassert>
#include "TextureCache.h"
#include "FontCache.h"

Game::Game(D3DHandler& d3d) : mTerrain(5), mpD3D(&d3d) {
	mPlayer.setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Player/Idle.png", false), { 43, 28, 117, 102 });
	mPlayer.mPos = Vector2(200, 0);
	// Floor
	mTerrain.at(0).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, GameConstants::SCREEN_RES_X, 128 });
	mTerrain.at(0).mPos = Vector2(0, GameConstants::SCREEN_RES_Y - 128);
	// Walls
	mTerrain.at(1).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 64, GameConstants::SCREEN_RES_Y });
	mTerrain.at(1).mPos = Vector2(0, 0);
	mTerrain.at(2).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 64, GameConstants::SCREEN_RES_Y });
	mTerrain.at(2).mPos = Vector2(GameConstants::SCREEN_RES_X - 64, 0);
	// Platforms
	mTerrain.at(3).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 128, 64 });
	mTerrain.at(3).mPos = Vector2(500, 300);
	mTerrain.at(4).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 256, 64 });
	mTerrain.at(4).mPos = Vector2(700, 500);

	// **DEBUG
	mDebugText.setFont(*FontCache::get().LoadSpriteFont(&mpD3D->GetDevice(), "courier.spritefont"));
}

Game::~Game() {
}

void Game::update(const float deltaTime) {
	mPlayer.update(deltaTime);

	// Check for collisions
	// Note: Checking against every terrain object is inefficient, possibly change later
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		// Collide player against terrain
		mPlayer.resolveCollision(mTerrain.at(i));
	}

	mPlayer.PhysicsGameObject::update(deltaTime);

	// **DEBUG
	mDebugText.mString = std::to_string(mPlayer.mVelocity.x) + "\n" + std::to_string(mPlayer.mVelocity.y);
}

void Game::render(DirectX::SpriteBatch& spriteBatch) {
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		mTerrain.at(i).render(spriteBatch);
	}
	mPlayer.render(spriteBatch);

	//// **DEBUG
	mDebugText.render(spriteBatch);
}
