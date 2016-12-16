#pragma once

#include "Trackable.h"
#include "Defines.h"

#include <map>
#include <string>
#include <vector>

class GameMap;

class GameMapManager : public Trackable
{
private:
	std::map<IDType, GameMap*> mMaps;
	std::map<IDType, GameMap*>::iterator mCurrentMap;
	std::vector<IDType> mMapLayout;

public:
	GameMapManager();
	~GameMapManager();

	void addMap(IDType id, GameMap* map);
	void loadMap(IDType id, std::string filename);
	
	GameMap* getMap(const IDType& id);
	GameMap* getCurrentMap();
	IDType getCurrentMapID();
	void setCurrentMap(const IDType& id);

	void update(float time);
	void loadMapEntities();
	void placePlayer();
	void connectDoors();
	void drawCurrentMap();
};