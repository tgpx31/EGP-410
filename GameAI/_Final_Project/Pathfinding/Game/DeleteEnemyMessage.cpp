#include "DeleteEnemyMessage.h"
#include "GameApp.h"
#include "EnemyManager.h"

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
	gpGameApp->getEnemyManager()->deleteEnemy();
}
