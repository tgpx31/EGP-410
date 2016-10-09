#pragma once

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