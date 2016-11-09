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

class UnitManager : public Trackable
{
private:
	float ENEMY_MAX_VEL = 180.0F;
	float mRotVel = 0.0f;

	float ENEMY_MAX_ACCEL = 100.0f;

	std::map<UnitKey, KinematicUnit*> mUnits;
	void cleanUp();
	Sprite* mEnemySpr;

public:
	UnitManager(Sprite* enemySprite);
	~UnitManager();

	void addUnit(Vector2D position, Behavior behavior = DYNAMIC_SEEK, KinematicUnit* target = NULL, Sprite* spr = NULL);
	void deleteUnit(const UnitKey& key);

	void draw(GraphicsSystem* gSystem);
	void update(double frameTime);

	inline int getRandUnit() { return 0 + (rand() % static_cast<int>(mUnits.size() - 0 + 1)); };
	inline std::map<UnitKey, KinematicUnit*> getMap() { return mUnits; };

	void changeMaxVel(float newVel) { ENEMY_MAX_VEL += newVel; };
	void changeRotVel(float newRot) { mRotVel += newRot; };
	void changeMaxAccel(float newAccel) { ENEMY_MAX_ACCEL += newAccel; };
};