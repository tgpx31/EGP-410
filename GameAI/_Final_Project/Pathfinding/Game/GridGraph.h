#pragma once

#include "Graph.h"
#include "Defines.h"

class Grid;

class GridGraph:public Graph
{
public:
	GridGraph( Grid* pGrid );
	virtual ~GridGraph();

	void setGrid( Grid* pGrid ) { mpGrid = pGrid; };
	void init(IDType mapID);

private:
	Grid* mpGrid;
};