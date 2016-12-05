#pragma once

#include "GameMessage.h"

class ChangeModeMessage : public GameMessage
{
private:
	int mValue;

public:
	ChangeModeMessage(int value);
	~ChangeModeMessage();

	void process();
};