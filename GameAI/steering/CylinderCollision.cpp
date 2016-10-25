#include "CylinderCollision.h"
#include "BoxCollision.h"

CylinderCollision::CylinderCollision(float x, float y, int radius)
{
	mPosition = Vector2D(x, y);
	mRadius = radius;

	std::cout << "\nCylinderCollider (circle) ADDED @ " << mPosition.getX() << ", "
		<< mPosition.getY() << " with RADIUS = " << mRadius << "\n";
}

CylinderCollision::CylinderCollision(Vector2D position, int radius)
{
	mPosition = position;
	mRadius = radius;

	std::cout << "\nCylinderCollider (circle) ADDED @ " << mPosition.getX() << ", "
		<< mPosition.getY() << " with RADIUS = " << mRadius << "\n";
}

bool CylinderCollision::isCollidingBoxes(BoxCollision * other)
{
	// Check if a box collider is colliding with your circle collider
	if (((other->getPos() - mPosition).getLength() <= mRadius) &&
		((other->getPos() - mPosition).getLength() >= -mRadius))
	{
		// In the radius
		return true;
	}

	return false;
}

bool CylinderCollision::isCollidingCylinders(CylinderCollision * other)
{
	return false;
}

void CylinderCollision::update(std::vector<BoxCollision*> boxes)
{
}
