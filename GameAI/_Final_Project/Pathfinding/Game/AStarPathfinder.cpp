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
	pFrom->setCostFromStart(pFrom, 0.0f);	// start node has cost of 0
	nodesToVisit.push_front(pFrom);			// visit the initial node first

	mFinalPath.clear();

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	mPath.clear();							// mPath does not contain the actual calculated path (based on Dean's original codebase)

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();

		//add Node to mPath
		mPath.addNode(pCurrentNode);

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
				pTempToNode->setPrevNode(pCurrentNode->getId());						// set the prev. node for pCurrentNode
				pTempToNode->setCostFromStart(pCurrentNode, connections[i]->getCost()); // set pCurrentNode's cost from start

				// Set the initial connection's toNode as the closest
				if (closestToTarget == NULL)
				{
					closestToTarget = pTempToNode;
					nodesToVisit.push_front(closestToTarget);
				}

				// Check your heuristic here
				// If there is a node that is closer to the target, prioritize that (put it at the front)
				else if (getHeuristic(pTempToNode, pTo) < getHeuristic(closestToTarget, pTo))
				{
					closestToTarget = pTempToNode;
					nodesToVisit.push_front(closestToTarget);
				}

				// Otherwise, push_back
				// it's further than the currently closest, so it is less likely to help find the path needed
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
	}
	// End of the while loop, all necessary nodes explored

	// Time to iterate backwards
	pCurrentNode = pTo;

	// Uses toNodeAdded for the loop
	// flips off when the start node is added into the path
	while (toNodeAdded)
	{
		// Build the path
		mFinalPath.push_back(pCurrentNode);

		if (pCurrentNode == pFrom)
			toNodeAdded = false;

		// iterate backwards until at start
		pCurrentNode = pCurrentNode->becomePrev();
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return mPath;
}

float AStarPathfinder::getHeuristic(Node * node, Node * goal)
{
	// Heuristic used is based off of the Manhattan Distance, referenced @ http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
	// Manhattan distance heuristic is admissable
	// To use an inadmissable heuristic, use euclidian distance

	//TODO: Change functionality to work with new multimap system
	/*
	float dx = abs(gpGameApp->getGrid()->getULCornerOfSquare(node->getId()).getX() - gpGameApp->getGrid()->getULCornerOfSquare(goal->getId()).getX());
	float dy = abs(gpGameApp->getGrid()->getULCornerOfSquare(node->getId()).getY() - gpGameApp->getGrid()->getULCornerOfSquare(goal->getId()).getY());
	
	return (dx + dy);
	*/

	std::cout << "AStarPathfinder::getHeuristic(Node * node, Node * goal) is not implemented. See source for details." << std::endl;

	return 0.0f;
}
