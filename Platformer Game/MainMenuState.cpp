#include "MainMenuState.h"
#include "GameObject.h"
#include "FontCache.h"
#include "Keyboard.h"
#include "StateMachine.h"
#include "PlayState.h"

MainMenuState::MainMenuState(StateMachine& stateMachine) : State(stateMachine)
{
	auto placeholderText = new GameObject;
	auto txt = placeholderText->addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	txt->mString = "Placeholder main menu.\nPress Space";
	mAllGameObjects.push_back(placeholderText);

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
