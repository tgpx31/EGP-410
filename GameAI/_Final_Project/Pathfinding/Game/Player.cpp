#include "Player.h"
#include "KinematicUnit.h"
#include "StateMachine.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "GameMapManager.h"
#include "GameMap.h"
#include "Grid.h"

Player::Player(Sprite* pSprite)
{
	mpUnit = new KinematicUnit(pSprite, Vector2D(0, 0), 0.0f, Vector2D(0, 0), 0.0f);
}

Player::~Player()
{
	delete mpUnit;
	mpUnit = NULL;
}

void Player::setState(PlayerMovementState state)
{
	mLastState = mCurrentState;
	mCurrentState = state;
}

void Player::update(float time)
{
	if (mCurrentState != mLastState)
	{
		switch (mCurrentState)
		{
			case GOING_UP:
				mpUnit->setVelocity(Vector2D(0, -100));
				mpUnit->setOrientation(0.5f * PI);
				break;
			case GOING_DOWN:
				mpUnit->setVelocity(Vector2D(0, 100));
				mpUnit->setOrientation(1.5f * PI);
				break;
			case GOING_LEFT:
				mpUnit->setVelocity(Vector2D(-100, 0));
				mpUnit->setOrientation(0.0f);
				break;
			case GOING_RIGHT:
				mpUnit->setVelocity(Vector2D(100, 0));
				mpUnit->setOrientation(PI);
				break;
			default:
				break;
		}
	}

	mpUnit->update(time);
	
	//Do collision detections with walls here
}

void Player::draw()
{
	mpUnit->draw(gpGame->getGraphicsSystem()->getBackBuffer());
}