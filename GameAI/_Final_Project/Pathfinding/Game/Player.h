#pragma once

class KinematicUnit;
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
	PlayerMovementState mLastState;
	
	/*
	StateMachine* mpStateMachine;
	
	SM_State* mpStateList[NUM_STATES];
	Transition* mpTransitions[NUM_TRANSITIONS];

	void initStates();
	void initTransitions();
	void applyTransitionsToStates();
	void addStatesToStateMachine();
	*/

public:
	Player(Sprite* pSprite);
	~Player();

	void setState(PlayerMovementState state);
	void update(float time = 0.0f);
	void draw();
};