#include "EditPropertyMessage.h"
#include "GameApp.h"
#include "Player.h"
#include "EnemyManager.h"

EditPropertyMessage::EditPropertyMessage(int id, bool inc)
:GameMessage(EDIT_PROPERTY_MESSAGE)
,mID(id)
,mInc(inc)
{
}

EditPropertyMessage::~EditPropertyMessage()
{
}

void EditPropertyMessage::process()
{
	int coef = 1;
	if (!mInc)
		coef = -1;

	// get the property ID
	switch (mID)
	{
	case 0:
		gpGameApp->getPlayer()->getUnit()->changeMaxVel(coef);
		break;
	case 1:
		gpGameApp->getEnemyManager()->setVel(gpGameApp->getEnemyManager()->getVel() + coef);
		break;
	case 2:
		gpGameApp->getEnemyManager()->setSpawnTime(gpGameApp->getEnemyManager()->getSpawnTime() + coef);
		break;
	case 3:
		gpGameApp->getEnemyManager()->setStepReset(gpGameApp->getEnemyManager()->getStepReset() + coef);
		break;
	case 4:
		gpGameApp->getPlayer()->setInvincible(!gpGameApp->getPlayer()->getInvincible());
		break;

	default: return;
		break;
	}
}