#ifndef DELETE_UNIT_MESSAGE_H
#define DELETE_UNIT_MESSAGE_H

#include "GameMessage.h"

class DeleteEnemyMessage : public GameMessage
{
private:

public:
	DeleteEnemyMessage();
	~DeleteEnemyMessage();

	void process();
};

#endif