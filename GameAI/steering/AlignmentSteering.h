#ifndef ALIGNMENT_STEERING_H
#define ALIGNMENT_STEERING_H

#include "Steering.h"

class KinematicUnit;

class AlignmentSteering : public Steering
{
private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;

	int mRadius;

public:
	AlignmentSteering(KinematicUnit* pMover, KinematicUnit* pTarget = NULL);
	~AlignmentSteering() {};

	virtual Steering* getSteering();
	Vector2D calculateAlignmentVector();

	void updateRadius(float radius) { mRadius += radius; };
	inline float getRadius() { return mRadius; };
};

#endif