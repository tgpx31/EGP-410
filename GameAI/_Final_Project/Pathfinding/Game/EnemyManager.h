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
	void addEnemy(IDType mapID, Vector2D position);
	void deleteEnemy();
	inline int getRandEnemy() { return rand() % mEnemies.size(); };

	void draw();
	void update(double frameTime = 33.3f);

	inline float getVel() const { return mEnemyVel; };
	inline void setVel(const float& vel) { mEnemyVel = vel; };

	inline float getSpawnTime() const { return mRespawnTime; };
	inline void setSpawnTime(const float& timer) { mRespawnTime = timer; };

	inline int getStepReset() { return STEP_RESET_LIMIT; };
	inline void setStepReset(const int& val) { STEP_RESET_LIMIT = val; };

private:
	std::map<IDType, Enemy*> mEnemies;
	void cleanUp();

	float mEnemyVel;
	float mRespawnTime;

	Sprite* mNormalSprite;
	Sprite* mScaredSprite;

	int STEP_RESET_LIMIT = 5;
};