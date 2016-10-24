#pragma once

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <string>
#include "Wall.h"
#include <vector>

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class GameMessageManager;
class Timer;

class UnitManager;
class InputManager;
class BoxCollision;

class Properties;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

enum Behavior
{
	INVALID_BEHAVIOR = -1,
	DYNAMIC_SEEK = 0,
	DYNAMIC_ARRIVE = 1,
	WANDER_AND_SEEK = 2,
	WANDER_AND_FLEE = 3
};

enum GameProperties
{
	INVALID_PROPERTY = -1,
	ENEMY_VELOCITY = 0,
	REACTION_RADIUS = 1,
	ANGULAR_VELOCITY = 2,
	CHANGE_MAX_ACCEL = 3
};

class Game :public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline ALLEGRO_FONT* getFont() const { return mpFont; };

	inline KinematicUnit* getPlayerUnit() { return mpUnit; };//should be someplace else
	inline UnitManager* getUnitManager() { return mpUnitManager; }
	inline void setShouldExit(bool exit = true) { mShouldExit = exit; };
	std::vector<BoxCollision*> getWalls() { return mWalls; };

	Properties* getProperties();

private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	bool mShouldExit;

	//should be somewhere else
	ALLEGRO_FONT* mpFont;
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;

	KinematicUnit* mpUnit;

	UnitManager* mpUnitManager;
	InputManager* mpInputManager;

	std::vector<BoxCollision*> mWalls;

	Properties* mpPropertiesManager;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

