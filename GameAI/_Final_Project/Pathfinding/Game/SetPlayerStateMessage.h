#pragma once

#include "GameMessage.h"

enum PlayerMovementState;

class SetPlayerStateMessage : public GameMessage
{
private:
	PlayerMovementState mState;

public:
	SetPlayerStateMessage(PlayerMovementState state);
	~SetPlayerStateMessage();

	void process();
};