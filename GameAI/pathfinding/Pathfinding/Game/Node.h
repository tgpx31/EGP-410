#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node:public Trackable
{
public:
	Node( const NODE_ID& id );
	Node();
	~Node();

	const NODE_ID& getId() const {return mId;};

	inline NODE_ID getPrevNode() { return mPrevNodeId; };
	inline void setPrevNode(const NODE_ID& id) { mPrevNodeId = id; };
	inline float getCostFromStart() { return mCostFromStart; };
	void setCostFromStart(Node* pPrevNode, float cost);

	Node* becomePrev();

private:
	const NODE_ID mId;
	NODE_ID mPrevNodeId;
	float mCostFromStart;
};