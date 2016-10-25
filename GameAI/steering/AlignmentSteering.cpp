#include "AlignmentSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

AlignmentSteering::AlignmentSteering(KinematicUnit* pMover, KinematicUnit* pTarget)
:mpMover(pMover),
mpTarget(pTarget)
{
	mRadius = DEFAULT_RADIUS;
}

Steering * AlignmentSteering::getSteering()
{
	mLinear = calculateAlignmentVector();
	mAngular = 0;
	return this;
}

Vector2D AlignmentSteering::calculateAlignmentVector()
{
	// Calculate the alignment vector
	// Check number of other units in your alignment radius
	Vector2D alignmentVector(0, 0);
	int neighborCount = 0;

	std::map<UnitKey, KinematicUnit*>::iterator iter;
	std::map<UnitKey, KinematicUnit*> myMap = gpGame->getUnitManager()->getMap();

	for (iter = myMap.begin(); iter != myMap.end(); ++iter)
	{
		// ignore this Unit
		if (iter->second != mpMover)
		{
			// Check if in mpMover's radius
			if ( ((iter->second->getPosition() - mpMover->getPosition()).getLength() <= mRadius &&
				(iter->second->getPosition() - mpMover->getPosition()).getLength() >= -mRadius) )
			{
				alignmentVector += Vector2D(iter->second->getVelocity().getX(), iter->second->getVelocity().getY());

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
		alignmentVector /= neighborCount;

		// Normalize
		alignmentVector.normalize();

		return alignmentVector;
	}

	return Vector2D();
}

