#include "DoorManager.h"
#include "Door.h"
#include "CylinderCollision.h"
#include "GameApp.h"
#include "Player.h"

#include "SetCurrentMapMessage.h"
#include "SetPlayerLocationMessage.h"
#include "GameMessageManager.h"

#include "GameMap.h"

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

void DoorManager::addDoor(IDType id, Door* pDoor)
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
	//Check for collision
	std::map<IDType, Door*>::iterator iter;

	for (iter = mDoors.begin(); iter != mDoors.end(); iter++)
	{
		if (iter->second->getCollider()->isCollidingCylinders(gpGameApp->getPlayer()->getCollider()))
		{
			GameMessage* pMessage = new SetCurrentMapMessage(iter->second->getMapTo());
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);

			Vector2D newPlayerPos;

			switch (gpGameApp->getPlayer()->getState())
			{
				case GOING_UP:
					newPlayerPos = Vector2D(iter->second->getConnectedDoor()->getPosition().getX(), iter->second->getConnectedDoor()->getPosition().getY() - GRID_SQUARE_SIZE);
					break;
				case GOING_DOWN:
					newPlayerPos = Vector2D(iter->second->getConnectedDoor()->getPosition().getX(), iter->second->getConnectedDoor()->getPosition().getY() + GRID_SQUARE_SIZE);
					break;
				case GOING_LEFT:
					newPlayerPos = Vector2D(iter->second->getConnectedDoor()->getPosition().getX() - GRID_SQUARE_SIZE, iter->second->getConnectedDoor()->getPosition().getY());
					break;
				case GOING_RIGHT:
					newPlayerPos = Vector2D(iter->second->getConnectedDoor()->getPosition().getX() + GRID_SQUARE_SIZE, iter->second->getConnectedDoor()->getPosition().getY());
					break;
			}

			pMessage = new SetPlayerPositionMessage(newPlayerPos);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
		}
	}
}

void DoorManager::draw()
{
	std::map<IDType, Door*>::iterator iter;

	for (iter = mDoors.begin(); iter != mDoors.end(); iter++)
	{
		iter->second->draw();
	}
}
