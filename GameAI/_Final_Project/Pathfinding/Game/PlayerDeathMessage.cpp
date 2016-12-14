#include "PlayerDeathMessage.h"
#include "GameApp.h"

PlayerDeathMessage::PlayerDeathMessage()
:GameMessage(PLAYER_DEATH_MESSAGE)
{
}

PlayerDeathMessage::~PlayerDeathMessage()
{
}

void PlayerDeathMessage::process()
{
	gpGameApp->stopUpdating();
	// stop updating player and enemies
	// display the score on the screen
	std::cout << gpGameApp->getScore() << std::endl;
}
