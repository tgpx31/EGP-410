#pragma once

#include "GameMessage.h"

class ChangeMapMessage : public GameMessage
{
private:
	int mMapID;

public:
	ChangeMapMessage(int mapID);
	~ChangeMapMessage();

	void process();
};