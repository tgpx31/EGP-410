#include "StateMachine.h"

#include <assert.h>

/**
*	STATE FUNCTIONS
**/
SM_State::~SM_State() 
{
	std::map<TransitionType, Transition*>::iterator iter;

	for (iter = mTransitions.begin(); iter != mTransitions.end(); iter++)
	{
		delete iter->second;
	}
}

// Add transition
void SM_State::addTransition(Transition * pTransition)
{
	mTransitions[pTransition->getTransitionType()] = pTransition;
}


StateMachine::~StateMachine()
{
	std::map<SM_ID, SM_State*>::iterator iter;

	for (iter = mStates.begin(); iter != mStates.end(); iter++)
	{
		delete iter->second;
	}
}

/**
*	STATE MACHINE FUNCTIONS
**/
void StateMachine::addState(SM_State * pState)
{
	mStates[pState->getID()] = pState;
}

// Update
void StateMachine::update()
{
	if (mpCurrentState == NULL)
	{
		start();
		assert(mpCurrentState != NULL);
	}

	Transition* pTransition = mpCurrentState->update();
	if (pTransition != NULL)
	{
		transitionToState(pTransition->getTargetStateID());
	}
}

// Start
void StateMachine::start()
{
	if (mInitialStateID != -1)
	{
		transitionToState(mInitialStateID);
	}
}

// Transition to state
void StateMachine::transitionToState(const SM_ID & targetID)
{
	if (mpCurrentState != NULL)
	{
		mpCurrentState->onExit();
	}

	mpCurrentState = mStates[targetID];
	if (mpCurrentState != NULL)
	{
		mpCurrentState->onEntrance();
	}
}
