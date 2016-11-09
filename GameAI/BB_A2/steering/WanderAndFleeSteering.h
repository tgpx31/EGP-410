#pragma once

#include "Steering.h"
#include "Game.h"

class KinematicUnit;

class WanderAndFleeSteering : public Steering
{
private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;

	int mRadius;
public:
	WanderAndFleeSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = true, int radius = DEFAULT_RADIUS);
	~WanderAndFleeSteering() {};

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };
	virtual Steering* getSteering();
};