#include "BoidsSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"

BoidsSteering::BoidsSteering(KinematicUnit* pMover, KinematicUnit* pTarget)
:mpMover(pMover),
mpTarget(pTarget)
{
	//mRadius = DEFAULT_RADIUS;

	mpAlignment = new AlignmentSteering(pMover);
	mpCohesion = new CohesionSteering(pMover);
	mpSeperation = new SeperationSteering(pMover);
}

BoidsSteering::~BoidsSteering()
{
	delete mpAlignment;
	delete mpCohesion;
	delete mpSeperation;

	mpAlignment = NULL;
	mpCohesion = NULL;
	mpSeperation = NULL;
}

Steering * BoidsSteering::getSteering()
{
	// wander until needed
	/*if(checkNoneNearby())
	{
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() * (genRandomBinomial());
		return this;
	}*/

	// Boids behaivor
	// Calculate all the other steerings vectors
	//mLinear = mpAlignment->calculateAlignmentVector() + mpCohesion->calculateCohesionVector + mpSeperation->calculateSeperationVector();

	mLinear = mpAlignment->calculateAlignmentVector() + mpCohesion->calculateCohesionVector() + mpSeperation->calculateSeperationVector();

	mLinear.normalize();

	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;

	return this;
}

bool BoidsSteering::checkNoneNearby()
{
	std::map<UnitKey, KinematicUnit*>::iterator iter;
	std::map<UnitKey, KinematicUnit*> myMap = gpGame->getUnitManager()->getMap();

	for (iter = myMap.begin(); iter != myMap.end(); ++iter)
	{
		if (((iter->second->getPosition() - mpMover->getPosition()).getLength() <= mRadius &&
			(iter->second->getPosition() - mpMover->getPosition()).getLength() >= -mRadius))
		{
			return false;
		}
	}
	return true;
}
