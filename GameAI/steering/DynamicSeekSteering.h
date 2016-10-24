#ifndef DYNAMIC_SEEK_STEERING_H
#define DYNAMIC_SEEK_STEERING_H

#include "Steering.h"

class KinematicUnit;

class DynamicSeekSteering:public Steering
{
public:
	DynamicSeekSteering( KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = false );
	~DynamicSeekSteering(){};

	void setTarget( KinematicUnit* pTarget ){ mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;
};

#endif