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
#include "Tilemap.h"
#include "Tile.h"
#include "GameObjectUtils.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayState::PlayState(StateMachine& stateMachine) : State(stateMachine)
{
	// Set up backgrounds
	for (unsigned int i = 0; i < 3; i++)
	{
		auto bgObj = std::make_unique<GameObject>();
		auto bgSpr = bgObj->addComponent<Sprite>();
		bgSpr->setTexture(*TextureCache::get().LoadTexture("Backgrounds/bg" + std::to_string(i) + ".png", false), { 0, 1, GameConstants::SCREEN_RES_X, 1080 });
		bgSpr->mOrigin.y = 1080;
		bgObj->mPos.y = GameConstants::SCREEN_RES_Y;
		mBackgroundSprites.push_back(bgSpr);
		mAllGameObjects.push_back(std::move(bgObj));
	}

	// Set up death event
	EventFunction<Collider&> playerDeathEvent([=](Collider& other)
	{
		mpPlayer->mPos = mLevels.at(mCurrentLevelIndex).playerSpawnPos;
		mpPlayer->getComponent<PhysicsBody>()->mVelocity = Vector2(0, 0);
	});

	// Set up tilemap
	Tile tile;
	tile.setTexture(0, *TextureCache::get().LoadTexture("Tiles/Grass.png", false));
	tile.setTexture(Tile::Adjacency::Top | Tile::Adjacency::Bottom, *TextureCache::get().LoadTexture("Tiles/Column.png", false));
	tile.setTexture(Tile::Adjacency::Top, *TextureCache::get().LoadTexture("Tiles/column_down.png", false));
	tile.setTexture(Tile::Adjacency::Top | Tile::Adjacency::Bottom | Tile::Adjacency::Right | Tile::Adjacency::Left, *TextureCache::get().LoadTexture("Tiles/Dirt.png", false));
	tile.setTexture(Tile::Adjacency::Top | Tile::Adjacency::Right | Tile::Adjacency::Left, *TextureCache::get().LoadTexture("Tiles/DirtDown.png", false));
	tile.setTexture(Tile::Adjacency::Top | Tile::Adjacency::Bottom | Tile::Adjacency::Right, *TextureCache::get().LoadTexture("Tiles/DirtLeft.png", false));
	tile.setTexture(Tile::Adjacency::Top | Tile::Adjacency::Right, *TextureCache::get().LoadTexture("Tiles/DirtLeftCorner.png", false));
	tile.setTexture(Tile::Adjacency::Top | Tile::Adjacency::Bottom  | Tile::Adjacency::Left, *TextureCache::get().LoadTexture("Tiles/DirtRight.png", false));
	tile.setTexture(Tile::Adjacency::Top | Tile::Adjacency::Left, *TextureCache::get().LoadTexture("Tiles/DirtRightCorner.png", false));
	tile.setTexture(Tile::Adjacency::Right, *TextureCache::get().LoadTexture("Tiles/GrassCliffLeft.png", false));
	tile.setTexture(Tile::Adjacency::Right | Tile::Adjacency::Left, *TextureCache::get().LoadTexture("Tiles/GrassCliffMid.png", false));
	tile.setTexture(Tile::Adjacency::Left, *TextureCache::get().LoadTexture("Tiles/GrassCliffRight.png", false));
	tile.setTexture(Tile::Adjacency::Right | Tile::Adjacency::Bottom, *TextureCache::get().LoadTexture("Tiles/GrassLeft.png", false));
	tile.setTexture(Tile::Adjacency::Right | Tile::Adjacency::Left | Tile::Adjacency::Bottom, *TextureCache::get().LoadTexture("Tiles/GrassMid.png", false));
	tile.setTexture(Tile::Adjacency::Left | Tile::Adjacency::Bottom, *TextureCache::get().LoadTexture("Tiles/GrassRight.png", false));
	tile.setTexture(Tile::Adjacency::Bottom, *TextureCache::get().LoadTexture("Tiles/GrassTop.png", false));
	tile.mScale = Vector2(0.5f, 0.5f);

	Tilemap tilemap(tile, Vector2(64, 64));
	//for (int i = -1; i < 30; i++)
	//{
	//	mAllGameObjects.push_back(tilemap.addTile(i, 13));
	//	mAllGameObjects.push_back(tilemap.addTile(i, 14));
	//}
	// Level 1
	addGameObjects(tilemap.fillTiles({ -1,13 }, { 30,14 }));
	addGameObjects(tilemap.fillTiles({ 9,11 }, { 15,12 }));
	addGameObjects(tilemap.fillTiles({ 16,12 }, { 22,7 }));
	addGameObjects(tilemap.fillTiles({ 23,12 }, { 22,7 }));
	addGameObjects(tilemap.fillTiles({ 11,3 }, { 13,3 }));
	// Level 2
	addGameObjects(tilemap.fillTiles({ 20,1 }, { 32,12 }));
	addGameObjects(tilemap.fillTiles({ 38,1 }, { 43,12 }));
	addGameObjects(tilemap.fillTiles({ 50,0 }, { 55,0 }));
	addGameObjects(tilemap.fillTiles({ 58,-4 }, { 61,-4 }));
	addGameObjects(tilemap.fillTiles({ 70,2 }, { 73,2 }));
	addGameObjects(tilemap.fillTiles({ 78,-1 }, { 120,12 }));
	auto pit = std::make_unique<GameObject>();
	pit->mPos = Vector2(64 * 32, 64 * 5);
	auto pitCol = pit->addComponent<Collider>();
	pitCol->mIsTrigger = true;
	pitCol->mSize = Vector2(64 * 48, 1);
	pitCol->mOnTrigger += playerDeathEvent;
	mAllGameObjects.push_back(std::move(pit));
	// Level 3
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(91 * 64, -64)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(92 * 64, -64)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(93 * 64, -64)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(106 * 64, -64)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(107 * 64, -64)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(108 * 64, -64)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(111 * 64, -64)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(112 * 64, -64)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(113 * 64, -64)));
	addGameObjects(tilemap.fillTiles({ 120,-5 }, { 136,3 }));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Left, Vector2(120 * 64, -64 * 4)));
	// Level 4
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(134 * 64, -64 * 5)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(135 * 64, -64 * 5)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(136 * 64, -64 * 5)));
	pit = std::make_unique<GameObject>();
	pit->mPos = Vector2(64 * 135, 64 * 3);
	pitCol = pit->addComponent<Collider>();
	pitCol->mIsTrigger = true;
	pitCol->mSize = Vector2(64 * 48, 1);
	pitCol->mOnTrigger += playerDeathEvent;
	mAllGameObjects.push_back(std::move(pit));
	addGameObjects(tilemap.fillTiles({ 142,0 }, { 147,0 }));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(144 * 64, 0)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(145 * 64, 0)));
	addGameObjects(tilemap.fillTiles({ 151,-2 }, { 157,-2 }));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(151 * 64, 64 * -2)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(152 * 64, 64 * -2)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(156 * 64, 64 * -2)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Up, Vector2(157 * 64, 64 * -2)));
	addGameObjects(tilemap.fillTiles({ 163,-13 }, { 170,-3 }));
	addGameObjects(tilemap.fillTiles({ 161,0 }, { 170,2 }));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Left, Vector2(163 * 64, 64 * -2)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Left, Vector2(163 * 64, 64 * -3)));
	mAllGameObjects.push_back(makeSpike(playerDeathEvent, SpikeDirection::Left, Vector2(163 * 64, 64 * -4)));
	//for (int i = 6; i < 11; i++)
	//	mAllGameObjects.push_back(tilemap.addTile(7, i));
	tilemap.updateTilemap();


	//auto spike = makeSpike(playerDeathEvent, SpikeDirection::Up);
	//spike->mPos = Vector2(5 * 64, 13 * 64 + 10);
	//mAllGameObjects.push_back(std::move(spike));

	// Set up collider at edge of map
	auto mapLeftBound = std::make_unique<GameObject>();
	mapLeftBound->mPos.x = -10;
	mapLeftBound->addComponent<Collider>()->mSize = Vector2(10, 1000);
	mAllGameObjects.push_back(std::move(mapLeftBound));
	//auto mapRightBound = std::make_unique<GameObject>();
	//mapRightBound->mPos.x = 64 * 45;
	//mapRightBound->mPos.y = -500;
	//mapRightBound->addComponent<Collider>()->mSize = Vector2(10, 1000);
	//mAllGameObjects.push_back(std::move(mapRightBound));

	// Set up levels
	mCurrentLevelIndex = 0;
	mLevels.insert(mLevels.end(), { 
		Level({ 0, -64 * 6, 64 * 25, 64 * 14 }, Vector2(150,800)),
		Level({ 64 * 25, -64 * 10, 64 * 85, 64 * 4}, Vector2(1770,60)),
		Level({ 64 * 85, -64 * 10, 64 * 125, 64 * 4}, Vector2(5530,-70)),
		Level({ 64 * 125, -64 * 12, 64 * 168, 64 * 2}, Vector2(8140,-330)),
		Level({ 64 * 168, -64 * 12, 64 * 200, 64 * 2}, Vector2(10850,0))
	});

	// Set up player
	auto upPlayer = std::make_unique<GameObject>();
	mpPlayer = upPlayer.get();
	mpPlayer->addComponent<Sprite>()->setTexture(*TextureCache::get().LoadTexture("Player/Idle.png", false), { 1, 24, 75, 24 + 78 });
	mpPlayer->getComponent<Sprite>()->mOrigin = Vector2(36, 80);
	mpPlayer->addComponent<Collider>();
	mpPlayer->addComponent<PhysicsBody>();
	mpPlayer->addComponent<PlayerController>();
	// Animations
	auto animator = mpPlayer->addComponent<SpriteAnimator>();
	// Idle animation
	std::vector<RECT> idleFrames;
	for (int i = 0; i < 30; i++)
		idleFrames.push_back({ 0, 24, 75, 28 + 80 });
	for (int i = 0; i < 11; i++)
		idleFrames.push_back({ i * 76, 24, (i+1) * 76 - 1, 24 + 80 });
	animator->addAnimation("Idle", SpriteAnimator::Animation(idleFrames, .05f, TextureCache::get().LoadTexture("Player/Idle.png", false)));
	// Run animation
	std::vector<RECT> runFrames;
	for (int i = 0; i < 10; i++)
		runFrames.push_back({ i * 100, 49, (i + 1) * 100 - 1, 49 + 80 });
	for (int i = 0; i < 8; i++)
		runFrames.push_back({ i * 100, 176, (i + 1) * 100 - 1, 176 + 80 });
	animator->addAnimation("Run", SpriteAnimator::Animation(runFrames, .05f, TextureCache::get().LoadTexture("Player/Run.png", false)));
	// Jump/Fall animations
	animator->addAnimation("Jump", SpriteAnimator::Animation({ {37, 25, 37 + 77,25 + 78} }, 1.0f, TextureCache::get().LoadTexture("Player/Jump.png", false), false));
	animator->addAnimation("Fall", SpriteAnimator::Animation({ {152, 25, 152 + 67,25 + 78} }, 1.0f, TextureCache::get().LoadTexture("Player/Jump.png", false), false));
	// 
	mpPlayer->mPos = Vector2(200, 0);
	mpPlayer->mPos = Vector2(10850, 0);// **DEBUG
	mAllGameObjects.push_back(std::move(upPlayer));

	// **DEBUG
	auto debugTextObj = std::make_unique<GameObject>();
	debugTextObj->mIsInWorldSpace = false;
	mpDebugText = debugTextObj->addComponent<Text>();
	mpDebugText->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	mAllGameObjects.push_back(std::move(debugTextObj));
	// ***

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
	//for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	//{
	//	delete mAllGameObjects.at(i);
	//}
	mAllGameObjects.clear();
}

