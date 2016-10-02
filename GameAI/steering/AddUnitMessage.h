#pragma once

#include "GameMessage.h"
#include "Vector2D.h"
#include "Game.h"

class AddUnitMessage : public GameMessage
{
private:
	Behavior mBehavior;
	Vector2D mPos;

public:
	AddUnitMessage(const Vector2D& pos, const Behavior& behavior);
	~AddUnitMessage();

	void process();
};