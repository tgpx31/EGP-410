#pragma once 

#include "GameMessage.h"
#include "Defines.h"

class SetCurrentMapMessage : public GameMessage
{
private:
	IDType mMapID;

public:
	SetCurrentMapMessage(IDType mapID);
	~SetCurrentMapMessage();
	
	void process();
};