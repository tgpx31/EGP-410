#pragma once

#include "Trackable.h"
#include <string>

class Grid;
class GridVisualizer;
class GridGraph;
class UnitManager;

class GameMap : public Trackable
{
private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph;
	
	UnitManager* mpCoinManager;
	UnitManager* mpDoorManager;
	UnitManager* mpCandyManager;

	std::string mFilename;

public:
	GameMap(std::string filename);
	~GameMap();

	inline Grid* getGrid() const { return mpGrid; };

	void init();
	void update();
	void draw();
};