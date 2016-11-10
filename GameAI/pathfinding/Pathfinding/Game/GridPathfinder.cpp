#include <allegro5/allegro.h>
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "Game.h"
#include "GraphicsBuffer.h"

GridPathfinder::GridPathfinder( GridGraph* pGraph )
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
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
	if (mpVisualizer == NULL)
	{
		mpVisualizer = new GridVisualizer(pGrid);
	}
	else
	{
		mpVisualizer->clear();
	}

	static ALLEGRO_COLOR pathColor;

	if (!isAStar)
		pathColor = al_map_rgb( 255, 64, 64 );
	else
		pathColor = al_map_rgb(64, 64, 255);

	static ALLEGRO_COLOR startColor = al_map_rgb(1, 128, 255);
	static ALLEGRO_COLOR stopColor = al_map_rgb(1, 255, 128);

	unsigned int numNodes = mPath.getNumNodes();
	ALLEGRO_COLOR currentPathColor = pathColor;

	if (numNodes > 0)
	{
		for (unsigned int i = 1; i < numNodes-1; i++)
		{
			mpVisualizer->addColor(mPath.peekNode(i)->getId(), currentPathColor);
			float lerpVal = lerp( i, 0, numNodes );

			if (!isAStar)
				currentPathColor.r = 1.0f - lerpVal;
			else if (isAStar)
				currentPathColor.b = 1.0f - lerpVal;
		}

		//add beginning and ending color
		mpVisualizer->addColor(mPath.peekNode(0)->getId(), stopColor);
		mpVisualizer->addColor(mPath.peekNode(numNodes - 1)->getId(), startColor);
	}

	mpVisualizer->draw(*pDest);
}
#endif