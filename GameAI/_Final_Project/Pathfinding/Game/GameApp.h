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

enum SpriteType
{
	INVALID_SRITE_TYPE = -1,
	ENEMY_REG = 1,
	ENEMY_SCARED = 2,
	PLAYER = 3,
	COIN = 4,
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
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid() { return mpGrid; };
	inline GridGraph* getGridGraph() { return mpGridGraph; };

	void changeMethod(bool isAStar);
	void setPathfinding(GridPathfinder* pathfinder);

	inline KinematicUnit* getPlayer() { return mpPlayerUnit; };

private:
	GameMessageManager* mpMessageManager;
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph;
	DebugDisplay* mpDebugDisplay;

	GridPathfinder* mpPathfinder;

	InputManager* mpInputManager;

	bool mIsAStar = false;

	// Units
	UnitManager* mpUnitManager;
	KinematicUnit* mpPlayerUnit;
};

