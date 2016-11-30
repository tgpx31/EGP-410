#include "DamageState.h"

#include <iostream>

void DamageState::onEntrance()
{
	std::cout << "\nEntering DamageState id: " << mID << std::endl;
}

void DamageState::onExit()
{
	std::cout << "\nExitting DamageState id: " << mID << std::endl;
}

Transition * DamageState::update()
{
	std::cout << "\nDAMAGE!" << std::endl;

	// Find the right transition IMMEDIATELY
	// In this case, check lives. if lives remaining is 0, END_GAME
	// else, restart the game with 1 less life
	std::map<TransitionType, Transition*>::iterator iter = mTransitions.find(END_GAME_TRANSITION);
	if (iter != mTransitions.end())//found?
	{
		Transition* pTransition = iter->second;
		return pTransition;
	}

	// If there is no transition...
	return NULL;
}
