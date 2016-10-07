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

	float getX() { return mPosition.getX(); };
	float getY() { return mPosition.getY(); };
	float getWidth() { return mDimensions.getX(); };
	float getHeight() { return mDimensions.getX(); };

	void setPos(Vector2D newPos) { mPosition = newPos; };

	bool isColliding(BoxCollision* other);
	void update();

};