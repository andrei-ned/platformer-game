#include "Game.h"
#include "GameObject.h"
#include "GameConstants.h"
#include <cassert>

Game::Game() : mTerrain(5) {
	//if (!mSpriteAtlas.loadFromFile("../Assets/atlas.png"))
	//	assert(false);
	if (!mPlayerIdleTexture.loadFromFile("../Assets/Player/Idle.png"))
		assert(false);
	if (!mWallTexture.loadFromFile("../Assets/Tiles/Dirt.png"))
		assert(false);
	mWallTexture.setRepeated(true);

	mPlayer.setTexture(mPlayerIdleTexture, sf::IntRect(43, 28, 74, 74));
	mPlayer.setPos(sf::Vector2f(500, 600));
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
}

Game::~Game() {
}

void Game::update(const sf::Time& deltaTime) {
	sf::Vector2f playerVel(0, GameConstants::GRAVITY);
	sf::FloatRect playerBounds = mPlayer.getBounds();
	// Checking against every terrain object is inefficient, possibly change later
	for (int i = 0; i < mTerrain.size(); i++)
	{
		if (mPlayer.checkForCollision(mTerrain.at(i)))
		{
			sf::FloatRect terrainBounds = mTerrain.at(i).getBounds();
			// Collision against floor
			if (playerBounds.top + playerBounds.height > terrainBounds.top)
			{
				if (playerVel.y > 0)
				{
					playerVel.y = 0;
				}
			}
		}
	}
	mPlayer.setVelocity(playerVel);
	mPlayer.update(deltaTime);
}

void Game::render(sf::RenderWindow& window) {
	for (int i = 0; i < mTerrain.size(); i++)
	{
		mTerrain.at(i).render(window);
	}
	mPlayer.render(window);
}
