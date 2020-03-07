#pragma once
#include "State.h"
#include <unordered_map>
#include <typeindex>

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
	// Add state T to map of states
private:
	template <class T>
	T* addState();
	std::unordered_map<std::type_index, State*> mStates; 
	State* mpCurrentState;
	State* mpDesiredState;
};

template <class T>
void StateMachine::changeState()
{
	auto search = mStates.find(typeid(T));
	if (search != mStates.end())
	{
		mpDesiredState = (*search).second;
	}
	else
	{
		mpDesiredState = addState<T>();
	}
}

template <class T>
T* StateMachine::addState()
{
	T* pT = new T(*this);
	mStates.insert({ typeid(T), pT });
	return pT;
}
