#include "ChangeCurrentPropertyMessage.h"
#include "Game.h"
#include "Properties.h"
#include "UnitManager.h"
#include"KinematicUnit.h"
#include "WanderAndSeekSteering.h"

ChangeCurrentPropertyMessage::ChangeCurrentPropertyMessage(bool isInc, float amount)
:GameMessage(CHANGE_CURRENT_PROPERTY_MESSAGE)
,mInc(isInc)
,mAmount(amount)
{
}

ChangeCurrentPropertyMessage::~ChangeCurrentPropertyMessage()
{
}

void ChangeCurrentPropertyMessage::process()
{
	if (!gpGame->getProperties()->getActive())
	{
		return; // nothing to do here
	}

	// Get the current property
	GameProperties prop = gpGame->getProperties()->getCurrentProperty();
	std::map<UnitKey, KinematicUnit*> map = gpGame->getUnitManager()->getMap();
	std::map<UnitKey, KinematicUnit*>::iterator iter;

	//change it by the amount
	if (!mInc)
	{
		// Make amount negative
		mAmount = -mAmount;
	}

	// Velocity
	if (prop == 0)
	{
		gpGame->getUnitManager()->changeMaxVel(mAmount);
		for (iter = map.begin(); iter != map.end(); ++iter)
		{
			iter->second->changeMaxVel(mAmount);
			std::cout << "\nEnemyUnit MAXVEL: " << iter->second->getMaxVelocity();
		}
	}
	// Reaction Radius
	else if (prop == 1)
	{
		//DEFAULT_RADIUS += mAmount;
		for (iter = map.begin(); iter != map.end(); ++iter)
		{
			iter->second->getSteering()->updateRadius(mAmount);
			//std::cout << "\nEnemyUnit ReactionRadius: " << iter->second->getSteering()->getRadius();
		}
	}
	// Angular Velocity
	else if (prop == 2)
	{
		gpGame->getUnitManager()->changeRotVel(mAmount);
		for (iter = map.begin(); iter != map.end(); ++iter)
		{
			iter->second->changeRotVel(mAmount);
			std::cout << "\nEnemyUnit ROT_VEL: " << iter->second->getRotVelocity();
		}
	}
	// Unit accel
	else if (prop == 3)
	{
		// Change the Max acceleration
		gpGame->getUnitManager()->changeMaxAccel(mAmount);
		for (iter = map.begin(); iter != map.end(); ++iter)
		{
			iter->second->changeMaxAccel(mAmount);
			std::cout << "\nEnemyUnit MaxACCEL: " << iter->second->getMaxAcceleration();
		}
	}
}
