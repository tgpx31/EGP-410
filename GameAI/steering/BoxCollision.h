#pragma once

#include "Trackable.h"
#include "Vector2D.h"

class BoxCollision : public Trackable
{
private:
	Vector2D mDimensions;
	Vector2D mPosition;


public:
	BoxCollision(float width, float height, float x, float y);
	BoxCollision(Vector2D dim, Vector2D pos);
	BoxCollision();

	bool isColliding();
	void update();

};