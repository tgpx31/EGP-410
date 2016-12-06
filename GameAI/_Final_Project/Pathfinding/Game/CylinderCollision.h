#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include <vector>

class BoxCollision;

class CylinderCollision : public Trackable
{
private:
	Vector2D mPosition;
	int mRadius;

public:
	CylinderCollision(float x, float y, int radius);
	CylinderCollision(Vector2D position, int radius);
	~CylinderCollision() {};

	inline float getX() { return mPosition.getX(); };
	inline float getY() { return mPosition.getY(); };

	inline Vector2D getPos() { return mPosition; };

	inline void setPos(Vector2D newPos) { mPosition = newPos; };
	inline void setRadius(int rad) { mRadius = rad; };
	inline int getRadius() { return mRadius; };

	bool isCollidingBoxes(BoxCollision* other);
	bool isCollidingCylinders(CylinderCollision* other);

	bool update(std::vector<BoxCollision*> boxes);	// update to check for cylinders too

	// ADD: DEBUG TO VIEW COLLIDER
};