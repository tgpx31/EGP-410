#pragma once

#include "Steering.h"

class KinematicUnit;



class WanderAndSeekSteering : public Steering
{
private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;

	int mRadius;
public:
	WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = false, int radius = 50);
	~WanderAndSeekSteering() {};

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };
	virtual Steering* getSteering();
};