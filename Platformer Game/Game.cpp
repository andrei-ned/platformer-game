#include "Game.h"
#include "GameConstants.h"
#include <cassert>
//#include <iostream>

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
	mPlayer.updateInput(deltaTime);

	// Check for collisions
	// Note: Checking against every terrain object is inefficient, possibly change later
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		// Collide player against terrain
		mPlayer.resolveCollision(mTerrain.at(i));
	}

	mPlayer.updatePhysics(deltaTime);
}

void Game::render(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		mTerrain.at(i).render(window);
	}
	mPlayer.render(window);
}

//Game::CollisionType Game::getCollision(PhysicsGameObject o1, PhysicsGameObject o2) const {
//	if (o1.checkForCollision(o2)) // objects are intersecting
//	{
//		sf::FloatRect o1Bounds = o1.getBounds();
//		float o1Top = o1Bounds.top, o1Bottom = o1Bounds.top + o1Bounds.height, o1Left = o1Bounds.left, o1Right = o1Bounds.left + o1Bounds.width;
//		sf::FloatRect o2Bounds = o2.getBounds();
//		float o2Top = o2Bounds.top, o2Bottom = o2Bounds.top + o2Bounds.height, o2Left = o2Bounds.left, o2Right = o2Bounds.left + o2Bounds.width;
//
//		//std::cout << "o1: left:" << o1Bounds.left << " top:" << o1Bounds.top << " width:" << o1Bounds.width << " height:" << o1Bounds.height << "\n";
//		//std::cout << "o2: left:" << o2Bounds.left << " top:" << o2Bounds.top << " width:" << o2Bounds.width << " height:" << o2Bounds.height << "\n";
//		
//		if (o1Bottom > o2Top && o1Top < o2Top)
//			return CollisionType::Bottom;
//
//		//if (o1Bounds.top + o1Bounds.height > o2Bounds.top && o1Bounds.top < o2Bounds.top)
//		//	return CollisionType::Bottom;
//		//if (o1Bounds.left < o2Bounds.left + o2Bounds.width && o1Bounds.left + o1Bounds.width > o2Bounds.left + o2Bounds.width)
//		//	return CollisionType::Left;
//		//if (o1Bounds.left + o1Bounds.width > o2Bounds.left && o1Bounds.left < o2Bounds.left)
//		//	return CollisionType::Right;
//		//if (o1Bounds.top < o2Bounds.top + o2Bounds.height && o1Bounds.top + o1Bounds.height < o2Bounds.top + o2Bounds.top)
//		//	return CollisionType::Top;
//	}
//	return CollisionType::None;
//}
