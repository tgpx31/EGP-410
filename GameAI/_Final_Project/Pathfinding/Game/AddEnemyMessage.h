#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class AddEnemyMessage : public GameMessage
{
private:
	Vector2D mPos;
public:
	AddEnemyMessage(const Vector2D& pos);
	~AddEnemyMessage();

	void process();
};