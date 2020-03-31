#pragma once
#include "Camera.h"

class StateMachine;

class State
{
public:
	virtual ~State() {};
	// Called when machine enters the state
	virtual void enter() {}
	// Called when machine exits the state
	virtual void exit() {}
	// Will be called every frame, used for game logic
	virtual void update(const float deltaTime) {}
	// Will be called every frame, used for rendering
	virtual void render(Camera& camera) {}
protected:
	StateMachine* mpStateMachine;
	State(StateMachine& stateMachine);
};

