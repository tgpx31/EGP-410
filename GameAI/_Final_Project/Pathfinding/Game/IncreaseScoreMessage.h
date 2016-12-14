#pragma once

#include "GameMessage.h"

class IncreaseScoreMessage : public GameMessage
{
private:
	int mValue;
public:
	IncreaseScoreMessage(int val) :GameMessage(INCREASE_SCORE_MESSAGE), mValue(val) {};
	~IncreaseScoreMessage();

	void process();
};