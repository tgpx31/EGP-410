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
	if (mBehavior == WANDER_AND_FLEE)
		mPos.setX(mPos.getX() + 100);
	else if (mBehavior == WANDER_AND_SEEK)
		mPos.setX(mPos.getX() + 200);

	if (mBehavior == BOIDS_BEHAVIOR)
	{
		mPos.setX(mPos.getX() + 100);
	}

	gpGame->getUnitManager()->addUnit(mPos, mBehavior, gpGame->getPlayerUnit());
}