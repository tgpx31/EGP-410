#include "GameMap.h"
#include "Grid.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "GameApp.h"
#include "Game.h"
#include "GridVisualizer.h"

#include <fstream>

GameMap::GameMap(std::string filename)
{
	mFilename = filename;
	
	mpGrid = new Grid(gpGame->getGraphicsSystem()->getWidth(), gpGame->getGraphicsSystem()->getHeight(), 32);

	std::ifstream fin;
	fin.open(mFilename);
	mpGrid->load(fin);
	fin.close();
	
	mpGridVisualizer = new GridVisualizer(mpGrid);

	mpCoinManager = new UnitManager();

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

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpCoinManager;
	mpCoinManager = NULL;
}

void GameMap::update()
{
	/* Check coins for collisions with player, update as necessary */
}

void GameMap::draw()
{
	mpGridVisualizer->draw(*gpGame->getGraphicsSystem()->getBackBuffer());
	mpCoinManager->draw(gpGame->getGraphicsSystem());
}