#include "Game.h"
#include "GameConstants.h"
#include <cassert>

Game::Game() : mTerrain(5) {
	if (!mPlayerIdleTexture.loadFromFile("../Assets/Player/Idle.png"))
		assert(false);
	if (!mWallTexture.loadFromFile("../Assets/Tiles/Dirt.png"))
		assert(false);
	mWallTexture.setRepeated(true);

	// **DEBUG
	if (!mDebugFont.loadFromFile("../Assets/Fonts/arial.ttf"))
		assert(false);

	mPlayer.setTexture(mPlayerIdleTexture, sf::IntRect(43, 28, 74, 74));
	mPlayer.setPos(sf::Vector2f(200, 0));
	// Floor
	mTerrain.at(0).setTexture(mWallTexture, sf::IntRect(0, 0, GameConstants::SCREEN_RES_X, 128));
	mTerrain.at(0).setPos(sf::Vector2f(0, GameConstants::SCREEN_RES_Y - 128));
	// Walls
	mTerrain.at(1).setTexture(mWallTexture, sf::IntRect(0, 0, 64, GameConstants::SCREEN_RES_Y));
	mTerrain.at(1).setPos(sf::Vector2f(0, 0));
	mTerrain.at(2).setTexture(mWallTexture, sf::IntRect(0, 0, 64, GameConstants::SCREEN_RES_Y));
	mTerrain.at(2).setPos(sf::Vector2f(GameConstants::SCREEN_RES_X - 64, 0));
	// Platforms
	mTerrain.at(3).setTexture(mWallTexture, sf::IntRect(0, 0, 128, 64));
	mTerrain.at(3).setPos(sf::Vector2f(500, 300));
	mTerrain.at(4).setTexture(mWallTexture, sf::IntRect(0, 0, 256, 64));
	mTerrain.at(4).setPos(sf::Vector2f(700, 500));

	// **DEBUG
	mDebugText.setFont(mDebugFont);
	//mDebugText.setPos(sf::Vector2f(500, 300));
}

Game::~Game() {
}

void Game::update(const sf::Time& deltaTime) {
	mPlayer.update(deltaTime);

	// Check for collisions
	// Note: Checking against every terrain object is inefficient, possibly change later
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		// Collide player against terrain
		mPlayer.resolveCollision(mTerrain.at(i));
	}

	mPlayer.PhysicsGameObject::update(deltaTime);

	mDebugText.setString(std::to_string(mPlayer.getVelocity().x));
}

void Game::render(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		mTerrain.at(i).render(window);
	}
	mPlayer.render(window);

	// **DEBUG
	mDebugText.render(window);
}
