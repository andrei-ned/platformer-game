#pragma once
#include "State.h"
#include <unordered_map>
#include <typeindex>
#include <memory>


// Boilerplate setup for a state machine, to be used for e.g. game states
class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	// Will be called every frame, used for game logic
	void update(const float deltaTime);
	// Will be called every frame, used for rendering
	void render(Camera& camera);

	// Change current state to T, create it if it doesn't exist
	template <class T>
	void changeState();

private:
	// Add state T to map of states
	template <class T>
	T* addState();
	std::unordered_map<std::type_index, std::unique_ptr<State>> mStates; 
	State* mpCurrentState;
	State* mpDesiredState;
};

template <class T>
void StateMachine::changeState()
{
	auto search = mStates.find(typeid(T));
	if (search != mStates.end())
	{
		mpDesiredState = (*search).second.get();
	}
	else
	{
		mpDesiredState = addState<T>();
	}
}

template <class T>
T* StateMachine::addState()
{
	auto upT = std::make_unique<T>(*this);
	T* pT = upT.get();
	mStates.insert({ typeid(T), std::move(upT) });
	return pT;
}
