#include "SetPlayerLocationMessage.h"
#include "GameApp.h"
#include "Player.h"

SetPlayerPositionMessage::SetPlayerPositionMessage(Vector2D position) : GameMessage (SET_PLAYER_POSITION_MESSAGE)
{
	mPosition = position;
}

SetPlayerPositionMessage::~SetPlayerPositionMessage()
{
}

void SetPlayerPositionMessage::process()
{
	gpGameApp->getPlayer()->setPosition(mPosition);
}
