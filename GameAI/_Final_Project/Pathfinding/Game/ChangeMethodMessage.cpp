#include "ChangeMethodMessage.h"
#include "GameApp.h"

ChangeMethodMessage::ChangeMethodMessage(bool aStar)
:GameMessage(CHANGE_METHOD_MESSAGE)
,mIsAStar(aStar)
{
}

ChangeMethodMessage::~ChangeMethodMessage()
{
}

void ChangeMethodMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if (pGame != NULL)
	{
		// Set the pathfinding method based on mIsAStar
		//gpGameApp->changeMethod(mIsAStar);
	}
}