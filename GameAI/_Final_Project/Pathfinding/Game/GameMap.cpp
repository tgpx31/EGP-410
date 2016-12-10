#include "GameMap.h"
#include "Grid.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "GameApp.h"
#include "Game.h"
#include "GridVisualizer.h"
#include "GridGraph.h"

#include <fstream>

GameMap::GameMap(std::string filename)
{
	mFilename = filename;
	mpGrid = NULL;
	mpGridGraph = NULL;
	mpGridVisualizer = NULL;
	mpCoinManager = NULL;
	mpDoorManager = NULL;
	mpCandyManager = NULL;
}

GameMap::~GameMap()
{
	delete mpGrid;
	mpGrid = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpCoinManager;
	mpCoinManager = NULL;

	delete mpDoorManager;
	mpDoorManager = NULL;

	delete mpCandyManager;
	mpCandyManager = NULL;
}

void GameMap::init()
{
	mpGrid = new Grid(gpGame->getGraphicsSystem()->getWidth(), gpGame->getGraphicsSystem()->getHeight(), 32);

	std::ifstream fin;
	fin.open(mFilename);
	mpGrid->load(fin);
	fin.close();

	mpGridGraph = new GridGraph(mpGrid);
	mpGridGraph->init();

	mpGridVisualizer = new GridVisualizer(mpGrid);

	mpCoinManager = new UnitManager();
	mpDoorManager = new UnitManager();
	mpCandyManager = new UnitManager();

	int numValues = mpGrid->getNumValues();

	for (int i = 0; i < numValues; i++)
	{
		int value = mpGrid->getValueAtIndex(i);

		if (value == COIN_VALUE)
		{
			//Create new coin unit at location of i
			mpCoinManager->addUnit(mpGrid->getULCornerOfSquare(i), gpGame->getSpriteManager()->getSprite(COIN));
		}
		else if (value == DOOR_VALUE)
		{
			mpDoorManager->addUnit(mpGrid->getULCornerOfSquare(i), gpGame->getSpriteManager()->getSprite(DOOR));
		}
		else if (value == CANDY_VALUE)
		{
			mpCandyManager->addUnit(mpGrid->getULCornerOfSquare(i), gpGame->getSpriteManager()->getSprite(CANDY));
		}
	}
}

void GameMap::update()
{
	/* Check coins for collisions with player, update as necessary */
}

void GameMap::draw()
{
	mpGridVisualizer->draw(*gpGame->getGraphicsSystem()->getBackBuffer());
	mpCoinManager->draw(gpGame->getGraphicsSystem());
	mpDoorManager->draw(gpGame->getGraphicsSystem());
	mpCandyManager->draw(gpGame->getGraphicsSystem());
}