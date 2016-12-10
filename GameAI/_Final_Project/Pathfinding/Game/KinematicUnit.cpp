#include "Game.h"

#include "Kinematic.h"
#include "KinematicUnit.h"
#include "UnitManager.h"

#include "Sprite.h"
#include "GraphicsSystem.h"

#include "Steering.h"

#include "CylinderCollision.h"

#include "StateMachine.h"
#include "PlayerMoveState.h"

using namespace std;

Steering gNullSteering(gZeroVector2D, 0.0f);
const Vector2D CENTER_SCREEN = Vector2D(512, 384);

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
	:Kinematic(position, orientation, velocity, rotationVel)
	, mpSprite(pSprite)
	, mpCurrentSteering(NULL)
	, mMaxVelocity(maxVelocity)
	, mMaxAcceleration(maxAcceleration)
{
	mpCircleCollider = new CylinderCollision(mPosition, mpSprite->getWidth() / 2);

	/*
	// init the states and transitions
	mpStateMachine = new StateMachine();

	initStates();
	initTransitions();
	applyTransitionsToStates();
	addStatesToStateMachine();
	*/
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;

	delete mpCircleCollider;
	mpCircleCollider = nullptr;

	/*
	delete mpStateMachine;
	
	for (SM_ID i = 0; i < NUM_TRANSITIONS; ++i)
	{
		delete mpTransitions[i];
	}

	for (SM_ID i = 0; i < NUM_STATES; ++i)
	{
		delete mpStateList[i];
	}
	*/
}

void KinematicUnit::draw(GraphicsBuffer* pBuffer)
{
	mpSprite->draw(*pBuffer, mPosition.getX(), mPosition.getY(), mOrientation);
}

void KinematicUnit::update(float time)
{
	Steering* steering;
	if (mpCurrentSteering != NULL)
	{
		steering = mpCurrentSteering->getSteering();
	}
	else
	{
		steering = &gNullSteering;
	}

	if (steering->shouldApplyDirectly())
	{
		//not stopped
		if (getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED)
		{
			setVelocity(steering->getLinear());
			setOrientation(steering->getAngular());
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity(0.0f);
		steering->setAngular(0.0f);
	}

	//move the unit using current velocities
	Kinematic::update(time);

	//calculate new velocities
	calcNewVelocities(*steering, time, mMaxVelocity, 25.0f);

	//set the orientation to match the direction of travel
	setNewOrientation();

	//// Keep the Colliders with the sprite
	mpCircleCollider->setPos(mPosition);

	//if (mpCircleCollider->update(gpGame->getWalls()))
	//{
	//	// shit, hit a wall. turn around
	//	// seek the middle of the screen until not colliding
	//	Vector2D bounceVel = CENTER_SCREEN - mPosition;
	//	bounceVel.normalize();
	//	bounceVel *= mMaxVelocity;

	//	setVelocity(bounceVel);
	//}
}

/*
void KinematicUnit::initStates()
{
	mpStateList[0] = new PlayerMoveState(0);
}

void KinematicUnit::initTransitions()
{
	mpTransitions[0] = new Transition(DIRECTIONAL_VELOCITY_TRANSITION, 0);
}

void KinematicUnit::applyTransitionsToStates()
{
	mpStateList[0]->addTransition(mpTransitions[0]);
}

void KinematicUnit::addStatesToStateMachine()
{
	mpStateMachine->addState(mpStateList[0]);

	// set initial stuff
	mpStateMachine->setInitialStateID(0);
}
*/

//private - deletes old Steering before setting
void KinematicUnit::setSteering(Steering* pSteering)
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{
	mOrientation = getOrientationFromVelocity(mOrientation, mVelocity);
}