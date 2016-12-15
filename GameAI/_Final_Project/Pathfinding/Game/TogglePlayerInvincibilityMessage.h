#pragma once

#include "GameMessage.h"

class TogglePlayerIvincibilityMessage : public GameMessage
{
public:
	TogglePlayerIvincibilityMessage();
	~TogglePlayerIvincibilityMessage();

private:
	void process();
};