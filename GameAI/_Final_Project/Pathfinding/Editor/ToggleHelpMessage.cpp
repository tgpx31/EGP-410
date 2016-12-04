#include "ToggleHelpMessage.h"

ToggleHelpMessage::ToggleHelpMessage() : GameMessage(TOGGLE_HELP_MESSAGE)
{
}

ToggleHelpMessage::~ToggleHelpMessage()
{
}

void ToggleHelpMessage::process()
{
	std::cout << "Toggling HELP" << std::endl;
}