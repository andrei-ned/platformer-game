#include "MainMenuState.h"
#include "GameObject.h"


MainMenuState::MainMenuState(StateMachine& stateMachine) : State(stateMachine)
{
	GameObject placeholderText;
	auto txt = placeholderText.addComponent<Text>();
	//txt->setFont()
	txt->mString = "Placeholder main menu.\nPress Space";
}


MainMenuState::~MainMenuState()
{
}
