#include "GameMapManager.h"
#include "GameMap.h"
#include "DoorManager.h"
#include "SpriteManager.h"
#include "Vector2D.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "Door.h"
#include "Grid.h"

#include <ctime>
#include <vector>
#include <algorithm>

GameMapManager::GameMapManager()
{
	mCurrentMap = mMaps.end();
}

GameMapManager::~GameMapManager()
{
	std::map<IDType, GameMap*>::iterator iter;

	for (iter = mMaps.begin(); iter != mMaps.end(); iter++)
	{
		delete iter->second;
	}
}

void GameMapManager::addMap(IDType id, GameMap* map)
{
	std::map<IDType, GameMap*>::iterator iter;

	iter = mMaps.find(id);

	if (iter != mMaps.end())
	{
		delete iter->second;
		mMaps.erase(id);
	}

	mMaps[id] = map;

	if (mCurrentMap == mMaps.end())
	{
		mCurrentMap = mMaps.find(id);
	}
}

void GameMapManager::loadMap(IDType id, std::string filename)
{
	std::map<IDType, GameMap*>::iterator iter;

	iter = mMaps.find(id);

	if (iter != mMaps.end())
	{
		delete iter->second;
		mMaps.erase(id);
	}

	GameMap* pGameMap = new GameMap(filename);
	pGameMap->init();
	mMaps[id] = pGameMap;

	if (mCurrentMap == mMaps.end())
	{
		mCurrentMap = mMaps.find(id);
	}
}

GameMap* GameMapManager::getMap(const IDType& id)
{
	std::map<IDType, GameMap*>::iterator iter;

	iter = mMaps.find(id);

	if (iter != mMaps.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

GameMap* GameMapManager::getCurrentMap()
{
	if (mCurrentMap != mMaps.end())
	{
		return mCurrentMap->second;
	}
	else
	{
		return nullptr;
	}
	
}

void GameMapManager::setCurrentMap(const IDType & id)
{	
	if (mMaps.find(id) != mMaps.end())
	{
		mCurrentMap = mMaps.find(id);
	}
}

void GameMapManager::update()
{
	mCurrentMap->second->update();
}

void GameMapManager::connectDoors()
{
	std::cout << "Generating map. Connecting doors." << std::endl;

	Vector2D top(gpGame->getGraphicsSystem()->getWidth() / 2 - GRID_SQUARE_SIZE, 0);
	Vector2D bot(gpGame->getGraphicsSystem()->getWidth() / 2 - GRID_SQUARE_SIZE, gpGame->getGraphicsSystem()->getHeight() - GRID_SQUARE_SIZE);
	Vector2D left(0, gpGame->getGraphicsSystem()->getHeight() / 2 - GRID_SQUARE_SIZE);
	Vector2D right(gpGame->getGraphicsSystem()->getWidth() - GRID_SQUARE_SIZE, gpGame->getGraphicsSystem()->getHeight() / 2 - GRID_SQUARE_SIZE);

	srand(time(NULL));

	/*
		Map layout, using indicies of maps vector	
		[ 
		0, 1
		2, 3 
		]

		index 0 == top left room
		index 1 == top right room
		index 2 == bottom left room
		index 3 == bottom right room
	*/

	std::vector<int> maps = { 0, 1, 2, 3 };	//Vector of map ids
	std::random_shuffle(maps.begin(), maps.end());
	
	for (int i = 0; i < 4; i++)
	{
		std::cout << maps[i] << ", ";
	}
	std::cout << std::endl;
	Sprite* pSprite = gpGame->getSpriteManager()->getSprite(DOOR);

	//Link top left room and top right room
	Door* pDoorOne = new Door(right, pSprite); //top left room door
	Door* pDoorTwo = new Door(left, pSprite); //top right room door

	pDoorOne->setMapTo(maps[1]);
	pDoorTwo->setMapTo(maps[0]);

	pDoorOne->setConnectedDoor(pDoorTwo);
	pDoorTwo->setConnectedDoor(pDoorOne);

	mMaps[maps[0]]->getDoorManager()->addDoor(0, pDoorOne);
	mMaps[maps[1]]->getDoorManager()->addDoor(0, pDoorTwo);

	mMaps[maps[0]]->getGrid()->setValueAtPixelXY(right.getX(), right.getY(), CLEAR_VALUE);
	mMaps[maps[1]]->getGrid()->setValueAtPixelXY(left.getX(), left.getY(), CLEAR_VALUE);

	//Link top right room and bottom right room
	pDoorOne = new Door(bot, pSprite); //top right room door
	pDoorTwo = new Door(top, pSprite); //bottom right room door

	pDoorOne->setMapTo(maps[3]);
	pDoorTwo->setMapTo(maps[1]);

	pDoorOne->setConnectedDoor(pDoorTwo);
	pDoorTwo->setConnectedDoor(pDoorOne);

	mMaps[maps[1]]->getDoorManager()->addDoor(1, pDoorOne);
	mMaps[maps[3]]->getDoorManager()->addDoor(0, pDoorTwo);

	mMaps[maps[1]]->getGrid()->setValueAtPixelXY(bot.getX(), bot.getY(), CLEAR_VALUE);
	mMaps[maps[3]]->getGrid()->setValueAtPixelXY(top.getX(), top.getY(), CLEAR_VALUE);

	//Link bottom right room and bottom left room
	pDoorOne = new Door(left, pSprite); //bottom right room door
	pDoorTwo = new Door(right, pSprite); //bottom left room door

	pDoorOne->setMapTo(maps[2]);
	pDoorTwo->setMapTo(maps[3]);

	pDoorOne->setConnectedDoor(pDoorTwo);
	pDoorTwo->setConnectedDoor(pDoorOne);

	mMaps[maps[3]]->getDoorManager()->addDoor(1, pDoorOne);
	mMaps[maps[2]]->getDoorManager()->addDoor(0, pDoorTwo);

	mMaps[maps[3]]->getGrid()->setValueAtPixelXY(left.getX(), left.getY(), CLEAR_VALUE);
	mMaps[maps[2]]->getGrid()->setValueAtPixelXY(right.getX(), right.getY(), CLEAR_VALUE);

	//Link bottom left room and top left room
	pDoorOne = new Door(top, pSprite); //bottom left room door
	pDoorTwo = new Door(bot, pSprite); //top left room door

	pDoorOne->setMapTo(maps[0]);
	pDoorTwo->setMapTo(maps[2]);

	pDoorOne->setConnectedDoor(pDoorTwo);
	pDoorTwo->setConnectedDoor(pDoorOne);

	mMaps[maps[2]]->getDoorManager()->addDoor(1, pDoorOne);
	mMaps[maps[0]]->getDoorManager()->addDoor(1, pDoorTwo);

	mMaps[maps[2]]->getGrid()->setValueAtPixelXY(top.getX(), top.getY(), CLEAR_VALUE);
	mMaps[maps[0]]->getGrid()->setValueAtPixelXY(bot.getX(), bot.getY(), CLEAR_VALUE);

	setCurrentMap(maps[0]); //set current map to be top left corner
}

void GameMapManager::drawCurrentMap()
{
	mCurrentMap->second->draw();
}
