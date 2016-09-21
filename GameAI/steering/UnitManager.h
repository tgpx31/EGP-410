#pragma once

#include "Trackable.h"
#include <string>
#include <map>

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
	std::map<UnitKey, KinematicUnit*> mUnits;
	void cleanUp();

public:
	UnitManager();
	~UnitManager();

	void addUnit(Vector2D position);
	void deleteUnit();
	void update(double frameTime);
};