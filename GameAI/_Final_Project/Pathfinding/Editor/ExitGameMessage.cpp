#include "ExitGameMessage.h"
#include "Editor.h"

ExitGameMessage::ExitGameMessage()
	:GameMessage(EXIT_GAME_MESSAGE)
{
}

ExitGameMessage::~ExitGameMessage()
{
}

void ExitGameMessage::process()
{
		gpGame->markForExit();
}