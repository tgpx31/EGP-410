#pragma once

#include "Pathfinder.h"
#include "Defines.h"

class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder:public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder( GridGraph* pGraph , IDType mapID);
	virtual ~GridPathfinder();

	virtual const Path& findPath( Node* pFrom, Node* pTo ) = 0;
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization( Grid* pGrid, GraphicsBuffer* pDest, bool isAStar);
	void drawLineToNodes(Node* node);
	void setGraph(GridGraph* pGraph);
	
	inline void clearFinalPath() { mFinalPath.clear(); };
	inline std::vector<Node*> getFinalPath() { return mFinalPath; };
protected:
	std::vector<Node*> mVisitedNodes;
	GridVisualizer* mpVisualizer;

	std::vector<Node*> mFinalPath;
#endif
	IDType mMapID;
	double mTimeElapsed;
};