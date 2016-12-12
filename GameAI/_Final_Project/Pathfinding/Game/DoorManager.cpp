#include "DoorManager.h"
#include "Door.h"

DoorManager::DoorManager()
{
}

DoorManager::~DoorManager()
{
	std::map<IDType, Door*>::iterator iter;

	for (iter = mDoors.begin(); iter != mDoors.end(); iter++)
	{
		delete iter->second;
	}
}

void DoorManager::addDoor(IDType& id, Door* pDoor)
{
	std::map<IDType, Door*>::iterator iter;

	iter = mDoors.find(id);

	if (iter != mDoors.end())
	{
		delete iter->second;
		mDoors.erase(id);
	}
	
	mDoors[id] = pDoor;
}

void DoorManager::createDoor(Vector2D position, Sprite * pSprite)
{
	Door* newDoor = new Door(position, pSprite);
	IDType id = mDoors.size() + 1;
	addDoor(id, newDoor);
}

void DoorManager::update()
{
	//Does something idk
}

void DoorManager::draw()
{
	std::map<IDType, Door*>::iterator iter;

	for (iter = mDoors.begin(); iter != mDoors.end(); iter++)
	{
		iter->second->draw();
	}
}
