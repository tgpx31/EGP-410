#include "Door.h"
#include "CylinderCollision.h"
#include "Sprite.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"

Door::Door(Vector2D position, Sprite * pSprite)
{
	mPosition = position;
	mpSprite = pSprite;
	mpCollider = new CylinderCollision(mPosition, 16);

	mMapTo = 0;
	mConnectedDoor = NULL;
}

Door::~Door()
{
	delete mpCollider;
	mpCollider = NULL;
}

void Door::draw()
{
	mpSprite->draw(*gpGame->getGraphicsSystem()->getBackBuffer(), mPosition.getX(), mPosition.getY());
}
