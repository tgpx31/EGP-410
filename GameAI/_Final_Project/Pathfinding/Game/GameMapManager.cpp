#include "GameMapManager.h"
#include "GameMap.h"

GameMapManager::GameMapManager()
{
	mCurrentMap = mpMaps.end();
}

GameMapManager::~GameMapManager()
{
	std::map<IDType, GameMap*>::iterator iter;

	for (iter = mpMaps.begin(); iter != mpMaps.end(); iter++)
	{
		delete iter->second;
	}
}

void GameMapManager::addMap(IDType id, GameMap* map)
{
	std::map<IDType, GameMap*>::iterator iter;

	iter = mpMaps.find(id);

	if (iter != mpMaps.end())
	{
		delete iter->second;
		mpMaps.erase(id);
	}

	mpMaps[id] = map;

	if (mCurrentMap == mpMaps.end())
	{
		mCurrentMap = mpMaps.find(id);
	}
}

void GameMapManager::loadMap(IDType id, std::string filename)
{
	std::map<IDType, GameMap*>::iterator iter;

	iter = mpMaps.find(id);

	if (iter != mpMaps.end())
	{
		delete iter->second;
		mpMaps.erase(id);
	}

	GameMap* pGameMap = new GameMap(filename);
	pGameMap->init();
	mpMaps[id] = pGameMap;

	if (mCurrentMap == mpMaps.end())
	{
		mCurrentMap = mpMaps.find(id);
	}
}

GameMap* GameMapManager::getMap(const IDType& id)
{
	std::map<IDType, GameMap*>::iterator iter;

	iter = mpMaps.find(id);

	if (iter != mpMaps.end())
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
	if (mCurrentMap != mpMaps.end())
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
	if (mpMaps.find(id) != mpMaps.end())
	{
		mCurrentMap = mpMaps.find(id);
	}
}

void GameMapManager::drawCurrentMap()
{
	mCurrentMap->second->draw();
}
