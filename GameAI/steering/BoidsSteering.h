#ifndef BOIDS_STEERING_H
#define BOIDS_STEERING_H

#include "Steering.h"

class KinematicUnit;

class AlignmentSteering;
class CohesionSteering;
class SeperationSteering;
class KinematicWanderSteering;

class BoidsSteering : public Steering
{
private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;

	AlignmentSteering* mpAlignment;
	CohesionSteering* mpCohesion;
	SeperationSteering* mpSeperation;

	KinematicWanderSteering* mpWander;

	int mRadius;

public:
	BoidsSteering(KinematicUnit* pMover, KinematicUnit* pTarget = NULL);
	~BoidsSteering();

	virtual Steering* getSteering();
	bool checkNoneNearby();
};

#endif