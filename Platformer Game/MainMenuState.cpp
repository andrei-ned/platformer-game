#include "MainMenuState.h"
#include "GameObject.h"
#include "FontCache.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "GameConstants.h"
#include "TextureCache.h"

MainMenuState::MainMenuState(StateMachine& stateMachine) : State(stateMachine)
{
	auto placeholderText = new GameObject;
	auto txt = placeholderText->addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	txt->mString = "Placeholder main menu.\nPress Space";
	mAllGameObjects.push_back(placeholderText);

	mpPlayButton = new GameObject;
	mpPlayButton->mIsInWorldSpace = false;
	mpPlayButton->mPos = Vector2(GameConstants::SCREEN_RES_X / 2, 250);
	auto spr = mpPlayButton->addComponent<Sprite>();
	spr->setTexture(*TextureCache::get().LoadTexture("UI/buttons.png", false), { 488, 50, 488 + 512, 50 + 128 });
	spr->mOrigin = Vector2(256, 64);
	spr->mScale = Vector2(0.75f, 0.75f);
	txt = mpPlayButton->addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	txt->mString = "Play";
	txt->mOrigin = txt->getDimensions() / 2;
	mpPlayButton->addComponent<Collider>();
	mAllGameObjects.push_back(mpPlayButton);

	for (int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->start();
	}
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::update(const float deltaTime)
{
	auto keyboardState = Keyboard::Get().GetState();
	auto mouseState = Mouse::Get().GetState();

	if (mouseState.leftButton && mpPlayButton->getComponent<Collider>()->containsPoint(Vector2(mouseState.x, mouseState.y)))
	{
		mpStateMachine->changeState<PlayState>();
	}

	if (keyboardState.Space)
	{
		mpStateMachine->changeState<PlayState>();
	}
}

void MainMenuState::render(Camera& camera)
{
	for (int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->render(camera);
	}
}
