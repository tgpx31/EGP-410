#pragma once

#include "GameMessage.h"

class LoadMessage : public GameMessage
{
private:

public:
	LoadMessage();
	~LoadMessage();

	void process();
};