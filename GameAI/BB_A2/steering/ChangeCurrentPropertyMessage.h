#pragma once

#include "GameMessage.h"

class ChangeCurrentPropertyMessage : public GameMessage
{
private:
	bool mInc;
	float mAmount;
public:
	ChangeCurrentPropertyMessage(bool isInc, float amount);
	~ChangeCurrentPropertyMessage();

	void process();
};