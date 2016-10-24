#ifndef PLAYER_MOVETO_MESSAGE_H
#define PLAYER_MOVETO_MESSAGE_H

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class PlayerMoveToMessage:public GameMessage
{
public:
	PlayerMoveToMessage( const Vector2D& pos );
	~PlayerMoveToMessage();

	void process();

private:
	Vector2D mPos;
};

#endif