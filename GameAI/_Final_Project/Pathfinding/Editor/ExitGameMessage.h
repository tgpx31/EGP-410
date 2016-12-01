#pragma once

#include "GameMessage.h"

class ExitGameMessage : public GameMessage
{
private:

public:
	ExitGameMessage();
	~ExitGameMessage();

	void process();
};