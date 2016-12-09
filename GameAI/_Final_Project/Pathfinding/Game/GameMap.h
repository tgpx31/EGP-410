#pragma once

#include "Trackable.h"
#include <string>

class Grid;
class GridVisualizer;
class UnitManager;

class GameMap : public Trackable
{
private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	UnitManager* mpCoinManager;
	std::string mFilename;

public:
	GameMap(std::string filename);
	~GameMap();

	inline Grid* getGrid() const { return mpGrid; };

	void update();
	void draw();
};