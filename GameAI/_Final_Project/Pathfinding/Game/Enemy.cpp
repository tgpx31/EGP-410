#include "Enemy.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "Player.h"

#include "StateMachine.h"
#include "EnemyChaseState.h"
#include "EnemyFleeState.h"
#include "EnemyWanderState.h"

#include "GameApp.h"
#include "PlayerDeathMessage.h"
#include "GameMessageManager.h"
#include "IncreaseScoreMessage.h"
#include "SoundSystem.h"

#include "AStarPathfinder.h"
#include "GameMapManager.h"
#include "DoorManager.h"
#include "Door.h"
#include "GameMap.h"
#include "Grid.h"
#include "GridGraph.h"

const int COLLISION_PIXEL_BUFFER = 4;

bool Enemy::checkCollidingPlayer()
{
	return (getCollider()->isCollidingCylinders(gpGameApp->getPlayer()->getCollider()));
}

bool Enemy::checkCollidingWalls()
{
	int topLeft = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + COLLISION_PIXEL_BUFFER, mpUnit->getPosition().getY() + COLLISION_PIXEL_BUFFER));
	int topRight = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() - COLLISION_PIXEL_BUFFER + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY() + COLLISION_PIXEL_BUFFER));
	int botLeft = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + COLLISION_PIXEL_BUFFER, mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight() - COLLISION_PIXEL_BUFFER));
	int botRight = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getValueAtIndex(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() - COLLISION_PIXEL_BUFFER + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight() - COLLISION_PIXEL_BUFFER));

	if ((topLeft == BLOCKING_VALUE) || (botLeft == BLOCKING_VALUE) || (topRight == BLOCKING_VALUE) || (botRight == BLOCKING_VALUE))
	{
		mpUnit->setPosition(mPreviousPosition);
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::recalculatePath()
{
	mElapsedTime = 0;
	Vector2D startPos = mpUnit->getPosition() + Vector2D(16, 16);
	setStart(startPos);
	setGoal(determineTarget());
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

Vector2D Enemy::determineTarget()
{
	Vector2D target(32, 32);
	
	if (mpStateMachine->getCurrentState() == 0)	// Wander
	{
		int rnd = std::rand() % 4;

		target = mpUnit->getPosition();

		switch (rnd)
		{
			case 0: // go up
				target += Vector2D(0, -256);
				break;
			case 1: // go down
				target += Vector2D(0, 256);
				break;
			case 2: // go left
				target += Vector2D(-256, 0);
				break;
			case 3: // go right
				target += Vector2D(256, 0);
				break;
		}
	}
	else if (mpStateMachine->getCurrentState() == 1) // Chase
	{
		target = gpGameApp->getPlayer()->getPosition() + Vector2D(16, 16);
	}
	else if (mpStateMachine->getCurrentState() == 2) // Flee
	{
		if (gpGameApp->getPlayer()->getPosition().getX() >= mpUnit->getPosition().getX())
		{
			target.setX(32); 
		}
		else
		{
			target.setX(gpGameApp->getGraphicsSystem()->getWidth() - 64);
		}

		if (gpGameApp->getPlayer()->getPosition().getY() >= mpUnit->getPosition().getY())
		{
			target.setY(32);
		}
		else
		{
			target.setY(gpGameApp->getGraphicsSystem()->getHeight() - 64);
		}

		target += Vector2D(16, 16);
	}

	return target;
}

void Enemy::doWander()
{
	mpAStar->clearPath();
	mpAStar->clearFinalPath();
	if (mElapsedTime >= mTimeToRecalculate)
	{
		mElapsedTime = 0;
		mpUnit->seek(determineTarget());
	}
	else if (checkCollidingWalls())
	{
		mpUnit->seek(determineTarget());
	}
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
		mpAStar->clearPath();
		mpAStar->clearFinalPath();
		mpUnit->seek(determineTarget());
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

void Enemy::updateMovement(float time)
{
	mpUnit->update(time);
	mpStateMachine->update();

	if (mpStateMachine->getCurrentState() == 0)
	{
		doWander();
	}
	else
	{
		doPathfinding();
	}

	mPreviousPosition = mpUnit->getPosition();
}

void Enemy::setSprite(bool isFlee)
{
	if (isFlee)
		mpUnit->setSprite(mpFleeSprite);
	else
		mpUnit->setSprite(mpNormalSprite);
}

void Enemy::changeMap(IDType mapID)
{
	mMapID = mapID;
	mpAStar->setGraph(gpGameApp->getGameMapManager()->getMap(mapID)->getGridGraph());
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
	mGetPathToDoor = true;

	mpNormalSprite = pNormalSprite;
	mpFleeSprite = pFleeSprite;
	
	mpUnit = new KinematicUnit(mpNormalSprite, position, 0.0f, Vector2D(0, 0), 0.0f, 80.0f);

	mpAStar = new AStarPathfinder(gpGameApp->getGameMapManager()->getMap(mMapID)->getGridGraph(), mapID);

	mpStateMachine = new StateMachine();
	mpStateMachine->addState(new EnemyWanderState(this));
	mpStateMachine->addState(new EnemyFleeState(this));
	mpStateMachine->addState(new EnemyChaseState(this));

	mpStateMachine->setInitialStateID(0);
	mpStateMachine->start();

	updateMovement(0);
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
	IDType playerMap = gpGameApp->getGameMapManager()->getCurrentMapID();

	if (mIsDead)
	{
		if (mElapsedTime >= mRespawnTime)
		{
			respawn();
		}
	}
	else if (mMapID == gpGameApp->getGameMapManager()->getCurrentMapID())
	{
		updateMovement(time);

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
	else if (mpStateMachine->getCurrentState() == 1 && playerMap != mMapID) // Chase state
	{
		//Determine door to path to
		IDType playerMap = gpGameApp->getGameMapManager()->getCurrentMapID();
		Door* doorTo = gpGameApp->getGameMapManager()->getMap(mMapID)->getDoorManager()->getDoorTo(playerMap);

		//Set the goal
		////do aster
		//mElapsedTime = 0;
		if (mGetPathToDoor)
		{
			Vector2D startPos = mpUnit->getPosition() + Vector2D(16, 16);
			setStart(startPos);
			setGoal(doorTo->getPosition());
			mpAStar->clearPath();
			mpAStar->clearFinalPath();
			mpAStar->findPath(goal, start);
			mStepIntoPathCounter = 1;
			mGetPathToDoor = false;
		}
		
		if (shouldMove())
		{
			++mStepIntoPathCounter;
		}
		if (mStepIntoPathCounter >= mpAStar->getFinalPath().size())
		{
			changeMap(doorTo->getMapTo());
			mpUnit->setPosition(doorTo->getConnectedDoor()->getPosition());
			mGetPathToDoor = true;
			return;
		}

		mpUnit->seek(gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid()->getULCornerOfSquare(mpAStar->getFinalPath()[mStepIntoPathCounter]->getId()));
		mpUnit->update(time);
		//go along path

		//if hit door teleport
	}
}

void Enemy::draw(bool isDebug)
{
	if (mMapID == gpGameApp->getGameMapManager()->getCurrentMapID() && !mIsDead)
	{
		if (isDebug)
		{
			mpAStar->drawVisualization(gpGameApp->getGameMapManager()->getMap(mMapID)->getGrid(), gpGameApp->getGraphicsSystem()->getBackBuffer(), true);
		}
		mpUnit->draw(gpGame->getGraphicsSystem()->getBackBuffer(), isDebug);
	}
}
