#include "DeleteUnitMessage.h"
#include "Game.h"
#include "UnitManager.h"
#include <string>

DeleteUnitMessage::DeleteUnitMessage()
:GameMessage(DELETE_UNIT_MESSAGE)
{
}

DeleteUnitMessage::~DeleteUnitMessage()
{
}

void DeleteUnitMessage::process()
{
	std::string key;

	key = "Unit " + std::to_string(gpGame->getUnitManager()->getRandUnit());

	gpGame->getUnitManager()->deleteUnit(key);
}
