#include "Wall.h"

Wall::Wall(float width, float height, float x, float y)
{
	mDimensions.setX(width);
	mDimensions.setY(height);

	mPosition.setX(x);
	mPosition.setY(y);

	std::cout << "\nWALL ADDED @ " << mPosition.getX() << ", " << mPosition.getY() << "\n";
}

Wall::Wall(Vector2D dimensions, Vector2D position)
{
	mDimensions = dimensions;
	mPosition = position;
	std::cout << "\nWALL ADDED @ " << mPosition.getX() << ", " << mPosition.getY() << "\n";
}

Wall::~Wall()
{}