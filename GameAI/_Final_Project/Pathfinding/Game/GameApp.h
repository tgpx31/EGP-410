#pragma once

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"

//forward declarations
class GraphicsBuffer;
class Sprite;

class GameMessageManager;
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class DebugDisplay;

class InputManager;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class UnitManager;
class KinematicUnit;
class GameMapManager;

class Player;
class EnemyManager;
class UserInterface;

enum SpriteType
{
	INVALID_SPRITE_TYPE = -1,
	ENEMY_REG = 1,
	ENEMY_SCARED = 2,
	PLAYER = 3,
	COIN = 4,
	CANDY = 5,
	DOOR = 6
};

class GameApp: public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	//accessors
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline GameMapManager* getGameMapManager() { return mpGameMapManager; };
	inline EnemyManager* getEnemyManager() { return mpEnemyManager; };

	inline int getCoinSpawnRate() { return mCoinSpawnRate; };
	inline Player* getPlayer() { return mpPlayer; };

	inline void setScore(int incVal) { mScore += incVal; std::cout << mScore << std::endl; };
	inline int getScore() { return mScore; };

	inline void stopUpdating() { mShouldUpdate = false; };
	inline UserInterface* getUI() const { return mpUI; };
private:
	GameMessageManager* mpMessageManager;
	EnemyManager* mpEnemyManager;

	InputManager* mpInputManager;
	GameMapManager* mpGameMapManager;

	void initMaps();
	void initGraphicsBuffers();
	void initSprites();

	// Units
	Player* mpPlayer;

	int mCoinSpawnRate;
	int mScore;

	bool mShouldUpdate;

	UserInterface* mpUI;
};