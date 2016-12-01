#pragma once

#include "GameMessage.h"

class SaveMessage : public GameMessage
{
private:

public:
	SaveMessage();
	~SaveMessage();

	void process();
};