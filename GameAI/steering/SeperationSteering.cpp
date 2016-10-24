#include "SeperationSteering.h"

#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

SeperationSteering::SeperationSteering(KinematicUnit* pMover, KinematicUnit* pTarget)
	:mpMover(pMover),
	mpTarget(pTarget)
{
	mRadius = DEFAULT_RADIUS;
}

Steering * SeperationSteering::getSteering()
{
	mLinear = calculateSeperationVector();
	mAngular = 0;
	return this;
}

Vector2D SeperationSteering::calculateSeperationVector()
{
	Vector2D seperationVector(0, 0);
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
				seperationVector += Vector2D(mpMover->getPosition().getX() - iter->second->getPosition().getX(), mpMover->getPosition().getY() - iter->second->getPosition().getY());
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
		seperationVector /= neighborCount;

		// Normalize
		seperationVector.normalize();

		return seperationVector;
	}

	return Vector2D();
}
