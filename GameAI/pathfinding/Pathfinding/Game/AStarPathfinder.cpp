#include "AStarPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <algorithm>

#include "GameApp.h"
#include "Grid.h"
#include "Vector2D.h"

using namespace std;

AStarPathfinder::AStarPathfinder(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

AStarPathfinder::~AStarPathfinder()
{
}

const Path& AStarPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	list<Node*> nodesToVisit;				// allocate nodes to visit list and place starting node in it
	pFrom->setPrevNode(pFrom->getId());		// it's the start, doesn't come from anywhere
	pFrom->setCostFromStart(pFrom, 0.0f);
	nodesToVisit.push_front(pFrom);		// visit the initial node first

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	mPath.clear();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();

		// Should you be adding it to the path?
		//add Node to Path
		mPath.addNode(pCurrentNode);
		//mVisitedNodes.push_back(pCurrentNode);

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());
		static Node* closestToTarget = NULL;

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i < connections.size(); ++i)
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();
			if (!toNodeAdded &&
				!mPath.containsNode(pTempToNode) &&
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode) == nodesToVisit.end())
			{
				pTempToNode->setPrevNode(pCurrentNode->getId());
				pTempToNode->setCostFromStart(pCurrentNode, connections[i]->getCost());

				// Check your hueristic here
				if (closestToTarget == NULL)
				{
					closestToTarget = pTempToNode;
					nodesToVisit.push_front(closestToTarget);
				}
				// If there is a node that is closer to the target, prioritize that
				else if (std::abs((gpGameApp->getGrid()->getULCornerOfSquare(pTo->getId()) - gpGameApp->getGrid()->getULCornerOfSquare(pTempToNode->getId())).getLength()) <
					     std::abs((gpGameApp->getGrid()->getULCornerOfSquare(pTo->getId()) - gpGameApp->getGrid()->getULCornerOfSquare(closestToTarget->getId())).getLength()))
				{
					closestToTarget = pTempToNode;
					nodesToVisit.push_front(closestToTarget);
				}
				// Otherwise push_back
				else
				{
					nodesToVisit.push_back(pTempToNode);
				}

				if (pTempToNode == pTo)
				{
					toNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif

			}
		}
	} // End of the while loop, all necessary nodes explored

	  // Time to iterate backwards
	//pCurrentNode = pTo;
	//mPath.clear();

	//while (toNodeAdded && !mPath.containsNode(pFrom))
	//{
	//	// Build the path
	//	mPath.addNode(pCurrentNode);

	//	// iterate backwards until at start
	//	pCurrentNode = pCurrentNode->becomePrev();
	//}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return mPath;

}