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
	int STEP_RESET_LIMIT = 5;

	float mTimeToRecalculate;
	float mRespawnTime;
	float mElapsedTime;

	bool mIsDead;
	Vector2D mOriginalPosition;
	Vector2D mPreviousPosition;
	IDType mOriginalMapID;

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
	bool checkCollidingWalls();
	void recalculatePath();
	void kill();
	void respawn();
	
	Vector2D determineTarget();
	void doWander();
	void doPathfinding();
	bool shouldMove();
	void updateMovement(float time);

	Node* start;
	Node* goal;
	AStarPathfinder* mpAStar;

	bool mGetPathToDoor;
	
public:
	Enemy(IDType mapID, Vector2D position, Sprite* pNormalSprite, Sprite* pFleeSprite, float timeToRecalculate);
	~Enemy();

	void update(float time = 0.0f);
	void draw(bool isDebug);

	inline KinematicUnit* getUnit() { return mpUnit; };
	inline CylinderCollision* getCollider() { return mpUnit->getCollider(); };
	inline AStarPathfinder* getAStar() { return mpAStar; };

	void setStart(Vector2D position);
	void setGoal(Vector2D position);

	inline Node* getStart() { return start; };
	inline Node* getGoal() { return goal; };

	void setSprite(bool isFlee);
	void changeMap(IDType mapID);

	inline float getSpawnTime() const { return mRespawnTime; };
	inline void setSpawnTime(const float& timer) { mRespawnTime = timer; };

	inline int getStepReset() { return STEP_RESET_LIMIT; };
	inline void setStepReset(const int& val) { STEP_RESET_LIMIT = val; };

	inline void resetTime() { mElapsedTime = 0; };
	inline void forceWander() { mpUnit->seek(determineTarget()); };
	inline void forceRecalculatePath() { recalculatePath(); };
};