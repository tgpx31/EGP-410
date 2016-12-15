#include "EnemyManager.h"
#include "Enemy.h"
#include "KinematicUnit.h"
#include "GraphicsSystem.h"
#include "GameApp.h"
#include "Player.h"
#include "AStarPathfinder.h"
EnemyManager::EnemyManager(Sprite* spr1, Sprite* spr2)
{
	mNormalSprite = spr1;
	mScaredSprite = spr2;
}

EnemyManager::~EnemyManager()
{
	cleanUp();
}

void EnemyManager::addEnemy(IDType mapID, Vector2D position)
{
	Enemy* pEnemy;
	pEnemy = new Enemy(mapID, mNormalSprite, mScaredSprite);
	//Vector2D gridPos = Vector2D(int(position.getX() / 32) * 32, int(position.getY() / 32) * 32);
	pEnemy->getUnit()->setPosition(position);
	//pEnemy->getUnit()->seek(NULL);

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

void EnemyManager::draw()
{
	// Traverse map w/ iterator
	std::map<IDType, Enemy*>::iterator iter;

	for (iter = mEnemies.begin(); iter != mEnemies.end(); ++iter)
	{
		iter->second->draw();
	}
}

void EnemyManager::update(double frameTime)
{
	// Traverse map w/ iterator
	std::map<IDType, Enemy*>::iterator iter;

	for (iter = mEnemies.begin(); iter != mEnemies.end(); ++iter)
	{
		iter->second->update(frameTime);
	}
}