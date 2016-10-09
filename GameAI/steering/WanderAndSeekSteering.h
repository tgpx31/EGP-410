#pragma once

#include "Steering.h"
#include "Game.h"

class KinematicUnit;

//const float DEFAULT_RADIUS = 200.0f;

class WanderAndSeekSteering : public Steering
{
private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;

	int mRadius;
public:
	WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = false, int radius = DEFAULT_RADIUS);
	~WanderAndSeekSteering() {};

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };
	void updateRadius(float radius) { mRadius += radius; };
	float getRadius() { return mRadius; };
	virtual Steering* getSteering();
};