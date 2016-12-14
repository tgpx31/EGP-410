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

Enemy::Enemy(Sprite* pNormalSprite, Sprite* pFleeSprite)
{
	mpNormalSprite = pNormalSprite;
	mpFleeSprite = pFleeSprite;
	
	mpUnit = new KinematicUnit(mpNormalSprite, Vector2D(100, 100), 0.0f, Vector2D(0, 0), 0.0f, .8f);

	mpStateMachine = new StateMachine();

	mpAStar = new AStarPathfinder(gpGameApp->getGameMapManager()->getCurrentMap()->getGridGraph());
	
	setStart(mpUnit->getPosition());
	setGoal(gpGameApp->getPlayer()->getPosition());
	//start = new Node(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(mpUnit->getPosition().getX(), mpUnit->getPosition().getY()));
	//goal = new Node(gpGameApp->getGameMapManager()->getCurrentMap()->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayer()->getPosition().getX(), gpGameApp->getPlayer()->getPosition().getY()));
	mpAStar->findPath(start, goal);
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
	mpUnit->seek(gpGameApp->getPlayer()->getPosition());
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
