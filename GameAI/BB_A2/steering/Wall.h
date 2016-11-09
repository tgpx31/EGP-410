#pragma once

#include "Trackable.h"
#include "Vector2D.h"

/* Walls:
   Bounding box
   Dimensions
*/

class Wall : public Trackable
{
private:
	Vector2D mDimensions;
	Vector2D mPosition;

public:
	Wall(float width = 1, float height =1, float x = 0, float y = 0);
	Wall(Vector2D dimensions = Vector2D(1, 1), Vector2D position = Vector2D(0, 0));
	~Wall();


};