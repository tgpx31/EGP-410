#ifndef BOIDS_STEERING_H
#define BOIDS_STEERING_H

/* Boids Steering Class
 * Manages 3 behaivors via weighting and blending
 * AKA the Big Poppa class
 */

#include "Steering.h"
#include <string>

class KinematicUnit;

class AlignmentSteering;
class CohesionSteering;
class SeperationSteering;

class BoidsSteering : public Steering
{
private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;

	AlignmentSteering* mpAlignment;
	CohesionSteering* mpCohesion;
	SeperationSteering* mpSeperation;

	int mWeights[3] = {0, 0, 0};	// cohesion seperation alignment
	int mRadius;

	void loadWeights();

public:
	BoidsSteering(KinematicUnit* pMover, KinematicUnit* pTarget = NULL);
	~BoidsSteering();

	virtual Steering* getSteering();
	bool checkNoneNearby();

	void updateRadius(float radius);
	float getRadius() { return mRadius; };

	void updateWeight(int weight, int id);
	int getWeight(int id) { return mWeights[id]; };
};

#endif