#include "WanderAndFleeSteering.h"
#include "KinematicUnit.h"

WanderAndFleeSteering::WanderAndFleeSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee, int radius)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mShouldFlee(shouldFlee)
	, mRadius(radius)
{
	mApplyDirectly = false;
}

Steering * WanderAndFleeSteering::getSteering()
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


	// return this
	return this;
}