#include "BoidsSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"

#include "KinematicWanderSteering.h"

void BoidsSteering::loadWeights()
{
			mWeights[0] = gpGame->getUnitManager()->getWeight(0);
			mWeights[1] = gpGame->getUnitManager()->getWeight(1);
			mWeights[2] = gpGame->getUnitManager()->getWeight(2);
}

BoidsSteering::BoidsSteering(KinematicUnit* pMover, KinematicUnit* pTarget)
:mpMover(pMover),
mpTarget(pTarget)
{
	mRadius = DEFAULT_RADIUS;

	mpAlignment = new AlignmentSteering(pMover);
	mpCohesion = new CohesionSteering(pMover);
	mpSeperation = new SeperationSteering(pMover);

	mApplyDirectly = false;
	
	loadWeights();
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
	mpAlignment->getSteering();
	mpCohesion->getSteering();
	mpSeperation->getSteering();

	mpAlignment->setLinear(mpAlignment->getLinear() * mWeights[0]);
	mpCohesion->setLinear(mpCohesion->getLinear() * mWeights[1]);
	mpSeperation->setLinear(mpSeperation->getLinear() * mWeights[2]);

	mLinear = mpAlignment->getLinear() + mpCohesion->getLinear() + mpSeperation->getLinear();
	
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

void BoidsSteering::updateRadius(float radius)
{
	mpAlignment->updateRadius(radius);
	mpCohesion->updateRadius(radius);
	mpSeperation->updateRadius(radius);
	mRadius = mpAlignment->getRadius();
}

void BoidsSteering::updateWeight(int weight, int id)
{
	mWeights[id] += weight;
}
