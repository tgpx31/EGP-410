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

	inline Vector2D getVelocity() const { return mVelocity; };
	inline void setVelocity(const Vector2D& velocity) { mVelocity = velocity; };

	inline float getMaxVelocity() const { return mMaxVelocity; };
	inline void changeMaxVel(float vel) { mMaxVelocity += vel; };
	
	inline float getMaxAcceleration() const { return mMaxAcceleration; };
	inline void changeMaxAccel(float accel) { mMaxAcceleration += accel; };

	inline void changeRotVel(float rot) { mRotationVel += rot; };
	inline float getRotVelocity() { return mRotationVel; };

	inline int getRadius() { return mpCurrentSteering->getRadius(); };

	inline void setSprite(Sprite* newSpr) { mpSprite = newSpr; };

	virtual void setNewOrientation();//face the direction you are moving
									 
	void draw(GraphicsBuffer* pBuffer);//draw yourself to the indicated buffer
	void update(float time = 0.0f);//move according to the current velocities and update velocities based on current Steering

	//initiate behaviors
	// Write in behavior here
	// SM using A* and steering

	inline CylinderCollision* getCollider() { return mpCircleCollider; };
	Steering* getSteering() { return mpCurrentSteering; };	
	
private:
	Sprite* mpSprite;
	Steering* mpCurrentSteering;
	Vector2D mTarget;
	CylinderCollision* mpCircleCollider;


	float mMaxVelocity;
	float mMaxAcceleration;

	void setSteering(Steering* pSteering);

};