#include "DeleteEnemyMessage.h"
#include "Game.h"
#include "UnitManager.h"
#include <string>

DeleteEnemyMessage::DeleteEnemyMessage()
:GameMessage(DELETE_UNIT_MESSAGE)
{
}

DeleteEnemyMessage::~DeleteEnemyMessage()
{
}

void DeleteEnemyMessage::process()
{
	std::string key;

	//key = "Unit " + std::to_string(gpGame->getUnitManager()->getRandUnit());


	gpGame->getUnitManager()->deleteUnit();
}
