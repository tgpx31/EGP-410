#ifndef CHANGE_CURRENT_PROPERTY_H
#define CHANGE_CURRENT_PROPERTY_H

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

#endif