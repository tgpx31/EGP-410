#include "SetCurrentMapMessage.h"
#include "GameApp.h"
#include "GameMapManager.h"

SetCurrentMapMessage::SetCurrentMapMessage(IDType mapID) : GameMessage(SET_CURRENT_MAP_MESSAGE)
{
	mMapID = mapID;
}

SetCurrentMapMessage::~SetCurrentMapMessage()
{
}

void SetCurrentMapMessage::process()
{
	gpGameApp->getGameMapManager()->setCurrentMap(mMapID);
}