#ifndef SEPERATION_STEERING_H
#define SEPERATION_STEERING_H

#include "Steering.h"

class KinematicUnit;

class SeperationSteering : public Steering
{
private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;

	int mRadius;

public:
	SeperationSteering(KinematicUnit* pMover, KinematicUnit* pTarget = NULL);
	~SeperationSteering() {};

	virtual Steering* getSteering();
	Vector2D calculateSeperationVector();

	void updateRadius(float radius) { mRadius += radius; };
};

#endif