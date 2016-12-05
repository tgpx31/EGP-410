#include "ToggleHelpMessage.h"
#include "Editor.h"

ToggleHelpMessage::ToggleHelpMessage() : GameMessage(TOGGLE_HELP_MESSAGE)
{
}

ToggleHelpMessage::~ToggleHelpMessage()
{
}

void ToggleHelpMessage::process()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	pEditor->setShowHelp(!pEditor->getShowHelp());
	std::cout << "Toggling HELP" << std::endl;
}