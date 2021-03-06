#include "StateMachine.h"



StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
	mStates.clear();
}



void StateMachine::update(const float deltaTime)
{
	if (mpCurrentState != mpDesiredState && mpDesiredState)
	{
		if (mpCurrentState)
			mpCurrentState->exit();
		mpCurrentState = mpDesiredState;
		mpCurrentState->enter();
	}
	mpCurrentState->update(deltaTime);
}

void StateMachine::render(Camera& camera)
{
	if (!mpCurrentState)
		return;
	mpCurrentState->render(camera);
}
