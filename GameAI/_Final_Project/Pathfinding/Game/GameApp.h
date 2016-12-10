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

enum SpriteType
{
	INVALID_SRITE_TYPE = -1,
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
	inline KinematicUnit* getPlayer() { return mpPlayerUnit; };

private:
	GameMessageManager* mpMessageManager;

	InputManager* mpInputManager;
	GameMapManager* mpGameMapManager;

	bool mIsAStar = false;

	// Units
	UnitManager* mpUnitManager;
	KinematicUnit* mpPlayerUnit;
};
