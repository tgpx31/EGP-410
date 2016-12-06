#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include <allegro5\allegro_primitives.h>
#include <vector>

class BoxCollision : public Trackable
{
private:
	Vector2D mDimensions;
	Vector2D mPosition;

public:
	BoxCollision(float width, float height, float x, float y);
	BoxCollision(Vector2D dim, Vector2D pos);
	~BoxCollision() {};

	inline float getX() { return mPosition.getX(); };
	inline float getY() { return mPosition.getY(); };
	inline Vector2D getPos() { return mPosition; };
	inline void setPos(Vector2D newPos) { mPosition = newPos; };

	inline float getWidth() { return mDimensions.getX(); };
	inline float getHeight() { return mDimensions.getY(); };
	inline Vector2D getDimensions() { return mDimensions; };
	inline void setDim(Vector2D dim) { mDimensions = dim; };

	Vector2D getCenterPoint();

	bool isColliding(BoxCollision* other);
	bool update(std::vector<BoxCollision*> walls);

	// ADD: DEBUG TO VIEW COLLIDER
};