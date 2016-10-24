#ifndef EXIT_GAME_MESSAGE_H
#define EXIT_GAME_MESSAGE_H

#include "GameMessage.h"

class ExitGameMessage : public GameMessage
{
private:

public:
	ExitGameMessage();
	~ExitGameMessage();

	void process();
};

#endif