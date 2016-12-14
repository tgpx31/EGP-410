#pragma once

#include "CylinderCollision.h"
#include "KinematicUnit.h"

class StateMachine;
class Sprite;
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

	/*
	SM_State* mpStateList[NUM_STATES];
	Transition* mpTransitions[NUM_TRANSITIONS];

	void initStates();
	void initTransitions();
	void applyTransitionsToStates();
	void addStatesToStateMachine();
	*/

	bool checkCollidingPlayer();

public:
	Enemy(Sprite* pNormalSprite, Sprite* pFleeSprite);
	~Enemy();

	void update(float time = 0.0f);
	void draw();

	inline KinematicUnit* getUnit() { return mpUnit; };
	inline CylinderCollision* getCollider() { return mpUnit->getCollider(); };
};
