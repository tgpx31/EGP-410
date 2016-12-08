#include "PlayerMoveState.h"

void PlayerMoveState::onEntrance()
{
	std::cout << "\nEntering PlayerMoveState id:" << mID << std::endl;
}

void PlayerMoveState::onExit()
{
	std::cout << "\nExitting PlayerMoveState id:" << mID << std::endl;
}

Transition * PlayerMoveState::update()
{
	// Check for transitions
	return NULL; // No transition
}
