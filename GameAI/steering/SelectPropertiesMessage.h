#ifndef SELECT_PROPERTIES_MESSAGE_H
#define SELECT_PROPERTIES_MESSAGE_H

#include "GameMessage.h"
#include "Game.h"

class SelectPropertiesMessage : public GameMessage
{
private:
	GameProperties mProperty;
public:
	SelectPropertiesMessage(const GameProperties& prop);
	~SelectPropertiesMessage();

	void process();
};

#endif