#include "ChangeMapMessage.h"
#include "Editor.h"

ChangeMapMessage::ChangeMapMessage(int mapID) : GameMessage(CHANGE_MAP_MESSAGE)
{
	if (mapID < 0)
		mMapID = 0;
	else
		mMapID = mapID;
}

ChangeMapMessage::~ChangeMapMessage()
{
}

void ChangeMapMessage::process()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	pEditor->setCurrentMapID(mMapID);
}