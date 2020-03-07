#pragma once
#include "State.h"
#include "Text.h"
#include <vector>

class MainMenuState : public State
{
public:
	MainMenuState(StateMachine& stateMachine);
	~MainMenuState();
private:
	std::vector<GameObject> mGameObjects;
};

