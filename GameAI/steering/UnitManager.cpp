#include "UnitManager.h"
#include "KinematicUnit.h"

#include "Vector2D.h"
#include "Game.h"

UnitManager::UnitManager(Sprite *enemySprite)
{
	mEnemySpr = enemySprite;
}

UnitManager::~UnitManager()
{
	cleanUp();
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

void UnitManager::addUnit(Vector2D position, bool seek, KinematicUnit* target, Sprite* spr)
{
	KinematicUnit* newUnit;
	// Create a new unit w/ sprite*, vector2d position, float orientation, vec2d velocity,
	// float rotationvel, float max vel, float maxaccel
	//newUnit = new KinematicUnit()

	if (spr != NULL)
	{
		// use given sprite
		newUnit = new KinematicUnit(spr, position, 1, Vector2D(0, 0), 0.0f, ENEMY_MAX_VEL, ENEMY_MAX_ACCEL);
	}
	else
	{
		// use the enemy sprite
		newUnit = new KinematicUnit(mEnemySpr, position, 1, Vector2D(0, 0), 0.0f, ENEMY_MAX_VEL, ENEMY_MAX_ACCEL);
	}

	// Set the steering
	if (target != NULL)
	{
		if (seek)
			newUnit->dynamicSeek(NULL);

		else
			newUnit->dynamicArrive(NULL);
	}

	// Add the unit to mUnits
	std::string key = "Unit " + std::to_string(mUnits.size());
	mUnits[key] = newUnit;
}

void UnitManager::deleteUnit(const UnitKey& key)
{
	// Delete unit with given UnitKey
	std::map<UnitKey, KinematicUnit*>::iterator iter = mUnits.find(key);

	// If it exists..
	if (iter != mUnits.end())
	{
		std::cout << "\nDELETED UNIT " << key <<  "\n";
		delete iter->second;
		mUnits.erase(iter);
	}

	if (mUnits.empty())
		gpGame->exit();

}

void UnitManager::draw(GraphicsSystem* gSystem)
{
	// Traverse map w/ iterator
	std::map<UnitKey, KinematicUnit*>::iterator iter;

	for (iter = mUnits.begin(); iter != mUnits.end(); ++iter)
	{
		iter->second->draw(gSystem->getBackBuffer());
	}
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