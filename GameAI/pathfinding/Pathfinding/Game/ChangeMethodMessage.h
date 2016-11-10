#pragma once

#include "GameMessage.h"

class ChangeMethodMessage : public GameMessage
{
private:
	bool mIsAStar;
public:
	ChangeMethodMessage(bool aStar);
	~ChangeMethodMessage();

	void process();
};