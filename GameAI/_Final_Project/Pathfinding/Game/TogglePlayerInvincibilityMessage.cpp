#include "TogglePlayerInvincibilityMessage.h"
#include "Player.h"
#include "GameApp.h"

TogglePlayerIvincibilityMessage::TogglePlayerIvincibilityMessage(bool invincible) : GameMessage(TOGGLE_PLAYER_INVINCIBILITY_MESSAGE)
{
	mInvincible = invincible;
}

TogglePlayerIvincibilityMessage::~TogglePlayerIvincibilityMessage()
{
}

void TogglePlayerIvincibilityMessage::process()
{
	gpGameApp->getPlayer()->setInvincible(mInvincible);

	if (gpGameApp->getPlayer()->getInvincible())
	{
		std::cout << "Player invincibility TRUE" << std::endl;
	}
	else
	{
		std::cout << "Player invincibility FALSE" << std::endl;
	}
}
