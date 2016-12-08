#pragma once

#include "Trackable.h"
#include <string>
#include <map>

#include "GraphicsSystem.h"
#include "Game.h"

class Sprite;
class Vector2D;
class KinematicUnit;

/* Unit Manager:
* Container w/ pointers to all units
* Add/Delete Units
* Update
*/

typedef std::string UnitKey;

enum Behavior
{
	INVALID_BEHAVIOR = -1
};

class UnitManager : public Trackable
{
private:
	const std::string mFile = "savedWeights.txt";

	float ENEMY_MAX_VEL = 180.0f;
	float mRotVel = 0.0f;

	float ENEMY_MAX_ACCEL = 100.0f;

	std::map<UnitKey, KinematicUnit*> mUnits;
	void cleanUp();

public:
	UnitManager();
	~UnitManager();

	void addUnit(Vector2D position, Sprite* spr = NULL, Behavior behavior = INVALID_BEHAVIOR, KinematicUnit* target = NULL);
	void deleteUnit();

	void draw(GraphicsSystem* gSystem);
	void update(double frameTime = 0.0);

	inline int getRandUnit() { return rand() % mUnits.size(); };
	inline std::map<UnitKey, KinematicUnit*> getMap() { return mUnits; };

	void changeMaxVel(float newVel) { ENEMY_MAX_VEL += newVel; };
	inline int getMaxVel() { return static_cast<int>(ENEMY_MAX_VEL); };
	void changeRotVel(float newRot) { mRotVel += newRot; };
	inline float getRotVel() { return mRotVel; };

	void changeMaxAccel(float newAccel) { ENEMY_MAX_ACCEL += newAccel; };
	inline float getMaxAccel() { return ENEMY_MAX_ACCEL; };
};