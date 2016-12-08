#include "GameMap.h"
#include "Grid.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "GameApp.h"

#include <fstream>

GameMap::GameMap(std::string filename)
{
	mFilename = filename;
	
	std::ifstream fin;
	fin.open(mFilename);
	mpGrid->load(fin);
	fin.close();

	int numValues = mpGrid->getNumValues();

	for (int i = 0; i < numValues; i++)
	{
		if (mpGrid->getValueAtIndex(i) == CLEAR_VALUE)
		{
			//Create new coin unit at location of i
			mpCoinManager->addUnit(mpGrid->getULCornerOfSquare(i), gpGame->getSpriteManager()->getSprite(COIN));
		}
	}
}

GameMap::~GameMap()
{
	delete mpGrid;
	mpGrid = NULL;

	delete mpCoinManager;
	mpCoinManager = NULL;
}
