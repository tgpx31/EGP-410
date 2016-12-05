#pragma once

#include "Game.h"
#include <fstream>

/*Editor - class to hold all application related info.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class GraphicsBuffer;
class Sprite;
class Grid;
class GridVisualizer;
class GraphicsBuffer;
class InputManager;
class GameMessageManager;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Editor: public Game
{
public:
	Editor();
	virtual ~Editor();

	inline Grid* getGrid() { return mpGrid; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline InputManager* getInputManager() { return mpInputManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };

	inline int getEditGridValue() { return mEditGridValue; };

	inline std::string getFilename() { return FILE_NAME; };

	inline void setEditGridValue(int value) { mEditGridValue = value; };

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	void saveGrid( std::ofstream& theStream );
	void loadGrid( std::ifstream& theStream );

private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	InputManager* mpInputManager;
	GameMessageManager* mpMessageManager;

	int mEditGridValue;

	const std::string FILE_NAME = "pathgrid.txt";
};