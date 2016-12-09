#include "Connection.h"
#include "GameApp.h"
#include "GridGraph.h"

Node::Node()
:mId(BAD_NODE_ID)
{
	mPrevNodeId = 0;
	mCostFromStart = 0.0f;
}

Node::Node( const NODE_ID& id )
:mId(id)
{
	mPrevNodeId = 0;
	mCostFromStart = 0.0f;
}

Node::~Node()
{
}

void Node::setCostFromStart(Node* pPrevNode, float cost)
{
	// If there is no previous node (mId = mPrevNodeId)
	// Then there's no weight to add in
	if (mId == mPrevNodeId)
	{
		return;
	}

	// Otherwise, add the cost from the previous node
	// and the cost of the connection to get here
	else
	{
		mCostFromStart = pPrevNode->getCostFromStart() + cost;
		return;
	}
}

Node * Node::becomePrev()
{
	//TODO: Change functionality to work with new multimap system
	//return gpGameApp->getGridGraph()->getNode(mPrevNodeId);

	std::cout << "Node::becomePrev() is not implemented. See see source for details." << std::endl;

	return nullptr;
}
