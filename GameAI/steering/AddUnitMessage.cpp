#include "AddUnitMessage.h"

#include "Game.h"
#include "UnitManager.h"

AddUnitMessage::AddUnitMessage(const Vector2D& pos, const bool& seek)
:GameMessage(ADD_UNIT_MESSAGE)
,mPos(pos)
,mSeek(seek)
{
}

AddUnitMessage::~AddUnitMessage()
{
}

void AddUnitMessage::process()
{
	if (mSeek)
		mPos.setX(mPos.getX() + 100);
	else
		mPos.setX(mPos.getX() + 200);

	gpGame->getUnitManager()->addUnit(mPos, mSeek, gpGame->getPlayerUnit());
}