#pragma once

#include "GameMessage.h"

class TogglePlayerIvincibilityMessage : public GameMessage
{
public:
	TogglePlayerIvincibilityMessage(bool invincible);
	~TogglePlayerIvincibilityMessage();

private:
	bool mInvincible;

	void process();
};