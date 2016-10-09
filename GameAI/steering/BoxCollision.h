#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include <allegro5\allegro_primitives.h>
#include "UnitManager.h"
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

	float getX() { return mPosition.getX(); };
	float getY() { return mPosition.getY(); };
	float getWidth() { return mDimensions.getX(); };
	float getHeight() { return mDimensions.getY(); };

	void setPos(Vector2D newPos) { mPosition = newPos; };

	bool isColliding(BoxCollision* other);
	bool update(std::vector<BoxCollision*> walls);

	void setDim(Vector2D dim) { mDimensions = dim; };
	//void draw() { al_draw_filled_rectangle(mPosition.getX(), mPosition.getY(), mPosition.getX() + mDimensions.getX(), mPosition.getY() + mDimensions.getY(), al_map_rgb(255,0,0)); };

};