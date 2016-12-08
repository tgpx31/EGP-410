#pragma once

#include "StateMachine.h"

class PlayerMoveState : public SM_State
{
public:
	PlayerMoveState(const SM_ID& id) :SM_State(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual Transition* update();
private:

};