#include "StateMachine.h"



StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}



void StateMachine::update(const float deltaTime)
{
	if (!mpCurrentState)
		return;
	if (mpCurrentState != mpDesiredState && mpDesiredState)
	{
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
