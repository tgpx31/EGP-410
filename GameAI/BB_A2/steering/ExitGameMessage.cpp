#include "ExitGameMessage.h"
#include "Game.h"

ExitGameMessage::ExitGameMessage()
:GameMessage(EXIT_GAME_MESSAGE)
{
}

ExitGameMessage::~ExitGameMessage()
{
}

void ExitGameMessage::process()
{
	gpGame->setShouldExit(true);
	std::cout << "\nEXIT GAME MESSAGE\n";
}