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
	// Referencing http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
	// for help, as I have never done Circle to Box collision before

	// check the center of the box
	Vector2D rectangleCenterPoint = other->getCenterPoint();
	Vector2D rectDimensions = other->getDimensions();
	Vector2D circleDist = Vector2D(std::abs(mPosition.getX() - rectangleCenterPoint.getX()), std::abs(mPosition.getY() - rectangleCenterPoint.getY()));

	float cornerDistSquared = (std::pow((circleDist.getX() - rectDimensions.getX() / 2), 2)) + (std::pow(circleDist.getY() - rectDimensions.getY() / 2, 2));

	if (circleDist.getX() > (rectDimensions.getX() / 2 + mRadius))
		{ return false; }
	if (circleDist.getY() > (rectDimensions.getY() / 2 + mRadius))
		{ return false; }

	if (circleDist.getX() <= (rectDimensions.getX() / 2))
		{ return true; }
	if (circleDist.getY() <= (rectDimensions.getY() / 2))
		{ return true; }

	return (cornerDistSquared <= mRadius * mRadius);
}

bool CylinderCollision::isCollidingCylinders(CylinderCollision * other)
{
	// Checking the two circles are intersecting
	// Mathematical formula courtesy of http://math.stackexchange.com/questions/275514/two-circles-overlap
	return (std::pow(mRadius + other->getRadius(), 2) >= (std::pow(other->getPos().getX() - mPosition.getX(), 2)) + (std::pow(mPosition.getY() - other->getPos().getY(), 2)));
}

void CylinderCollision::update(std::vector<BoxCollision*> boxes)
{
}