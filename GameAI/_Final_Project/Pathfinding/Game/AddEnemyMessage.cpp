#include "AddEnemyMessage.h"
#include "EnemyManager.h"
#include "GameApp.h"

AddEnemyMessage::AddEnemyMessage(const Vector2D& pos)
:GameMessage(ADD_UNIT_MESSAGE)
, mPos(pos)
{
}

AddEnemyMessage::~AddEnemyMessage()
{
}

void AddEnemyMessage::process()
{
	gpGameApp->getEnemyManager()->addEnemy(mPos);
}