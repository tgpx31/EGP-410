#include "BoidsSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"

#include "KinematicWanderSteering.h"

BoidsSteering::BoidsSteering(KinematicUnit* pMover, KinematicUnit* pTarget)
:mpMover(pMover),
mpTarget(pTarget)
{
	//mRadius = DEFAULT_RADIUS;

	mpAlignment = new AlignmentSteering(pMover);
	mpCohesion = new CohesionSteering(pMover);
	mpSeperation = new SeperationSteering(pMover);
	mpWander = new KinematicWanderSteering(pMover);

	mApplyDirectly = false;
}

BoidsSteering::~BoidsSteering()
{
	delete mpAlignment;
	delete mpCohesion;
	delete mpSeperation;

	delete mpWander;

	mpAlignment = NULL;
	mpCohesion = NULL;
	mpSeperation = NULL;

	mpWander = NULL;
}

Steering * BoidsSteering::getSteering()
{
	//mApplyDirectly = false;

	mpAlignment->getSteering();
	mpCohesion->getSteering();
	mpSeperation->getSteering();
	//mpWander->getSteering();

	mpAlignment->setLinear(mpAlignment->getLinear() * 3);
	mpCohesion->setLinear(mpCohesion->getLinear() * 1);
	mpSeperation->setLinear(mpSeperation->getLinear() * 5);

	mLinear = mpAlignment->getLinear() + mpCohesion->getLinear() + mpSeperation->getLinear() + mpWander->getLinear();

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
