#pragma once

#include "Trackable.h"
#include <string>
#include <map>

#include "GraphicsSystem.h"

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
	const float ENEMY_MAX_VEL = 180.0F;
	const float ENEMY_MAX_ACCEL = 100.0f;

	/*const float PLAYER_MAX_VEL = 200.0F;
	const float PLAYER_MAX_ACCEL = 10.0F;*/

	std::map<UnitKey, KinematicUnit*> mUnits;
	void cleanUp();
	Sprite* mEnemySpr;

public:
	UnitManager(Sprite* enemySprite);
	~UnitManager();

	void addUnit(Vector2D position, bool seek = true, KinematicUnit* target = NULL, Sprite* spr = NULL);
	void deleteUnit(const UnitKey& key);

	void draw(GraphicsSystem* gSystem);
	void update(double frameTime);

	inline int getRandUnit() { return 0 + (rand() % static_cast<int>(mUnits.size() - 0 + 1)); };
	inline std::map<UnitKey, KinematicUnit*> getMap() { return mUnits; };
};