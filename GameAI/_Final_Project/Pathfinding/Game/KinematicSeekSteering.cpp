#include "KinematicSeekSteering.h"
#include "KinematicUnit.h"

KinematicSeekSteering::KinematicSeekSteering(KinematicUnit *pMover, const Vector2D &targetPosition)
	:mpMover(pMover)
	, mTarget(targetPosition)
{
}

Steering* KinematicSeekSteering::getSteering()
{
	if (mSeeking)
		mLinear = mTarget - mpMover->getPosition();
	if (!mSeeking)
		mLinear = mpMover->getPosition() - mTarget;

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;
	return this;
}