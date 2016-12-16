#include "EnemyManager.h"
#include "Enemy.h"
#include "KinematicUnit.h"
#include "GraphicsSystem.h"
#include "GameApp.h"
#include "Player.h"
#include "AStarPathfinder.h"
#include "KinematicUnit.h"

EnemyManager::EnemyManager(Sprite* spr1, Sprite* spr2)
{
	mNormalSprite = spr1;
	mScaredSprite = spr2;

	mRespawnTime = 10.0f;
	mEnemyVel = 80.0f;
	STEP_RESET_LIMIT = 5;
}

EnemyManager::~EnemyManager()
{
	cleanUp();
}

void EnemyManager::addEnemy(IDType mapID, Vector2D position)
{
	Enemy* pEnemy;
	pEnemy = new Enemy(mapID, position, mNormalSprite, mScaredSprite, 2.0f);
	
	//pEnemy->getUnit()-

	pEnemy->setGoal(gpGameApp->getPlayer()->getPosition());
	pEnemy->setStart(position);

	pEnemy->getAStar()->clearPath();
	pEnemy->getAStar()->findPath(pEnemy->getGoal(), pEnemy->getStart());
	// Add the new enemy to the map
	mEnemies[mEnemies.size()] = pEnemy;
}

void EnemyManager::deleteEnemy()
{
	std::map<IDType, Enemy*>::iterator iter = mEnemies.begin();
	std::advance(iter, rand() % mEnemies.size());

	// If it exists..
	if (iter != mEnemies.end())
	{
		//std::cout << "\nDELETED UNIT " << key <<  "\n";
		delete iter->second;
		mEnemies.erase(iter);
	}
}

void EnemyManager::cleanUp()
{
	// Traverse map w/ iterator
	std::map<IDType, Enemy*>::iterator iter;

	// Clean all entries
	for (iter = mEnemies.begin(); iter != mEnemies.end(); ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}
	mEnemies.clear();
}

void EnemyManager::draw(bool drawLine)
{
	// Traverse map w/ iterator
	std::map<IDType, Enemy*>::iterator iter;

	for (iter = mEnemies.begin(); iter != mEnemies.end(); ++iter)
	{
		iter->second->draw(drawLine);
	}
}

void EnemyManager::update(double frameTime)
{
	// Traverse map w/ iterator
	std::map<IDType, Enemy*>::iterator iter;

	for (iter = mEnemies.begin(); iter != mEnemies.end(); ++iter)
	{
		iter->second->update(frameTime);
		// respawn time
		iter->second->setSpawnTime(mRespawnTime);
		// velocity
		iter->second->getUnit()->setMaxVelocity(mEnemyVel);
		// AStar
		iter->second->setStepReset(STEP_RESET_LIMIT);
	}
}