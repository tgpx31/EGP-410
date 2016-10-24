#ifndef DELETE_UNIT_MESSAGE_H
#define DELETE_UNIT_MESSAGE_H

#include "GameMessage.h"

class DeleteUnitMessage : public GameMessage
{
private:

public:
	DeleteUnitMessage();
	~DeleteUnitMessage();

	void process();
};

#endif