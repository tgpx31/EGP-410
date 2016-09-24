#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class AddUnitMessage : public GameMessage
{
private:
	bool mSeek;
	Vector2D mPos;

public:
	AddUnitMessage(const Vector2D& pos, const bool& seek);
	~AddUnitMessage();

	void process();
};