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
	auto placeholderText = new GameObject;
	placeholderText->mPos.y = 150;
	placeholderText->mIsInWorldSpace = false;
	auto txt = placeholderText->addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	txt->mString = "Main Menu";
	txt->mOrigin.x = txt->getDimensions().x / 2;
	mAllGameObjects.push_back(placeholderText);

	auto playButton = makeUIButton("Play");
	playButton->mPos.y = 350;
	playButton->getComponent<UIButton>()->mOnClick += EventFunction<>([=]() { mpStateMachine->changeState<PlayState>(); });
	mAllGameObjects.push_back(playButton);

	auto exitButton = makeUIButton("Exit");
	exitButton->mPos.y = 450;
	exitButton->getComponent<UIButton>()->mOnClick += EventFunction<>([=]() { PostQuitMessage(0); });
	mAllGameObjects.push_back(exitButton);

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
		mAllGameObjects.at(i)->mPos.x = camera.getDimensions().x / 2;
		mAllGameObjects.at(i)->render(camera);
	}
}
