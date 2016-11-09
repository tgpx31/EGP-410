#pragma once

#include "GameMessage.h"

class DeleteUnitMessage : public GameMessage
{
private:

public:
	DeleteUnitMessage();
	~DeleteUnitMessage();

	void process();
};