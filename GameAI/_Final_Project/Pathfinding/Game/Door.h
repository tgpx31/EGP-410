#pragma once

#include "Trackable.h"
#include "Vector2D.h"

class Sprite;
class CylinderCollision;

class Door : public Trackable
{
private:
	Vector2D mPosition;	
	Sprite* mpSprite;
	CylinderCollision* mpCollider;

public:
	Door(Vector2D position, Sprite* pSprite);
	~Door();

	inline Vector2D getPosition() { return mPosition; };
	inline CylinderCollision* getCollider() { return mpCollider; }

	void draw();
};