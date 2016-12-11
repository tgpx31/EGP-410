#include "SetPlayerStateMessage.h"
#include "GameApp.h"
#include "Player.h"

SetPlayerStateMessage::SetPlayerStateMessage(PlayerMovementState state) : GameMessage(SET_PLAYER_STATE_MESSAGE)
{
	mState = state;
}

SetPlayerStateMessage::~SetPlayerStateMessage()
{
}

void SetPlayerStateMessage::process()
{
	gpGameApp->getPlayer()->setState(mState);
}
