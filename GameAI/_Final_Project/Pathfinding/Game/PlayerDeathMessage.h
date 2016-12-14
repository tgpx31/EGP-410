#pragma once

#include "GameMessage.h"

class PlayerDeathMessage : public GameMessage
{
private:

public:
	PlayerDeathMessage();
	~PlayerDeathMessage();

	void process();
};