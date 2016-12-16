#include "PlayerDeathMessage.h"
#include "GameApp.h"
#include "SoundSystem.h"

PlayerDeathMessage::PlayerDeathMessage()
:GameMessage(PLAYER_DEATH_MESSAGE)
{
}

PlayerDeathMessage::~PlayerDeathMessage()
{
}

void PlayerDeathMessage::process()
{
	gpGameApp->getSS()->playSound(4);
	gpGameApp->stopUpdating();
	// stop updating player and enemies
	// display the score on the screen
	std::cout << gpGameApp->getScore() << std::endl;
}
