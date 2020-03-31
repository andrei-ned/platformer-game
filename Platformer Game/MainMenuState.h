#pragma once
#include "State.h"
#include "Text.h"
#include <vector>
#include "EventFunction.h"
#include <memory>

class MainMenuState : public State
{
public:
	MainMenuState(StateMachine& stateMachine);
	~MainMenuState() override;

	void update(const float deltaTime) override;
	void render(Camera& camera) override;
private:
	std::vector<std::unique_ptr<GameObject>> mAllGameObjects;
};

