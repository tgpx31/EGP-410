#pragma once

#include "CylinderCollision.h"
#include "KinematicUnit.h"
#include "Defines.h"

class StateMachine;
class Sprite;
class Node;
class AStarPathfinder;
//class SM_State;
//class Transition;

//const int NUM_STATES = 1;
//const int NUM_TRANSITIONS = 1;

class Enemy
{
private:
	KinematicUnit* mpUnit;
	StateMachine* mpStateMachine;

	Sprite* mpNormalSprite;
	Sprite* mpFleeSprite;

	int mStepIntoPathCounter;
	const int STEP_RESET_LIMIT = 3;

	float mTimeToRecalculate;
	float mElapsedTime;

	std::vector<Node*> mPath;

	IDType mMapID; //ID of map currently on

	/*
	SM_State* mpStateList[NUM_STATES];
	Transition* mpTransitions[NUM_TRANSITIONS];

	void initStates();
	void initTransitions();
	void applyTransitionsToStates();
	void addStatesToStateMachine();
	*/

	bool checkCollidingPlayer();
	void recalculatePath();

	Node* start;
	Node* goal;
	AStarPathfinder* mpAStar;
	
public:
	Enemy(IDType mapID, Sprite* pNormalSprite, Sprite* pFleeSprite, float timeToRecalculate);
	~Enemy();

	void update(float time = 0.0f);
	void draw();

	inline KinematicUnit* getUnit() { return mpUnit; };
	inline CylinderCollision* getCollider() { return mpUnit->getCollider(); };
	inline AStarPathfinder* getAStar() { return mpAStar; };

	void setStart(Vector2D position);
	void setGoal(Vector2D position);

	inline Node* getStart() { return start; };
	inline Node* getGoal() { return goal; };

	void doPathfinding();
	bool shouldMove();
};
