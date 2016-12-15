#pragma once

#include "Trackable.h"
#include "Defines.h"
#include <string>

class Graph;
class Grid;
class GridVisualizer;
class GridGraph;
class CandyManager;
class DoorManager;

const int GRID_SQUARE_SIZE = 32;

class GameMap : public Trackable
{
private:
	Grid* mpGrid;
	GridGraph* mpGridGraph;
	GridVisualizer* mpGridVisualizer;
	
	DoorManager* mpDoorManager;
	CandyManager* mpCandyManager;

	std::string mFilename;

public:
	GameMap(std::string filename);
	~GameMap();

	inline Grid* getGrid() const { return mpGrid; };
	inline GridGraph* getGridGraph() { return mpGridGraph; };
	inline DoorManager* getDoorManager() { return mpDoorManager; };
	inline CandyManager* getCandyManager() { return mpCandyManager; };

	void init(IDType mapID);
	void update(float time);
	void draw();
};