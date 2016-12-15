#include "TogglePlayerInvincibilityMessage.h"
#include "Player.h"
#include "GameApp.h"

TogglePlayerIvincibilityMessage::TogglePlayerIvincibilityMessage() : GameMessage(TOGGLE_PLAYER_INVINCIBILITY_MESSAGE)
{
}

TogglePlayerIvincibilityMessage::~TogglePlayerIvincibilityMessage()
{
}

void TogglePlayerIvincibilityMessage::process()
{
	gpGameApp->getPlayer()->setInvincible(!gpGameApp->getPlayer()->getInvincible());

	if (gpGameApp->getPlayer()->getInvincible())
	{
		std::cout << "Player invincibility TRUE" << std::endl;
	}
	else
	{
		std::cout << "Player invincibility FALSE" << std::endl;
	}
}
