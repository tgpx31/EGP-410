#ifndef COHESION_STEERING_H
#define COHESION_STEERING_H

#include "Steering.h"

class KinematicUnit;

class CohesionSteering : public Steering
{
private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;

	int mRadius;

public:
	CohesionSteering(KinematicUnit* pMover, KinematicUnit* pTarget = NULL);
	~CohesionSteering() {};

	virtual Steering* getSteering();
	Vector2D calculateCohesionVector();
};

#endif