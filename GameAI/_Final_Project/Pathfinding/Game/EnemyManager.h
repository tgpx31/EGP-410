#pragma once

#include "Trackable.h"
#include "Defines.h"
#include "Vector2D.h"
#include <map>

class Enemy;
class Sprite;
class GraphicsSystem;

class EnemyManager : public Trackable
{
public:
	EnemyManager(Sprite* spr1, Sprite* spr2);
	~EnemyManager();

	inline std::map<IDType, Enemy*> getMap() { return mEnemies; };
	void addEnemy(Vector2D position);
	void deleteEnemy();
	inline int getRandEnemy() { return rand() % mEnemies.size(); };

	void draw();
	void update(double frameTime = 33.3f);
private:
	std::map<IDType, Enemy*> mEnemies;
	void cleanUp();

	Sprite* mNormalSprite;
	Sprite* mScaredSprite;
};