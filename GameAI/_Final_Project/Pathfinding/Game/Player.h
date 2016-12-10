#pragma once

#include "KinematicUnit.h"

class StateMachine;
class SM_State;
class Transition;

	const int NUM_STATES = 1;
	const int NUM_TRANSITIONS = 1;

class Player : public KinematicUnit
{
private:

	StateMachine* mpStateMachine;
	SM_State* mpStateList[NUM_STATES];
	Transition* mpTransitions[NUM_TRANSITIONS];

	void initStates();
	void initTransitions();
	void applyTransitionsToStates();
	void addStatesToStateMachine();

public:
};