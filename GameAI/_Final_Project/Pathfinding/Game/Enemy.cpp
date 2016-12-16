#include "Enemy.h"
#include "KinematicUnit.h"
#include "StateMachine.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "Player.h"

#include "GameApp.h"
#include "PlayerDeathMessage.h"
#include "GameMessageManager.h"
#include "IncreaseScoreMessage.h"
#include "SoundSystem.h"

#include "AStarPathfinder.h"
#include "GameMapManager.h"
#include "GameMap.h"
#include "Grid.h"
#include "GridGraph.h"

bool Enemy::checkCollidingPlayer()
{
	return (getCollider()->isCollidingCylinders(gpGameApp->getPlayer()->getCollider()));
}

void Enemy::recalculatePath()
{
	mElapsedTime = 0;
	Vector2D startPos = mpUnit->getPosition() + Vector2D(16, 16);
	setStart(startPos);
	setGoal(gpGameApp->getPlayer()->getPosition() + Vector2D(16, 16));
	mpAStar->clearPath();
	mpAStar->clearFinalPath();
	mpAStar->findPath(goal, start);
	mStepIntoPathCounter = 1;
}

void Enemy::kill()
{
	GameMessage* pMessage = new IncreaseScoreMessage(100);
	gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	mIsDead = true;
	mElapsedTime = 0;
}

void Enemy::respawn()
{
	mMapID = mOriginalMapID;
	mpUnit->setPosition(mOriginalPosition);
	mIsDead = false;
	mElapsedTime = 0;
	recalculatePath();
}

void Enemy::setStart(Vector2D position)
{
	int startIndex = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(position.getX(), position.getY());
	start = gpGameApp->getGameMapManager()->getMap(mMapID)->getGridGraph()->getNode(startIndex);
}

void Enemy::setGoal(Vector2D position)
{
	int goalIndex = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(position.getX(), position.getY());
	goal = gpGameApp->getGameMapManager()->getMap(mMapID)->getGridGraph()->getNode(goalIndex);
}

void Enemy::doPathfinding()
{
	if (mStepIntoPathCounter >= STEP_RESET_LIMIT || mElapsedTime > mTimeToRecalculate)
	{
		recalculatePath();
	}

	if (mpAStar->getFinalPath().size() <= 0 || mStepIntoPathCounter >= mpAStar->getFinalPath().size() - 1)
	{
		mpUnit->seek(gpGameApp->getPlayer()->getPosition());
	}
	else
	{
		if (shouldMove())
		{
			++mStepIntoPathCounter;
		}
		mpUnit->seek(gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getULCornerOfSquare(mpAStar->getFinalPath()[mStepIntoPathCounter]->getId()));
	}
}

bool Enemy::shouldMove()
{
	int topLeft = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX(), mpUnit->getPosition().getY());
	int topRight = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY());
	int botLeft = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX(), mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight());
	int botRight = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight());

	int gID = mpAStar->getFinalPath()[mStepIntoPathCounter]->getId();

	int pUL = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX(), gpGameApp->getPlayer()->getPosition().getY());
	int pUR = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX() + gpGameApp->getPlayer()->getUnit()->getSprite()->getWidth(), gpGameApp->getPlayer()->getPosition().getY());
	int pBL = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX(), gpGameApp->getPlayer()->getPosition().getY() + gpGameApp->getPlayer()->getUnit()->getSprite()->getHeight());
	int pBR = gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX() + gpGameApp->getPlayer()->getUnit()->getSprite()->getWidth(), gpGameApp->getPlayer()->getPosition().getY() + gpGameApp->getPlayer()->getUnit()->getSprite()->getHeight());

	return (((topLeft == gID ||
		topRight == gID ||
		botLeft == gID ||
		botRight == gID))
		&&
		(topLeft != pUL ||
			topRight != pUR ||
			botLeft != pBL ||
			botRight != pBR));
}

Enemy::Enemy(IDType mapID, Vector2D position, Sprite* pNormalSprite, Sprite* pFleeSprite, float timeToRecalculate)
{
	mMapID = mapID;
	mOriginalMapID = mapID;

	mOriginalPosition = position;

	mTimeToRecalculate = timeToRecalculate;
	mRespawnTime = 10.0f;
	mElapsedTime = 0;
	
	mIsDead = false;

	mpNormalSprite = pNormalSprite;
	mpFleeSprite = pFleeSprite;
	
	mpUnit = new KinematicUnit(mpNormalSprite, position, 0.0f, Vector2D(0, 0), 0.0f, 80.0f);

	mpStateMachine = new StateMachine();

	mpAStar = new AStarPathfinder(gpGameApp->getGameMapManager()->getMap(mMapID)->getGridGraph(), mapID);
	mStepIntoPathCounter = 1;
	
	setStart(mpUnit->getPosition());
	setGoal(gpGameApp->getPlayer()->getPosition());
	
	mpAStar->findPath(start, goal);
	mPath = mpAStar->getFinalPath();
	// Build a path to the player, and seek each node iteratively
}

Enemy::~Enemy()
{
	delete mpUnit;
	mpUnit = NULL;

	delete mpStateMachine;
	mpStateMachine = NULL;

	delete mpAStar;
	mpAStar = NULL;
}

void Enemy::update(float time)
{
	mElapsedTime += time;

	if (mIsDead)
	{
		if (mElapsedTime >= mRespawnTime)
		{
			respawn();
		}
	}
	else if (mMapID == gpGameApp->getGameMapManager()->getCurrentMapID())
	{
		mpUnit->update(time);

		doPathfinding();

		if (checkCollidingPlayer())
		{
			if (gpGameApp->getPlayer()->getInvincible())
			{
				kill();
			}
			else
			{
				GameMessage* pMessage = new PlayerDeathMessage();
				gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			}
		}
	}
}

void Enemy::draw()
{
	if (mMapID == gpGameApp->getGameMapManager()->getCurrentMapID() && !mIsDead)
	{
		mpAStar->drawVisualization(gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid(), gpGameApp->getGraphicsSystem()->getBackBuffer(), true);
		mpUnit->draw(gpGame->getGraphicsSystem()->getBackBuffer());
	}
}
