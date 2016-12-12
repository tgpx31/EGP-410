#include "GameMapManager.h"
#include "GameMap.h"

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

void GameMapManager::connectDoors()
{
	std::cout << mMaps.size() << std::endl;
}

void GameMapManager::drawCurrentMap()
{
	mCurrentMap->second->draw();
}
