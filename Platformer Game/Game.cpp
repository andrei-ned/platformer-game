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

Game::Game(D3DHandler& d3d, SpriteBatch& spriteBatch) : mTerrain(5), mBackgrounds(3), mpD3D(&d3d), mCamera(spriteBatch, d3d.GetScreenViewport()) {
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
	// Backgrounds
	for (unsigned int i = 0; i < mBackgrounds.size(); i++)
	{
		mBackgrounds.at(i).addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture(&mpD3D->GetDevice(), "Backgrounds/bg" + std::to_string(i) + ".png", false), { 0, 1, GameConstants::SCREEN_RES_X, 1080 });
		//mBackgrounds.at(i).mIsInWorldSpace = false;
		mBackgroundSprites.push_back(mBackgrounds.at(i).getComponent<Sprite>());
		mBackgrounds.at(i).getComponent<Sprite>()->mOrigin.y = 1080;
		mBackgrounds.at(i).mPos.y = GameConstants::SCREEN_RES_Y;
	}

	// **DEBUG
	//mDebugText.setFont(*FontCache::get().LoadSpriteFont(&mpD3D->GetDevice(), "courier.spritefont"));
	Text* txt = mDebugText.addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont(&mpD3D->GetDevice(), "courier.spritefont"));
	mDebugText.mIsInWorldSpace = false;
	//mDebugText.removeComponent<Text>();

	mPlayer.start();
	mDebugText.start();
	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		mTerrain.at(i).start();
	}
	for (unsigned int i = 0; i < mBackgrounds.size(); i++)
	{
		mBackgrounds.at(i).start();
	}
}

Game::~Game() {
}

void Game::update(const float deltaTime) {

	//void Sprite::Scroll(float x, float y) {
	//	mTexRect.left += x;
	//	mTexRect.right += x;
	//	mTexRect.top += y;
	//	mTexRect.bottom += y;
	//}
	for (int i = 0; i < mBackgroundSprites.size(); i++)
	{
		mBackgroundSprites.at(i)->mTextureRect.left = mCamera.mPos.x * (i+1) * 0.1f;
		mBackgroundSprites.at(i)->mTextureRect.right = mBackgroundSprites.at(i)->mTextureRect.left + GameConstants::SCREEN_RES_X;

		//mBackgrounds.at(i).mPos.y = GameConstants::SCREEN_RES_Y + mCamera.mPos.y * 0.1f;
		//mBackgroundSprites.at(i)->mTextureRect.bottom = mCamera.mPos.y * i * 0.1f;
		//mBackgroundSprites.at(i)->mTextureRect.bottom = mBackgroundSprites.at(i)->mTextureRect.top + GameConstants::SCREEN_RES_Y;
	}

	mPlayer.update(deltaTime);

	//mCamera.mPos = mPlayer.mPos - Vector2(GameConstants::SCREEN_RES_X / 2, GameConstants::SCREEN_RES_Y / 2);
	mCamera.centerOn(mPlayer.mPos);

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
	for (int i = 0; i < mBackgrounds.size(); i++)
	{
		mBackgrounds.at(i).render(mCamera);
	}

	for (unsigned int i = 0; i < mTerrain.size(); i++)
	{
		mTerrain.at(i).render(mCamera);
	}
	mPlayer.render(mCamera);

	// **DEBUG
	mDebugText.render(mCamera);
}
