#include "Game.h"
#include "GameConstants.h"
#include <cassert>
#include "TextureCache.h"
#include "FontCache.h"
#include "Sprite.h"
#include "Text.h"
#include "Collider.h"
#include "PhysicsBody.h"
#include "PlayerController.h"

Game::Game(D3DHandler& d3d, SpriteBatch& spriteBatch) : mTerrain(5), mpD3D(&d3d), mCamera(spriteBatch) {
	mPlayer.addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Player/Idle.png", false), { 43, 28, 117, 102 });
	mPlayer.addComponent<Collider>();
	mpPlayerPhysics = mPlayer.addComponent<PhysicsBody>();
	mPlayer.addComponent<PlayerController>();
	mPlayer.mPos = Vector2(200, 0);
	// Floor
	mTerrain.at(0).addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, GameConstants::SCREEN_RES_X, 128 });
	mTerrain.at(0).mPos = Vector2(0, GameConstants::SCREEN_RES_Y - 128);
	mTerrainColliders.push_back(mTerrain.at(0).addComponent<Collider>());
	// Walls
	mTerrain.at(1).addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 64, GameConstants::SCREEN_RES_Y });
	mTerrain.at(1).mPos = Vector2(0, 0);
	mTerrainColliders.push_back(mTerrain.at(1).addComponent<Collider>());
	mTerrain.at(2).addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 64, GameConstants::SCREEN_RES_Y });
	mTerrain.at(2).mPos = Vector2(GameConstants::SCREEN_RES_X - 64, 0);
	mTerrainColliders.push_back(mTerrain.at(2).addComponent<Collider>());
	// Platforms
	mTerrain.at(3).addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 128, 64 });
	mTerrain.at(3).mPos = Vector2(500, 300);
	mTerrainColliders.push_back(mTerrain.at(3).addComponent<Collider>());
	mTerrain.at(4).addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 256, 64 });
	mTerrain.at(4).mPos = Vector2(700, 500);
	mTerrainColliders.push_back(mTerrain.at(4).addComponent<Collider>());

	// **DEBUG
	//mDebugText.setFont(*FontCache::get().LoadSpriteFont(&mpD3D->GetDevice(), "courier.spritefont"));
	Text* txt = mDebugText.addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont(&mpD3D->GetDevice(), "courier.spritefont"));
	//mDebugText.removeComponent<Text>();

	mPlayer.start();
	mDebugText.start();
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		mTerrain.at(i).start();
	}
}

Game::~Game() {
}

void Game::update(const float deltaTime) {
	mPlayer.update(deltaTime);

	mCamera.mPos = mPlayer.mPos - Vector2(GameConstants::SCREEN_RES_X / 2, GameConstants::SCREEN_RES_Y / 2);

	// Check for collisions
	// Note: Checking against every terrain object is inefficient, possibly change later
	for (unsigned int i = 0; i < mTerrainColliders.size(); i++)
	{
		// Collide player against terrain
		mpPlayerPhysics->resolveCollision(*mTerrainColliders.at(i));
	}

	mPlayer.updateLate(deltaTime);

	// **DEBUG
	mDebugText.getComponent<Text>()->mString = std::to_string(mpPlayerPhysics->mVelocity.x) + "\n" + std::to_string(mpPlayerPhysics->mVelocity.y);
}

void Game::render() {
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		mTerrain.at(i).render(mCamera);
	}
	mPlayer.render(mCamera);

	// **DEBUG
	mDebugText.render(mCamera);
}
