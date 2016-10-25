#include "CohesionSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"


CohesionSteering::CohesionSteering(KinematicUnit* pMover, KinematicUnit* pTarget)
	:mpMover(pMover),
	mpTarget(pTarget)
{
	mRadius = COHESION_RADIUS;
}

Steering * CohesionSteering::getSteering()
{
	mLinear = calculateCohesionVector();
	mAngular = 0;
	return this;
}

Vector2D CohesionSteering::calculateCohesionVector()
{
	// Add the position to the cohesion vector

	Vector2D cohesionVector(0, 0);
	int neighborCount = 0;

	std::map<UnitKey, KinematicUnit*>::iterator iter;
	std::map<UnitKey, KinematicUnit*> myMap = gpGame->getUnitManager()->getMap();

	for (iter = myMap.begin(); iter != myMap.end(); ++iter)
	{
		// ignore this Unit
		if (iter->second != mpMover)
		{
			// Check if in mpMover's radius
			if (((iter->second->getPosition() - mpMover->getPosition()).getLength() <= mRadius &&
				(iter->second->getPosition() - mpMover->getPosition()).getLength() >= -mRadius))
			{
				cohesionVector += Vector2D(iter->second->getPosition().getX(), iter->second->getPosition().getY());

				++neighborCount;
			}
		}
	}

	if (neighborCount == 0)
	{
		return Vector2D(0, 0);
	}
	else
	{
		cohesionVector /= neighborCount;

		cohesionVector = Vector2D(cohesionVector.getX() - mpMover->getPosition().getX(), cohesionVector.getY() - mpMover->getPosition().getY());

		// Normalize
		cohesionVector.normalize();

		return cohesionVector;
	}

	return Vector2D();
}

