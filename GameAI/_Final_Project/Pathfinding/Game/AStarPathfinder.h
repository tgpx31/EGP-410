#pragma once

#include "GridPathfinder.h"
#include "Defines.h"
#include <vector>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class AStarPathfinder :public GridPathfinder
{
public:
	AStarPathfinder(Graph* pGraph, IDType mapID);
	~AStarPathfinder();

	const Path& findPath(Node* pFrom, Node* pTo);	// make sure to delete the path when you are done!
private:
	float getHeuristic(Node* node, Node* goal);
};