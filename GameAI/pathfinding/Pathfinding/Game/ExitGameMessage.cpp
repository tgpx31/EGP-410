#include "ExitGameMessage.h"
#include "GameApp.h"

ExitGameMessage::ExitGameMessage()
:GameMessage(EXIT_GAME_MESSAGE)
{
}

ExitGameMessage::~ExitGameMessage()
{
}

void ExitGameMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if (pGame != NULL)
	{
		pGame->markForExit();
	}
}