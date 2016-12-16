#pragma once

#include "GameMessage.h"
#include "UI.h"

class EditPropertyMessage : public GameMessage
{
private:
	int mID;
	bool mInc;
public:
	EditPropertyMessage(int id, bool inc);
	~EditPropertyMessage();

	void process();
};