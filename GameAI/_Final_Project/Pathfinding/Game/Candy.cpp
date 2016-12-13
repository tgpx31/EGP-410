#include "Candy.h"
#include "Sprite.h"
#include "CylinderCollision.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Player.h"

Candy::Candy(Vector2D position, Sprite * pSprite, float respawnTime)
{
	mPosition = position;
	mpSprite = pSprite;
	mRespawnTime = respawnTime;
	mElapsedTime = 0;
	mIsActive = true;

	mpCollider = new CylinderCollision(mPosition, 16);
}

Candy::~Candy()
{
	delete mpCollider;
	mpCollider = NULL;
}

void Candy::update(float time)
{
	if (mIsActive)
	{
		if (mpCollider->isCollidingCylinders(gpGameApp->getPlayer()->getCollider()))
		{
			mIsActive = false;
		}
	}
	else
	{
		mElapsedTime += time;

		if (mElapsedTime >= mRespawnTime)
		{			
			mElapsedTime = 0;
			mIsActive = true;
		}
	}
}

void Candy::draw()
{
	if (mIsActive)
	{
		mpSprite->draw(*gpGame->getGraphicsSystem()->getBackBuffer(), mPosition.getX(), mPosition.getY());
	}
}