void PlayState::update(const float deltaTime)
{
	// Update current level
	for (unsigned int i = 0; i < mLevels.size(); i++)
		if (mLevels.at(i).bounds.containsPoint(mpPlayer->mPos))
			mCurrentLevelIndex = i;

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
	//mpDebugText->mString = std::to_string(mpPlayer->getComponent<PhysicsBody>()->mVelocity.x) + "\n" + std::to_string(mpPlayer->getComponent<PhysicsBody>()->mVelocity.y);
	mpDebugText->mString = std::to_string(static_cast<int>(mpPlayer->mPos.x / 64)) + ": " + std::to_string(mpPlayer->mPos.x) + "\n" + std::to_string(static_cast<int>(mpPlayer->mPos.y / 64)) + ": " + std::to_string(mpPlayer->mPos.y);
}

void PlayState::render(Camera& camera)
{
	// Camera movement within level bounds
	RECTF levelBounds = mLevels.at(mCurrentLevelIndex).bounds;
	Vector2 camDesiredPos;
	Vector2 camCurrentPos = camera.getCenter();
	Vector2 camHalfDim = camera.getDimensions() / 2;
	Vector2 camPosMin = Vector2(levelBounds.left + camHalfDim.x, levelBounds.top + camHalfDim.y);
	Vector2 camPosMax = Vector2(levelBounds.right - camHalfDim.x, levelBounds.bottom - camHalfDim.y);

	camDesiredPos.x = camPosMin.x < camPosMax.x ? std::clamp(mpPlayer->mPos.x + camHalfDim.x / 3, levelBounds.left + camHalfDim.x, levelBounds.right - camHalfDim.x) : (levelBounds.left + levelBounds.right) / 2;
	camDesiredPos.y = camPosMin.y < camPosMax.y ? std::clamp(mpPlayer->mPos.y, levelBounds.top + camHalfDim.y, levelBounds.bottom - camHalfDim.y) : (levelBounds.bottom + levelBounds.top) / 2;
	// Smooth camera movement
	camDesiredPos = camCurrentPos + 0.05f * (camDesiredPos - camCurrentPos);

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

void PlayState::addGameObjects(std::vector<GameObject*> newGameObjects)
{
	mAllGameObjects.insert(mAllGameObjects.end(), newGameObjects.begin(), newGameObjects.end());
}
