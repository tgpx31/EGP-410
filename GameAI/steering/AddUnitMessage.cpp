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
	if (mBehavior == DYNAMIC_SEEK)
		mPos.setX(mPos.getX() + 100);
	else if (mBehavior == DYNAMIC_ARRIVE)
		mPos.setX(mPos.getX() + 200);

	gpGame->getUnitManager()->addUnit(mPos, mBehavior, gpGame->getPlayerUnit());
}