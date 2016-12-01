#include "SaveMessage.h"
#include "Editor.h"

#include <iostream>
#include <fstream>

SaveMessage::SaveMessage() : GameMessage(SAVE_MESSAGE)
{
}

SaveMessage::~SaveMessage()
{
}

void SaveMessage::process()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);

	std::ofstream theStream(pEditor->getFilename());
	pEditor->saveGrid(theStream);
	theStream.close();
	
	std::cout << "Grid saved!\n";
	
}