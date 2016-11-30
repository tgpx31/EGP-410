#pragma once

#include "StateMachine.h"

class DamageState : public SM_State
{
public:
	DamageState(const SM_ID& id) :SM_State(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual Transition* update();
private:
};