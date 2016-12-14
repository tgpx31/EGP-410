#include "Candy.h"
#include "Sprite.h"
#include "CylinderCollision.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "IncreaseScoreMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Player.h"

const int CANDY_SCORE = 50;

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
			// Make the player invincible

			// send a score message
			GameMessage* pMessage = new IncreaseScoreMessage(CANDY_SCORE);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);

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
