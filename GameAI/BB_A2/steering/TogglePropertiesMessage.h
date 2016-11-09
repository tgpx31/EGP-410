#pragma once

#include "GameMessage.h"

class TogglePropertiesMessage : public GameMessage
{
private:

public:
	TogglePropertiesMessage();
	~TogglePropertiesMessage();

	void process();
};