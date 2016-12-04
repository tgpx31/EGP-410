#pragma once

#include "GameMessage.h"

class ToggleHelpMessage : public GameMessage
{
private:

public:
	ToggleHelpMessage();
	~ToggleHelpMessage();

	void process();
};