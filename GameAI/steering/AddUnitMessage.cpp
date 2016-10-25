#include "AddUnitMessage.h"

#include "UnitManager.h"

AddUnitMessage::AddUnitMessage(const Vector2D& pos, const Behavior& behavior)
:GameMessage(ADD_UNIT_MESSAGE)
,mPos(pos)
,mBehavior(behavior)
{
}

AddUnitMessage::~AddUnitMessage()
{
}

void AddUnitMessage::process()
{
	// Spawn multiple boids
	if (mBehavior == BOIDS_BEHAVIOR)
	{
		for (int i = 0; i < 5; ++i)
		{
			gpGame->getUnitManager()->addUnit(mPos, mBehavior, gpGame->getPlayerUnit());
			mPos += Vector2D(genRandomBinomial() * 75, genRandomBinomial() * 75);
		}
	}
}