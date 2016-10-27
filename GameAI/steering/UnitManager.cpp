#include "UnitManager.h"
#include "KinematicUnit.h"

#include "Vector2D.h"
#include <fstream>


void UnitManager::loadWeights()
{
	std::string line;
	int i = 0;


	// If the file does not exist, do default weights
	if (!std::ifstream(mFile))
	{
		return;
	}
	
	// If there is a file, open a filestream
	std::ifstream inFile;
	inFile.open(mFile);

	// check if good
	if (!inFile.fail())
	{
		// read in values and assign them
		while (!inFile.eof() && i < 2)
		{
			inFile >> mWeights[i];
				
			++i;
		}
	}
	else
	{
		std::cout << "\nFUCK ME, RIGHT\n";
	}

	// close the file
	inFile.close();
	
}

UnitManager::UnitManager(Sprite* enemySprite)
{
	mEnemySpr = enemySprite;
	loadWeights();
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

void UnitManager::addUnit(Vector2D position, Behavior behavior, KinematicUnit* target, Sprite* spr)
{
	KinematicUnit* newUnit;
	// Create a new unit w/ sprite*, vector2d position, float orientation, vec2d velocity,
	// float rotationvel, float max vel, float maxaccel
	//newUnit = new KinematicUnit()

	if (spr != NULL)
	{
		// use given sprite
		newUnit = new KinematicUnit(spr, position, 1, Vector2D(0, 0), mRotVel, ENEMY_MAX_VEL, ENEMY_MAX_ACCEL);
	}
	else
	{
		// use the enemy sprite
		newUnit = new KinematicUnit(mEnemySpr, position, 1, Vector2D(0, 0), mRotVel, ENEMY_MAX_VEL, ENEMY_MAX_ACCEL);
	}

	// Set the steering
	if (target != NULL)
	{
		switch (behavior)
		{
		case 0: newUnit->dynamicSeek(NULL);
			break;
		case 1: newUnit->dynamicArrive(NULL);
			break;
		case 2: newUnit->wanderAndSeek(NULL);
			break;
		case 3: newUnit->wanderAndFlee(NULL);
			break;
		case 4: newUnit->boidsSteering();
			break;
		default: std::cout << "INVALID STEERING BEHAIVOR";
		}
	}

	// Add the unit to mUnits
	std::string key = "Unit " + std::to_string(mUnits.size());
	mUnits[key] = newUnit;
}

void UnitManager::deleteUnit()
{
	std::map<UnitKey, KinematicUnit*>::iterator iter = mUnits.begin();
	std::advance(iter, rand() % mUnits.size());

	//// Delete unit with given UnitKey
	//std::map<UnitKey, KinematicUnit*>::iterator iter = mUnits.find(key);

	// If it exists..
	if (iter != mUnits.end())
	{
		//std::cout << "\nDELETED UNIT " << key <<  "\n";
		delete iter->second;
		mUnits.erase(iter);
	}
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