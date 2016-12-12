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
	mpUnit = new KinematicUnit(pSprite, Vector2D(0, 0), 0.0f, Vector2D(0, 0), 0.0f, 100.0f);
	mCurrentState = INVALID_MOVEMENT_STATE;
}

Player::~Player()
{
	delete mpUnit;
	mpUnit = NULL;
}

bool Player::checkCoinCollision()
{
	// Check the position of the collider

	// Old, not working method
	return mpUnit->checkSpecificCollision(COIN_VALUE);
}

void Player::setState(PlayerMovementState state)
{
	mCurrentState = state;

	switch (mCurrentState)
	{
	case GOING_UP:
		mpUnit->setVelocity(Vector2D(0, -100));
		break;
	case GOING_DOWN:
		mpUnit->setVelocity(Vector2D(0, 100));
		break;
	case GOING_LEFT:
		mpUnit->setVelocity(Vector2D(-100, 0));
		break;
	case GOING_RIGHT:
		mpUnit->setVelocity(Vector2D(100, 0));
		break;
	default:
		break;
	}
}

void Player::update(float time)
{
	mpUnit->update(time);
	
	// Collision stuff
	if (checkCoinCollision())
	{
		std::cout << "\nYou got a coin";
	}
}

void Player::draw()
{
	mpUnit->draw(gpGame->getGraphicsSystem()->getBackBuffer());
}