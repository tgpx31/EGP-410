#pragma once

#include "Trackable.h"
#include "Defines.h"

#include <map>
#include <string>

class GameMap;

class GameMapManager : public Trackable
{
private:
	std::map<IDType, GameMap*> mMaps;
	std::map<IDType, GameMap*>::iterator mCurrentMap;

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
	void connectDoors();
	void drawCurrentMap();
};