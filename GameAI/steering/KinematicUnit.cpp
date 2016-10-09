#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Steering.h"
#include "KinematicSeekSteering.h"
#include "KinematicArriveSteering.h"
#include "KinematicWanderSteering.h"
#include "DynamicSeekSteering.h"
#include "DynamicArriveSteering.h"

#include "WanderAndSeekSteering.h"
#include "WanderAndFleeSteering.h"
#include "BoxCollision.h"

using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
:Kinematic( position, orientation, velocity, rotationVel )
,mpSprite(pSprite)
,mpCurrentSteering(NULL)
,mMaxVelocity(maxVelocity)
,mMaxAcceleration(maxAcceleration)
{
	mBoxCollider = new BoxCollision(mpSprite->getWidth(), mpSprite->getHeight(), mPosition.getX(), mPosition.getY());
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;
	delete mBoxCollider;
	mBoxCollider = nullptr;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw( *pBuffer, mPosition.getX(), mPosition.getY(), mOrientation );
}

void KinematicUnit::update(float time)
{
	Steering* steering;
	if( mpCurrentSteering != NULL )
	{
		steering = mpCurrentSteering->getSteering();
	}
	else
	{
		steering = &gNullSteering;
	}

	if( steering->shouldApplyDirectly() )
	{
		//not stopped
		if( getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED )
		{
			setVelocity( steering->getLinear() );
			setOrientation( steering->getAngular() );
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity( 0.0f );
		steering->setAngular( 0.0f );
	}

	//move the unit using current velocities
	Kinematic::update( time );
	//calculate new velocities
	calcNewVelocities( *steering, time, mMaxVelocity, 25.0f );
	//move to oposite side of screen if we are off
	//GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	setNewOrientation();

	//// Keep the BoxColliders with the sprite
	mBoxCollider->setPos(mPosition);
	
	if (mBoxCollider->update(gpGame->getWalls()))
	{
		// shit, hit a wall. turn around
		Vector2D oppVel = Vector2D(-mVelocity.getX(), -mVelocity.getY());
		setVelocity(oppVel);
		setOrientation(getOrientationFromVelocity(mOrientation, oppVel));
	}
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{ 
	mOrientation = getOrientationFromVelocity( mOrientation, mVelocity ); 
}

void KinematicUnit::seek(const Vector2D &target)
{
	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering( this, target );
	setSteering( pSeekSteering );
}

void KinematicUnit::arrive(const Vector2D &target)
{
	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering( this, target );
	setSteering( pArriveSteering );
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering( this );
	setSteering( pWanderSteering );
}

void KinematicUnit::dynamicSeek( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, gpGame->getPlayerUnit() );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicFlee( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, gpGame->getPlayerUnit(), true );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicArrive( KinematicUnit* pTarget )
{
	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering( this, gpGame->getPlayerUnit() );
	setSteering( pDynamicArriveSteering );
}

void KinematicUnit::wanderAndSeek(KinematicUnit * pTarget)
{
	WanderAndSeekSteering* pWanderAndSeekSteering = new WanderAndSeekSteering(this, gpGame->getPlayerUnit(), false);
	setSteering(pWanderAndSeekSteering);
}

void KinematicUnit::wanderAndFlee(KinematicUnit * pTarget)
{
	WanderAndSeekSteering* pWanderAndFleeSteering = new WanderAndSeekSteering(this, gpGame->getPlayerUnit(), true);
	setSteering(pWanderAndFleeSteering);
}

BoxCollision* KinematicUnit::getBoxCollider()
{
	return mBoxCollider;
}
