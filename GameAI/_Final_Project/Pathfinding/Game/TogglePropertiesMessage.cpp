#include "TogglePropertiesMessage.h"
#include "GameApp.h"
#include "UI.h"

TogglePropertiesMessage::TogglePropertiesMessage()
:GameMessage(TOGGLE_PROPERTIES_MESSAGE)
{
}

TogglePropertiesMessage::~TogglePropertiesMessage()
{
}

void TogglePropertiesMessage::process()
{
	gpGameApp->getUI()->toggleProperties();
}