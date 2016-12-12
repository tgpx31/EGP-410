#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include "Defines.h"

class Sprite;
class CylinderCollision;

class Door : public Trackable
{
private:
	Vector2D mPosition;	
	Sprite* mpSprite;
	CylinderCollision* mpCollider;
	
	IDType mMapTo;
	Door* mConnectedDoor;

public:
	Door(Vector2D position, Sprite* pSprite);
	~Door();

	inline Vector2D getPosition() { return mPosition; };
	inline CylinderCollision* getCollider() { return mpCollider; }

	inline IDType getMapTo() { return mMapTo; }
	inline Door* getConnectedDoor() { return mConnectedDoor; };

	inline void setMapTo(IDType id) { mMapTo = id; };
	inline void setConnectedDoor(Door* door) { mConnectedDoor = door; };

	void draw();
};