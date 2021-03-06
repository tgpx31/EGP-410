#pragma once

#include "Grid.h"
#include "KinematicUnit.h"
#include "CylinderCollision.h"

class Sprite;
/*
class StateMachine;
class SM_State;
class Transition;
const int NUM_STATES = 1;
const int NUM_TRANSITIONS = 1;
*/
enum PlayerMovementState
{
	INVALID_MOVEMENT_STATE = -1,
	GOING_UP,
	GOING_DOWN,
	GOING_LEFT,
	GOING_RIGHT
};

class Player
{
private:
	KinematicUnit* mpUnit;
	PlayerMovementState mCurrentState;
	
	Vector2D mPreviousPosition;

	bool mInvincible;

	/*
	StateMachine* mpStateMachine;
	
	SM_State* mpStateList[NUM_STATES];
	Transition* mpTransitions[NUM_TRANSITIONS];

	void initStates();
	void initTransitions();
	void applyTransitionsToStates();
	void addStatesToStateMachine();
	*/
	void checkCollision();

public:
	Player(Sprite* pSprite);
	~Player();
	
	// Currently does not work because it is checking for grid spaces, not the coins
	// Should check actual collision with a collider

	inline PlayerMovementState getState() { return mCurrentState; };
	inline Vector2D getPosition() { return mpUnit->getPosition(); };
	inline CylinderCollision* getCollider() { return mpUnit->getCollider(); };
	inline bool getInvincible() { return mInvincible; };
	inline void setInvincible(bool invincible) { mInvincible = invincible; };

	void setState(PlayerMovementState state);
	void setPosition(Vector2D position);


	void update(float time = 0.0f);
	void draw(bool isDebug);

	inline KinematicUnit* getUnit() { return mpUnit; };
};