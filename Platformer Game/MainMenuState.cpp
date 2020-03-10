#include "MainMenuState.h"
#include "GameObject.h"
#include "FontCache.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "GameConstants.h"
#include "TextureCache.h"
#include "UIButton.h"


MainMenuState::MainMenuState(StateMachine& stateMachine) : State(stateMachine), mChangeToPlayStateFunction([=]() { mpStateMachine->changeState<PlayState>(); })
{
	auto placeholderText = new GameObject;
	placeholderText->mIsInWorldSpace = false;
	auto txt = placeholderText->addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	txt->mString = "Placeholder main menu.";
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
	mpPlayButton->addComponent<UIButton>()->mOnClick += mChangeToPlayStateFunction;
	mAllGameObjects.push_back(mpPlayButton);

	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->start();
	}
}


MainMenuState::~MainMenuState()
{
	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		delete mAllGameObjects.at(i);
	}
	mAllGameObjects.clear();
	mpPlayButton->addComponent<UIButton>()->mOnClick -= mChangeToPlayStateFunction;
}

void MainMenuState::update(const float deltaTime)
{
	//auto keyboardState = Keyboard::Get().GetState();
	//auto mouseState = Mouse::Get().GetState();

	//if (mouseState.leftButton && mpPlayButton->getComponent<Collider>()->containsPoint(Vector2(mouseState.x, mouseState.y)))
	//{
	//	mpStateMachine->changeState<PlayState>();
	//}

	//if (keyboardState.Space)
	//{
	//	mpStateMachine->changeState<PlayState>();
	//}

	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->update(deltaTime);
	}
}

void MainMenuState::render(Camera& camera)
{
	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->render(camera);
	}
}
