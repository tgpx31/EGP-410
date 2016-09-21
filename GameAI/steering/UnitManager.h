#pragma once

#include "Trackable.h"


/* Unit Manager:
 * Container w/ pointers to all units
 * Add/Delete Units
 * Update
 */

class UnitManager : public Trackable
{
private:

public:
	UnitManager();
	~UnitManager();

	void AddUnit();
	void DeleteUnit();
};