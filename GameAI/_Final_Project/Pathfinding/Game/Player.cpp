#include "Player.h"
#include "KinematicUnit.h"
#include "StateMachine.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "GameMapManager.h"
#include "GameMap.h"
#include "Grid.h"
#include "GameMessageManager.h"
#include "IncreaseScoreMessage.h"

const int COLLISION_PIXEL_BUFFER = 4;
const int COIN_SCORE = 10;

Player::Player(Sprite* pSprite)
{
	mpUnit = new KinematicUnit(pSprite, Vector2D(100, 100), 0.0f, Vector2D(0, 0), 0.0f, 100.0f);
	mCurrentState = INVALID_MOVEMENT_STATE;
	mPreviousPosition = mpUnit->getPosition();
	mInvincible = false;
}

Player::~Player()
{
	delete mpUnit;
	mpUnit = NULL;
}

void Player::checkCollision()
{
	int topLeft = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + COLLISION_PIXEL_BUFFER, mpUnit->getPosition().getY() + COLLISION_PIXEL_BUFFER));
	int topRight = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() - COLLISION_PIXEL_BUFFER + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY() + COLLISION_PIXEL_BUFFER));
	int botLeft = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + COLLISION_PIXEL_BUFFER, mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight() - COLLISION_PIXEL_BUFFER));
	int botRight = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() - COLLISION_PIXEL_BUFFER + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight() - COLLISION_PIXEL_BUFFER));


	if ((topLeft == BLOCKING_VALUE) || (botLeft == BLOCKING_VALUE) || (topRight == BLOCKING_VALUE) || (botRight == BLOCKING_VALUE))
	{
		mpUnit->setPosition(mPreviousPosition);
	}
	else if (topLeft == COIN_VALUE)
	{
		gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->setValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + COLLISION_PIXEL_BUFFER, mpUnit->getPosition().getY() + COLLISION_PIXEL_BUFFER), CLEAR_VALUE);
		GameMessage* pMessage = new IncreaseScoreMessage(COIN_SCORE);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (topRight == COIN_VALUE)
	{
		gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->setValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() - COLLISION_PIXEL_BUFFER + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY() + COLLISION_PIXEL_BUFFER), CLEAR_VALUE);
		GameMessage* pMessage = new IncreaseScoreMessage(COIN_SCORE);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (botLeft == COIN_VALUE)
	{
		gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->setValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + COLLISION_PIXEL_BUFFER, mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight() - COLLISION_PIXEL_BUFFER), CLEAR_VALUE);
		GameMessage* pMessage = new IncreaseScoreMessage(COIN_SCORE);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (botRight == COIN_VALUE)
	{
		gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->setValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() - COLLISION_PIXEL_BUFFER + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight() - COLLISION_PIXEL_BUFFER), CLEAR_VALUE);
		GameMessage* pMessage = new IncreaseScoreMessage(COIN_SCORE);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
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

void Player::setPosition(Vector2D position)
{
	mpUnit->setPosition(position);
}

void Player::update(float time)
{
	mpUnit->update(time);
	checkCollision();
	mPreviousPosition = mpUnit->getPosition();
}

void Player::draw()
{
	mpUnit->draw(gpGame->getGraphicsSystem()->getBackBuffer());
}