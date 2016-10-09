#include "SelectPropertiesMessage.h"
//#include "Game.h"
#include "Properties.h"

SelectPropertiesMessage::SelectPropertiesMessage(const GameProperties& prop)
:GameMessage(SELECT_PROPERTIES_MESSAGE)
,mProperty(prop)
{
}

SelectPropertiesMessage::~SelectPropertiesMessage()
{
}

void SelectPropertiesMessage::process()
{
	if (gpGame->getProperties()->getActive())
	{
		gpGame->getProperties()->setCurrentProperty(mProperty);
		std::cout << "\nCurrent Property: " << mProperty << std::endl;
	}
}
