#pragma once

#include "Trackable.h"
#include <string>

class Grid;
class GridVisualizer;
class GridGraph;
class UnitManager;
class DoorManager;

const int GRID_SQUARE_SIZE = 32;

class GameMap : public Trackable
{
private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph;
	
	DoorManager* mpDoorManager;
	UnitManager* mpCandyManager;

	std::string mFilename;

public:
	GameMap(std::string filename);
	~GameMap();

	inline Grid* getGrid() const { return mpGrid; };
	inline DoorManager* getDoorManager() { return mpDoorManager; };

	void init();
	void update();
	void draw();
};