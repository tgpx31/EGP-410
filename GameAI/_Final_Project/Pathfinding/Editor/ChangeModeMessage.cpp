#include "ChangeModeMessage.h"

ChangeModeMessage::ChangeModeMessage(EDIT_MODES mode) : GameMessage(CHANGE_MODE_MESSAGE)
{
	mMode = mode;
}

ChangeModeMessage::~ChangeModeMessage()
{
}

void ChangeModeMessage::process()
{
	switch (mMode)
	{
	case WALL:
		std::cout << "Now placing WALL" << std::endl;
		break;
	case ENEMY_SPAWN:
		std::cout << "Now placing ENEMY_SPAWN" << std::endl;
		break;
	case PLAYER_SPAWN:
		std::cout << "Now placing PLAYER_SPAWN" << std::endl;
		break;
	case CANDY:
		std::cout << "Now placing CANDY" << std::endl;
		break;
	}
}