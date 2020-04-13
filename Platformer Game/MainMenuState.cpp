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
#include "GameObjectUtils.h"

MainMenuState::MainMenuState(StateMachine& stateMachine) : State(stateMachine)
{
	auto placeholderText = std::make_unique<GameObject>();
	placeholderText->mPos.y = 150;
	placeholderText->mIsInWorldSpace = false;
	auto txt = placeholderText->addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	txt->mString = "Main Menu";
	txt->mOrigin.x = txt->getDimensions().x / 2;
	mAllGameObjects.push_back(std::move(placeholderText));

	auto playButton = makeUIButton("Play");
	playButton->mPos.y = 350;
	playButton->getComponent<UIButton>()->mOnClick += EventFunction<>([=]() { mpStateMachine->changeState<PlayState>(); });
	mAllGameObjects.push_back(std::move(playButton));

	auto exitButton = makeUIButton("Exit");
	exitButton->mPos.y = 450;
	exitButton->getComponent<UIButton>()->mOnClick += EventFunction<>([=]() { PostQuitMessage(0); });
	mAllGameObjects.push_back(std::move(exitButton));

	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->start();
	}
}


MainMenuState::~MainMenuState()
{
	mAllGameObjects.clear();
}

void MainMenuState::update(const float deltaTime)
{
	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->update(deltaTime);
	}
}

void MainMenuState::render(Camera& camera)
{
	for (unsigned int i = 0; i < mAllGameObjects.size(); i++)
	{
		mAllGameObjects.at(i)->mPos.x = camera.getDimensions().x / 2; // Center on screen
		mAllGameObjects.at(i)->render(camera);
	}
}
