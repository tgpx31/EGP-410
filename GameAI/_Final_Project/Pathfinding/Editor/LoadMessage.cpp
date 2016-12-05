#pragma once

#include "LoadMessage.h"
#include "Editor.h"
#include "GridVisualizer.h"

#include <fstream>
#include <iostream>

LoadMessage::LoadMessage() : GameMessage(LOAD_MESSAGE)
{
}

LoadMessage::~LoadMessage()
{
}

void LoadMessage::process()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);

	std::ifstream theStream(pEditor->getFilename());
	pEditor->loadGrid(theStream);
	theStream.close();

	pEditor->getGridVisualizer()->setModified();

	std::cout << "Loaded map from " << pEditor->getFilename() << std::endl;
}