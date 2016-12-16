#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "Grid.h"
#include "GraphicsBuffer.h"
#include "Vector2D.h"
#include "GameApp.h"

#include "GameMapManager.h"
#include "GameMap.h"

GridPathfinder::GridPathfinder( GridGraph* pGraph , IDType mapID)
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
,mMapID(mapID)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization( Grid* pGrid, GraphicsBuffer* pDest, bool isAStar )
{
	for (int i = 0; i < mFinalPath.size(); ++i)
	{
		// Draw a line
		drawLineToNodes(mFinalPath[i]);
	}
}
void GridPathfinder::drawLineToNodes(Node * node)
{	
	al_draw_line(
		gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getULCornerOfSquare(node->getId()).getX() + gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareSize() / 2,
		gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getULCornerOfSquare(node->getId()).getY() + gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareSize() / 2,
		gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getULCornerOfSquare(node->getPrevNode()).getX() + gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareSize() / 2,
		gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getULCornerOfSquare(node->getPrevNode()).getY() + gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareSize() / 2,
		al_map_rgb(255, 255, 255), 
		5);
}
#endif