#pragma once

#include <map>
#include <Trackable.h>

/**
*	State Machine.h
*
*	Contains:
*		Transitions
*		Transition Types
*
*		States
*		State Machine
**/

typedef int SM_ID;

/**
*	Transitions types
**/
enum TransitionType
{
	INVALID_TRANSITION_TYPE = -1,
	
	// Player Transitions
	DIRECTIONAL_VELOCITY_TRANSITION = 0,
	POWERUP_TO_NORMAL_TRANSITION = 1,
	NORMAL_TO_POWERUP_TRANSITION = 2,
	GAME_OVER_TRANSITION = 3,

	// NPC Transitions
	TO_WANDER_TRANSITION = 4,
	TO_CHASE_TRANSITION = 5,
	TO_FLEE_TRANSITION = 6,

	// Game state Transitions
	END_GAME_TRANSITION = 9
};

/**
*	Transition class
**/
class Transition : public Trackable
{
public:
	Transition(TransitionType type, const SM_ID& target_ID) :mTransitionType(type), mTargetState_ID(target_ID) {};
	~Transition() {};

	inline int getTargetStateID() const { return mTargetState_ID; };
	inline TransitionType getTransitionType() const { return mTransitionType; };

protected:
	SM_ID mTargetState_ID;
	TransitionType mTransitionType;
};

/**
*	State class
**/
class SM_State : public Trackable
{
public:
	SM_State(const SM_ID& id) :mID(id) {};
	~SM_State();

	void addTransition(Transition* pTransition);
	inline const SM_ID& getID() const { return mID; };

	virtual void onEntrance() = 0;						// Entering a state
	virtual void onExit() = 0;							// Leaving a state
	virtual Transition* update() = 0;					// Tick each frame, if no transition, then return NULL

protected:
	SM_ID mID;
	std::map<TransitionType, Transition*> mTransitions;
};

/**
*	State Machine Class
*	Handle current state and transitions
**/
class StateMachine : public Trackable
{
public:
	StateMachine() :mpCurrentState(NULL), mInitialStateID(-1) {};
	~StateMachine();

	void addState(SM_State* pState);
	inline void setInitialStateID(const SM_ID& id) { mInitialStateID = id; };
	
	inline SM_ID getCurrentState() { return mpCurrentState->getID(); };

	void update();							// Give the current state a chance to run
	void start();							// Go to the initial state

protected:
	void transitionToState(const SM_ID& targetID);	// Call onExit for old state and onEntrance for the new state

	std::map<SM_ID, SM_State*> mStates;					// All states, indexed by SM_ID
	SM_State* mpCurrentState;							// Currently active state
	SM_ID mInitialStateID;								// First state to run
};