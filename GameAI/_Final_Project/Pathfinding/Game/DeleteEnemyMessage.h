#pragma once

#include "GameMessage.h"

class DeleteEnemyMessage : public GameMessage
{
private:

public:
	DeleteEnemyMessage();
	~DeleteEnemyMessage();

	void process();
};
