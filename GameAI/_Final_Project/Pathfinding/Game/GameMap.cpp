#include "GameMap.h"
#include "Grid.h"
#include "CandyManager.h"
#include "DoorManager.h"
#include "SpriteManager.h"
#include "GameApp.h"
#include "Game.h"
#include "GridVisualizer.h"
#include "GridGraph.h"
#include "AddEnemyMessage.h"
#include "GameMessageManager.h"

#include <fstream>
#include <ctime>



GameMap::GameMap(std::string filename)
{
	mFilename = filename;
	mpGrid = NULL;
	mpGridGraph = NULL;
	mpGridVisualizer = NULL;
	mpDoorManager = NULL;
	mpCandyManager = NULL;

	srand(time(NULL));
}

GameMap::~GameMap()
{
	delete mpGrid;
	mpGrid = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpDoorManager;
	mpDoorManager = NULL;

	delete mpCandyManager;
	mpCandyManager = NULL;
}

void GameMap::init()
{
	std::cout << "Loading map " << mFilename << std::endl;
	
	mpGrid = new Grid(gpGame->getGraphicsSystem()->getWidth(), gpGame->getGraphicsSystem()->getHeight(), GRID_SQUARE_SIZE);

	std::ifstream fin;
	fin.open(mFilename);
	mpGrid->load(fin);
	fin.close();

	mpGridGraph = new GridGraph(mpGrid);
	mpGridGraph->init();

	mpGridVisualizer = new GridVisualizer(mpGrid);

	mpDoorManager = new DoorManager();
	mpCandyManager = new CandyManager();
}

void GameMap::update(float time)
{
	mpDoorManager->update();
	mpCandyManager->update(time);
}

void GameMap::draw()
{
	mpGridVisualizer->draw(*gpGame->getGraphicsSystem()->getBackBuffer());
	mpDoorManager->draw();
	mpCandyManager->draw();
}