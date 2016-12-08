#pragma once

#include "Kinematic.h"
#include "Steering.h"

class CylinderCollision;

/*KinematicUnit - a unit that is derived from the Kinematic class.  Adds behaviors and max speeds and a current Steering.

Dean Lawson
Champlain College
2011
*/

/**
	EACH UNIT NEEDS
	STATE MACHINE
	A*
	STEERING
**/

//forward declarations
class Sprite;
class GraphicsBuffer;

extern Steering gNullSteering;//global object - can point to it for a "NULL" Steering

							  //minmimum forward speed a unit has to have inorder to rotate 
							  //(keeps unit from spinning in place after stopping)
const float MIN_VELOCITY_TO_TURN_SQUARED = 1.0f;

class KinematicUnit : public Kinematic
{
public:
	KinematicUnit(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	~KinematicUnit();

	//getters and setters
	void setTarget(const Vector2D& target) { mTarget = target; };
	const Vector2D& getPosition() const { return mPosition; };
	float getMaxVelocity() const { return mMaxVelocity; };
	Vector2D getVelocity() const { return mVelocity; };
	float getMaxAcceleration() const { return mMaxAcceleration; };
	void setVelocity(const Vector2D& velocity) { mVelocity = velocity; };

	virtual void setNewOrientation();//face the direction you are moving

									 //draw yourself to the indicated buffer
	void draw(GraphicsBuffer* pBuffer);
	//move according to the current velocities and update velocities based on current Steering
	void update(float time);

	//initiate behaviors
	// Write in behavior here
	// SM using A* and steering

	inline CylinderCollision* getCollider() { return mpCircleCollider; };

	void changeMaxVel(float vel) { mMaxVelocity += vel; };
	Steering* getSteering() { return mpCurrentSteering; };

	void changeRotVel(float rot) { mRotationVel += rot; };
	float getRotVelocity() { return mRotationVel; };

	void changeMaxAccel(float accel) { mMaxAcceleration += accel; };

	inline int getRadius() { return mpCurrentSteering->getRadius(); };

	inline void setSprite(Sprite* newSpr) { mpSprite = newSpr; };
private:
	Sprite* mpSprite;
	Steering* mpCurrentSteering;
	Vector2D mTarget;
	float mMaxVelocity;
	float mMaxAcceleration;

	CylinderCollision* mpCircleCollider;

	void setSteering(Steering* pSteering);

};