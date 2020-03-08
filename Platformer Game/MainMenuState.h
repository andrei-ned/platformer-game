#pragma once
#include "State.h"
#include "Text.h"
#include <vector>

class MainMenuState : public State
{
public:
	MainMenuState(StateMachine& stateMachine);
	~MainMenuState();
	void update(const float deltaTime) override;
	void render(Camera& camera) override;
private:
	std::vector<GameObject*> mAllGameObjects;
};

