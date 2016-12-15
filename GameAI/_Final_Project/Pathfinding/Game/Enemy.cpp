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

#include "AStarPathfinder.h"
#include "GameMapManager.h"
#include "GameMap.h"
#include "Grid.h"
#include "GridGraph.h"

bool Enemy::checkCollidingPlayer()
{
	if (getCollider()->isCollidingCylinders(gpGameApp->getPlayer()->getCollider()))
		return true;

	return false;
}

void Enemy::setStart(Vector2D position)
{
	int startIndex = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(position.getX(), position.getY());
	start = gpGameApp->getGameMapManager()->getCurrentMap()->getGridGraph()->getNode(startIndex);
}

void Enemy::setGoal(Vector2D position)
{
	int goalIndex = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(position.getX(), position.getY());
	goal = gpGameApp->getGameMapManager()->getCurrentMap()->getGridGraph()->getNode(goalIndex);
}

void Enemy::doPathfinding()
{
	if (!mpAStar->getFinalPath().empty())
	{
		mpUnit->seek(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getULCornerOfSquare(mpAStar->getFinalPath()[mStepIntoPathCounter]->getId()));

		if (shouldMove())
		{
			++mStepIntoPathCounter;
		}
		if (mStepIntoPathCounter >= STEP_RESET_LIMIT)
		{
			setStart(mpUnit->getPosition());
			setGoal(gpGameApp->getPlayer()->getPosition());
			/*mpAStar->clearPath();
			mpAStar->clearFinalPath();*/
			mpAStar->findPath(goal, start);
			mStepIntoPathCounter = 1;
			mpUnit->seek(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getULCornerOfSquare(mpAStar->getFinalPath()[mStepIntoPathCounter]->getId()));
		}
	}
	else
		mpUnit->seek(gpGameApp->getPlayer()->getPosition());
}

bool Enemy::shouldMove()
{
	int topLeft = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX(), mpUnit->getPosition().getY());
	int topRight = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY());
	int botLeft = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX(), mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight());
	int botRight = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX() + mpUnit->getSprite()->getWidth(), mpUnit->getPosition().getY() + mpUnit->getSprite()->getHeight());

	int gID = mpAStar->getFinalPath()[mStepIntoPathCounter]->getId();

	int pUL = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX(), gpGameApp->getPlayer()->getPosition().getY());
	int pUR = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX() + gpGameApp->getPlayer()->getUnit()->getSprite()->getWidth(), gpGameApp->getPlayer()->getPosition().getY());
	int pBL = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX(), gpGameApp->getPlayer()->getPosition().getY() + gpGameApp->getPlayer()->getUnit()->getSprite()->getHeight());
	int pBR = gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX() + gpGameApp->getPlayer()->getUnit()->getSprite()->getWidth(), gpGameApp->getPlayer()->getPosition().getY() + gpGameApp->getPlayer()->getUnit()->getSprite()->getHeight());

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

Enemy::Enemy(Sprite* pNormalSprite, Sprite* pFleeSprite)
{
	mpNormalSprite = pNormalSprite;
	mpFleeSprite = pFleeSprite;
	
	mpUnit = new KinematicUnit(mpNormalSprite, Vector2D(100, 100), 0.0f, Vector2D(0, 0), 0.0f, .8f);

	mpStateMachine = new StateMachine();

	mpAStar = new AStarPathfinder(gpGameApp->getGameMapManager()->getCurrentMap()->getGridGraph());
	
	setStart(mpUnit->getPosition());
	setGoal(gpGameApp->getPlayer()->getPosition());
	
	mpAStar->findPath(start, goal);
	mPath = mpAStar->getFinalPath();
	mStepIntoPathCounter = 1;
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
	//mpStateMachine->update();
	mpUnit->update(time);
	//mpUnit->seek(gpGameApp->getPlayer()->getPosition());

	// for the path, seek the first node if new path
	// on arrival, seek next node
	// calculate new path on node 3
	// start over
	//if (!mPath.empty())
	doPathfinding();

	if (checkCollidingPlayer())
	{
		std::cout << "Hit the player" << std::endl;
		// Player death
		GameMessage* pMessage = new PlayerDeathMessage();
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
}

void Enemy::draw()
{
	mpAStar->drawVisualization(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid(), gpGameApp->getGraphicsSystem()->getBackBuffer(), true);
	mpUnit->draw(gpGame->getGraphicsSystem()->getBackBuffer());
}
