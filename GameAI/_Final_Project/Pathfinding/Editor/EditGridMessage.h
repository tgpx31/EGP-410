#pragma once

#include "GameMessage.h"

class EditGridMessage : public GameMessage
{
private:
	int mX;
	int mY;
	int mGridValue;

public:
	EditGridMessage(int x, int y, int gridValue);
	~EditGridMessage();

	void process();
};