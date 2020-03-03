#include "Game.h"
#include "GameConstants.h"
#include <cassert>
#include "TextureCache.h"
#include "FontCache.h"

Game::Game(D3DHandler& d3d) : mTerrain(5), mpD3D(&d3d) {
	//if (!mPlayerIdleTexture.loadFromFile("../Assets/Player/Idle.png"))
	//	assert(false);
	//if (!mWallTexture.loadFromFile("../Assets/Tiles/Dirt.png"))
	//	assert(false);
	//mWallTexture.setRepeated(true);

	//// **DEBUG
	//if (!mDebugFont.loadFromFile("../Assets/Fonts/arial.ttf"))
	//	assert(false);

	//mDebugText.setFont(FontCache::get().LoadSpriteFont())

	//mPlayer.setTexture(mPlayerIdleTexture, sf::IntRect(43, 28, 74, 74));
	mPlayer.setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Player/Idle.png", false), { 43, 28, 117, 102 });
	mPlayer.mPos = Vector2(200, 0);
	// Floor
	mTerrain.at(0).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, GameConstants::SCREEN_RES_X, 128 });
	mTerrain.at(0).mPos = Vector2(0, GameConstants::SCREEN_RES_Y - 128);
	//// Walls
	//mTerrain.at(1).setTexture(mWallTexture, sf::IntRect(0, 0, 64, GameConstants::SCREEN_RES_Y));
	//mTerrain.at(1).setPos(sf::Vector2f(0, 0));
	mTerrain.at(1).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 64, GameConstants::SCREEN_RES_Y });
	mTerrain.at(1).mPos = Vector2(0, 0);
	//mTerrain.at(2).setTexture(mWallTexture, sf::IntRect(0, 0, 64, GameConstants::SCREEN_RES_Y));
	//mTerrain.at(2).setPos(sf::Vector2f(GameConstants::SCREEN_RES_X - 64, 0));
	mTerrain.at(2).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 64, GameConstants::SCREEN_RES_Y });
	mTerrain.at(2).mPos = Vector2(GameConstants::SCREEN_RES_X - 64, 0);
	//// Platforms
	//mTerrain.at(3).setTexture(mWallTexture, sf::IntRect(0, 0, 128, 64));
	//mTerrain.at(3).setPos(sf::Vector2f(500, 300));
	mTerrain.at(3).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 128, 64 });
	mTerrain.at(3).mPos = Vector2(500, 300);
	//mTerrain.at(4).setTexture(mWallTexture, sf::IntRect(0, 0, 256, 64));
	//mTerrain.at(4).setPos(sf::Vector2f(700, 500));
	mTerrain.at(4).setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Tiles/Dirt.png", false), { 0, 0, 256, 64 });
	mTerrain.at(4).mPos = Vector2(700, 500);

	//// **DEBUG
	mDebugText.setFont(*FontCache::get().LoadSpriteFont(&mpD3D->GetDevice(), "courier.spritefont"));
	////mDebugText.setPos(sf::Vector2f(500, 300));
}

Game::~Game() {
}

void Game::update(const float deltaTime) {
	//auto keyboardState = Keyboard::Get().GetState();

	mPlayer.update(deltaTime);

	// Check for collisions
	// Note: Checking against every terrain object is inefficient, possibly change later
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		// Collide player against terrain
		mPlayer.resolveCollision(mTerrain.at(i));
	}

	//// **DEBUG
	//mDebugText.setString(std::to_string(mPlayer.mMaxVelDelta.x) + " x:" + std::to_string(mPlayer.getPos().x) + " y:" + std::to_string(mPlayer.getPos().y));

	mPlayer.PhysicsGameObject::update(deltaTime);

	// **DEBUG
	//mDebugText.mString = std::to_string(mPlayer.mVelocity.x) + "\n" + std::to_string(mPlayer.mVelocity.y);
	//mDebugText.mString = (keyboardState.A) ? "a" : "b";
	//mDebugText.mString = std::to_string(deltaTime);
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
