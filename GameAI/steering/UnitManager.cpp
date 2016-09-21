#include "UnitManager.h"
#include "KinematicUnit.h"

#include "Vector2D.h"

UnitManager::UnitManager(){}

UnitManager::~UnitManager()
{

}

void UnitManager::cleanUp()
{
	// Traverse map w/ iterator
	std::map<UnitKey, KinematicUnit*>::iterator iter;

	// Clean all entries
	for (iter = mUnits.begin(); iter != mUnits.end(); ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}
	mUnits.clear();
}

void UnitManager::addUnit(Vector2D position)
{
	KinematicUnit* newUnit;
	// Create a new unit w/ sprite*, vector2d position, float orientation, vec2d velocity, float rotationvel, float max vel, float maxaccel
	//newUnit = new KinematicUnit()

	// Add the unit to mUnits
}

void UnitManager::deleteUnit()
{
	// Delete a random unit from the map

}

void UnitManager::update(double frameTime)
{
	// Traverse map w/ iterator
	std::map<UnitKey, KinematicUnit*>::iterator iter;

	for (iter = mUnits.begin(); iter != mUnits.end(); ++iter)
	{
		iter->second->update(frameTime);
	}
}