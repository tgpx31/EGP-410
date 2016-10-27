#ifndef BOIDS_STEERING_H
#define BOIDS_STEERING_H

/*
*****************************************************************************
/$$$$$$$ /$$                /$$$$$$$
| $$__  $|__/               | $$__  $$
| $$  \ $$/$$ /$$$$$$       | $$  \ $$/$$$$$$  /$$$$$$  /$$$$$$  /$$$$$$
| $$$$$$$| $$/$$__  $$      | $$$$$$$/$$__  $$/$$__  $$/$$__  $$|____  $$
| $$__  $| $| $$  \ $$      | $$____| $$  \ $| $$  \ $| $$  \ $$ /$$$$$$$
| $$  \ $| $| $$  | $$      | $$    | $$  | $| $$  | $| $$  | $$/$$__  $$
| $$$$$$$| $|  $$$$$$$      | $$    |  $$$$$$| $$$$$$$| $$$$$$$|  $$$$$$$
|_______/|__/\____  $$      |__/     \______/| $$____/| $$____/ \_______/
			 /$$  \ $$                       | $$     | $$
			|  $$$$$$/                       | $$     | $$
			 \______/                        |__/     |__/
*****************************************************************************

In other words, this is the GroupAlignment steering. It contains all methods for boids behavior.
https://www.youtube.com/watch?v=phaJXp_zMYM

*/

#include "Steering.h"

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

	int mWeights[3] = {3, 6, 10};	// cohesion seperation alignment

	int mRadius;

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