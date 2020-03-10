#include "PlayState.h"
#include "StateMachine.h"
#include "MainMenuState.h"
#include "Keyboard.h"
#include "TextureCache.h"
#include "FontCache.h"
#include "PlayerController.h"
#include "GameConstants.h"
#include "SpriteAnimator.h"
#include <algorithm>

PlayState::PlayState(StateMachine& stateMachine) : State(stateMachine)
{
	// Set up backgrounds
	for (unsigned int i = 0; i < 3; i++)
	{
		auto bgObj = new GameObject;
		auto bgSpr = bgObj->addComponent<Sprite>();
		bgSpr->setTexture(*TextureCache::get().LoadTexture("Backgrounds/bg" + std::to_string(i) + ".png", false), { 0, 1, GameConstants::SCREEN_RES_X, 1080 });
		bgSpr->mOrigin.y = 1080;
		bgObj->mPos.y = GameConstants::SCREEN_RES_Y;
		mBackgroundSprites.push_back(bgSpr);
		mAllGameObjects.push_back(bgObj);
	}

	// Set up terrain
	std::pair<RECT, Vector2> terrainDetails[] = { 
		{{ 0, 0, GameConstants::SCREEN_RES_X, 128 }, Vector2(0, GameConstants::SCREEN_RES_Y - 128)},
	    {{ 0, 0, 64, GameConstants::SCREEN_RES_Y }, Vector2(0, 0)},
		{{ 0, 0, 64, GameConstants::SCREEN_RES_Y }, Vector2(GameConstants::SCREEN_RES_X - 64, 0)},
		{{ 0, 0, 128, 64 }, Vector2(500, 300)},
		{{ 0, 0, 256, 64 }, Vector2(700, 500)}
	};
	for (auto& item : terrainDetails)
	{
		auto terrainObj = new GameObject;
		terrainObj->addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture("Tiles/Dirt.png", false), item.first);
		terrainObj->addComponent<Collider>();
		terrainObj->mPos = item.second;
		mAllGameObjects.push_back(terrainObj);
	}

	// Set up player
	mpPlayer = new GameObject;
	mpPlayer->addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture("Player/Idle.png", false), { 2, 28, 72, 28 + 74 });
	mpPlayer->getComponent<Sprite>()->mOrigin = Vector2(35, 28 + 74);
	mpPlayer->addComponent<Collider>();
	mpPlayer->addComponent<PhysicsBody>();
	mpPlayer->addComponent<PlayerController>();
	// Animations
	auto animator = mpPlayer->addComponent<SpriteAnimator>();
	// Idle animation
	std::vector<RECT> idleFrames;
	for (int i = 0; i < 30; i++)
		idleFrames.push_back({ 0, 28, 75, 28 + 74 });
	for (int i = 0; i < 11; i++)
		idleFrames.push_back({ i * 76, 28, (i+1) * 76 - 1, 28 + 74 });
	animator->addAnimation("Idle", SpriteAnimator::Animation(idleFrames, .05f));
	// 
	mpPlayer->mPos = Vector2(200, 0);
	mAllGameObjects.push_back(mpPlayer);

	// **DEBUG
	auto debugTextObj = new GameObject;
	debugTextObj->mIsInWorldSpace = false;
	mpDebugText = debugTextObj->addComponent<Text>();
	mpDebugText->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	mAllGameObjects.push_back(debugTextObj);

	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->start();
		auto pCollider = mAllGameObjects.at(i)->getComponent<Collider>();
		if (pCollider)
			mAllColliders.push_back(pCollider);
		auto pPhysics = mAllGameObjects.at(i)->getComponent<PhysicsBody>();
		if (pPhysics)
			mAllPhysicsBodies.push_back(pPhysics);
	}

	animator->playAnimation("Idle");
}


PlayState::~PlayState()
{
	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		delete mAllGameObjects.at(i);
	}
	mAllGameObjects.clear();
}

void PlayState::update(const float deltaTime)
{
	// Input
	auto keyboardState = Keyboard::Get().GetState();
	if (keyboardState.Escape)
		mpStateMachine->changeState<MainMenuState>();

	// Update
	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->update(deltaTime);
	}

	// Resolve Collisions
	for (unsigned int i = 0; i < mAllPhysicsBodies.size(); i++)
	{
		for (unsigned int j = 0; j < mAllColliders.size(); j++)
		{
			mAllPhysicsBodies.at(i)->resolveCollision(*mAllColliders.at(j));
		}
	}

	// Update Late
	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->updateLate(deltaTime);
	}

	// **DEBUG
	mpDebugText->mString = std::to_string(mpPlayer->getComponent<PhysicsBody>()->mVelocity.x) + "\n" + std::to_string(mpPlayer->getComponent<PhysicsBody>()->mVelocity.y);
}

void PlayState::render(Camera& camera)
{
	// **TESTING
	RECTF levelBounds = { 0, -300, GameConstants::SCREEN_RES_X + 500, GameConstants::SCREEN_RES_Y};
	Vector2 camDesiredPos;
	Vector2 camCurrentPos = camera.getCenter();
	Vector2 camHalfDim = camera.getDimensions() / 2;
	Vector2 camPosMin = Vector2(levelBounds.left + camHalfDim.x, levelBounds.top + camHalfDim.y);
	Vector2 camPosMax = Vector2(levelBounds.right - camHalfDim.x, levelBounds.bottom - camHalfDim.y);

	camDesiredPos.x = camPosMin.x < camPosMax.x ? std::clamp(mpPlayer->mPos.x, levelBounds.left + camHalfDim.x, levelBounds.right - camHalfDim.x) : (levelBounds.left + levelBounds.right) / 2;
	camDesiredPos.y = camPosMin.y < camPosMax.y ? std::clamp(mpPlayer->mPos.y, levelBounds.top + camHalfDim.y, levelBounds.bottom - camHalfDim.y) : (levelBounds.bottom + levelBounds.top) / 2;
	// Smooth camera movement
	camDesiredPos = camCurrentPos + 0.05f * (camDesiredPos - camCurrentPos);
	// ****

	camera.centerOn(camDesiredPos);

	// Scroll backgrounds
	for (unsigned int i = 0; i < mBackgroundSprites.size(); i++)
	{
		mBackgroundSprites.at(i)->mTextureRect.left = static_cast<LONG>(camera.mPos.x * (i + 1) * 0.1f);
		mBackgroundSprites.at(i)->mTextureRect.right = static_cast<LONG>(mBackgroundSprites.at(i)->mTextureRect.left + camera.getDimensions().x);
		mBackgroundSprites.at(i)->mpGameObject->mPos = Vector2(camera.mPos.x, camera.mPos.y + camera.getDimensions().y);
	}

	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->render(camera);
	}
}
