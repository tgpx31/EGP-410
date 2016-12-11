#include "Game.h"

#include "Kinematic.h"
#include "KinematicUnit.h"
#include "UnitManager.h"

#include "Sprite.h"
#include "GraphicsSystem.h"

#include "Steering.h"

#include "CylinderCollision.h"

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
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;

	delete mpCircleCollider;
	mpCircleCollider = nullptr;
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
	//setNewOrientation();

	//// Keep the Colliders with the sprite
	mpCircleCollider->setPos(mPosition);
}

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