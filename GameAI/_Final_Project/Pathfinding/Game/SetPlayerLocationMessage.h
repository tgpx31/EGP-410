#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class SetPlayerPositionMessage : public GameMessage
{
private:
	Vector2D mPosition;

public:
	SetPlayerPositionMessage(Vector2D position);
	~SetPlayerPositionMessage();

	void process();
};