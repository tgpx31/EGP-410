#include "BoxCollision.h"
#include "UnitManager.h"
#include "Game.h"
#include "KinematicUnit.h"

BoxCollision::BoxCollision(float width, float height, float x, float y)
{
	mDimensions.setX(width);
	mDimensions.setY(height);

	mPosition.setX(x);
	mPosition.setY(y);

	std::cout << "\nBox Collider ADDED @ " << mPosition.getX() << ", " << mPosition.getY() << "\n";
}

// Use a Vector2D with X & Y, then one with WIDTH and HEIGHT

BoxCollision::BoxCollision(Vector2D dim, Vector2D pos)
{
	mDimensions = dim;
	mPosition = pos;
	std::cout << "\nBox Collider ADDED @ " << mPosition.getX() << ", " << mPosition.getY() << "\n";
}

BoxCollision::BoxCollision()
{
}

bool BoxCollision::isColliding(BoxCollision* other)
{
	
	// Check if other is colliding with you
	// If the rectangle intersects...
	if (((mPosition.getX() > other->getX() && mPosition.getX() < other->getX() + other->getWidth()) ||
		(mPosition.getX() + getWidth() > other->getX() && mPosition.getX() + getWidth() < other->getX() + other->getWidth()))
		&&
		((mPosition.getY() > other->getY() && mPosition.getY() < other->getY() + other->getHeight()) ||
		(mPosition.getY() + getHeight() > other->getY() && mPosition.getY() + getHeight() < other->getY() + other->getHeight())))
	{
		// Do something about it!

		return true;
	}
	return false;
}

void BoxCollision::update()
{
	// Check through the Units to see if any are colliding. They will all have a collider
	// Walls do not need to behave a certain way to avoid each other
	std::map<UnitKey, KinematicUnit*> map = gpGame->getUnitManager()->getMap();
	std::map<UnitKey, KinematicUnit*>::iterator iter;

	for (iter = map.begin(); iter != map.end(); ++iter)
	{
		if (iter->second->getBoxCollider() != this)
			if (isColliding(iter->second->getBoxCollider()))
			{
				// Do something!
				std::cout << "\nFUCK, I'M HIT\n";
				//Bounce the other (iter->second) back!
			}
	}
}
