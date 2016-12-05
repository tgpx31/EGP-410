#include "ChangeModeMessage.h"
#include "Editor.h"

ChangeModeMessage::ChangeModeMessage(int value) : GameMessage(CHANGE_MODE_MESSAGE)
{
	mValue = value;
}

ChangeModeMessage::~ChangeModeMessage()
{
}

void ChangeModeMessage::process()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	pEditor->setEditGridValue(mValue);

	std::cout << "Edit value set to " << mValue << std::endl;
}