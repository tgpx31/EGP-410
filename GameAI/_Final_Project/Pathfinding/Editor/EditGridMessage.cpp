#pragma once

#include "EditGridMessage.h"
#include "Editor.h"
#include "Grid.h"
#include "GridVisualizer.h"

EditGridMessage::EditGridMessage(int x, int y, int gridValue) : GameMessage(EDIT_GRID_MESSAGE)
{
	mX = x;
	mY = y;
	mGridValue = gridValue;
}

EditGridMessage::~EditGridMessage()
{
}

void EditGridMessage::process()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	pEditor->getGrid()->setValueAtPixelXY(mX, mY, mGridValue);
	pEditor->getGridVisualizer()->setModified();
}
