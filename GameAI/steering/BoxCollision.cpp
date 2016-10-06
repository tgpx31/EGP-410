#include "BoxCollision.h"

BoxCollision::BoxCollision(float width, float height, float x, float y)
{
	mDimensions.setX(width);
	mDimensions.setY(height);

	mPosition.setX(x);
	mPosition.setY(y);

	std::cout << "\Box Collider ADDED @ " << mPosition.getX() << ", " << mPosition.getY() << "\n";
}

// Use a Vector2D with X & Y, then one with WIDTH and HEIGHT

BoxCollision::BoxCollision(Vector2D dim, Vector2D pos)
{
	mDimensions = dim;
	mPosition = pos;
	std::cout << "\Box Collider ADDED @ " << mPosition.getX() << ", " << mPosition.getY() << "\n";
}

BoxCollision::BoxCollision()
{
}

bool BoxCollision::isColliding()
{
	return false;
}

void BoxCollision::update()
{
	// check if colliding in here
}
