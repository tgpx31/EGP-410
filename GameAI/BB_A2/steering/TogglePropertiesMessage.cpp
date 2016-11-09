#include "TogglePropertiesMessage.h"
#include "Game.h"
#include "Properties.h"

TogglePropertiesMessage::TogglePropertiesMessage()
	:GameMessage(TOGGLE_PROPERTIES_MESSAGE)
{
}

TogglePropertiesMessage::~TogglePropertiesMessage()
{
}

void TogglePropertiesMessage::process()
{
	gpGame->getProperties()->toggleActive();
	std::cout << "\nPROPERTIES TOGGLED\n";
}
