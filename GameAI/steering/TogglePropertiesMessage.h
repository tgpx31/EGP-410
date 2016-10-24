#ifndef TOGGLE_PROPERTIES_MESSAGE_H
#define TOGGLE_PROPERTIES_MESSAGE_H

#include "GameMessage.h"

class TogglePropertiesMessage : public GameMessage
{
private:

public:
	TogglePropertiesMessage();
	~TogglePropertiesMessage();

	void process();
};

#endif