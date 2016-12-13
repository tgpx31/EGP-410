#include "CandyManager.h"
#include "Candy.h"

CandyManager::CandyManager()
{
}

CandyManager::~CandyManager()
{
	std::map<IDType, Candy*>::iterator iter;

	for (iter = mCandy.begin(); iter != mCandy.end(); iter++)
	{
		delete iter->second;
	}
}

void CandyManager::addCandy(IDType id, Candy* pCandy)
{
	std::map<IDType, Candy*>::iterator iter;

	iter = mCandy.find(id);

	if (iter != mCandy.end())
	{
		delete iter->second;
		mCandy.erase(id);
	}

	mCandy[id] = pCandy;
}

void CandyManager::createCandy(Vector2D position, Sprite* pSprite, float respawnTime)
{
	std::map<IDType, Candy*>::iterator iter;

	IDType id = mCandy.size() + 1;

	Candy* newCandy = new Candy(position, pSprite, respawnTime);

	mCandy[id] = newCandy;
}

void CandyManager::update(float time)
{
	std::map<IDType, Candy*>::iterator iter;

	for (iter = mCandy.begin(); iter != mCandy.end(); iter++)
	{
		iter->second->update(time);
	}
}

void CandyManager::draw()
{
	std::map<IDType, Candy*>::iterator iter;

	for (iter = mCandy.begin(); iter != mCandy.end(); iter++)
	{
		iter->second->draw();
	}
}
