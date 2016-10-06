#include "WanderAndSeekSteering.h"
#include "KinematicUnit.h"

#include "Game.h"
#include "UnitManager.h"
#include <map>

WanderAndSeekSteering::WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee, int radius)
:mpMover(pMover)
,mpTarget(pTarget)
,mShouldFlee(shouldFlee)
,mRadius(radius)
{
	mApplyDirectly = false;
}

Steering * WanderAndSeekSteering::getSteering()
{
	// Check radius
	// If target is not in radius, wander
	if (!((mpTarget->getPosition() - mpMover->getPosition()).getLength() <= mRadius &&
		(mpTarget->getPosition() - mpMover->getPosition()).getLength() >= -mRadius))
	{
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
	}

	else
	{
		// else, seek the player
		if (!mShouldFlee)
		{
			mLinear = mpTarget->getPosition() - mpMover->getPosition();
		}
		else
		{
			mLinear = mpMover->getPosition() - mpTarget->getPosition();
		}

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
	}
	
	// Avoid other units
	std::map<UnitKey, KinematicUnit*>::iterator iter;
	std::map<UnitKey, KinematicUnit*> myMap = gpGame->getUnitManager()->getMap();

	for (iter = myMap.begin(); iter != myMap.end(); ++iter)
	{
		// ignore this Unit
		if (iter->second != mpMover)
		{
			if (((iter->second->getPosition() - mpMover->getPosition()).getLength() <= mRadius &&
				(iter->second->getPosition() - mpMover->getPosition()).getLength() >= -mRadius))
			{
				mLinear = mpMover->getPosition() - iter->second->getPosition();
			}

			mLinear.normalize();
			mLinear *= mpMover->getMaxVelocity();
			mAngular = 0;
		}
	}

	

	// return this
	return this;
}