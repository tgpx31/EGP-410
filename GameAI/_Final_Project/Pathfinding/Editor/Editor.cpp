#include <fstream>
#include <allegro5/allegro_primitives.h>

#include "Game.h"
#include "Editor.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"

#include "InputManager.h"
#include "GameMessageManager.h"

using namespace std;

const int GRID_SQUARE_SIZE = 32;
const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;

Editor::Editor()
:Game()
,mpGrid(NULL)
,mpGridVisualizer(NULL)
,mpInputManager(NULL)
,mpMessageManager(NULL)
,mEditGridValue(BLOCKING_VALUE)
,mCurrentMapID(0)
{
}

Editor::~Editor()
{
	cleanup();
}

bool Editor::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpMessageManager = new GameMessageManager();

	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);

	mpGridVisualizer = new GridVisualizer( mpGrid );

	mpInputManager = new InputManager();
	mpInputManager->init();

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}
	
	mpMasterTimer->start();
	return true;
}

void Editor::cleanup()
{
	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpInputManager;
	mpInputManager = NULL;

	delete mpMessageManager;
	mpMessageManager = NULL;
}

void Editor::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void Editor::processLoop()
{
	mpInputManager->update();
	mpMessageManager->processMessagesForThisframe();

	//copy to back buffer
	mpGridVisualizer->draw(*(mpGraphicsSystem->getBackBuffer()));

	//should be last thing in processLoop
	Game::processLoop();
}

bool Editor::endLoop()
{
	return Game::endLoop();
}

void Editor::saveGrid( ofstream& theStream )
{
	mpGrid->save( theStream );
}

void Editor::loadGrid( std::ifstream& theStream )
{
	mpGrid->load(theStream);
}
