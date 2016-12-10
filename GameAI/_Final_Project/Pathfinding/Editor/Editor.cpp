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
#include "LoadMessage.h"
#include "HelpMenu.h"

using namespace std;

const int GRID_SQUARE_SIZE = 32;
const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;

Editor::Editor()
:Game()
,mpGrid(NULL)
,mpGridVisualizer(NULL)
,mpInputManager(NULL)
,mpMessageManager(NULL)
,mpHelpMenu(NULL)
,mEditGridValue(BLOCKING_VALUE)
,mCurrentMapID(0)
,mShowHelp(false)
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
	mpGridVisualizer->setEditor(true);

	mpInputManager = new InputManager();
	mpInputManager->init();

	mpHelpMenu = new HelpMenu();

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(BLOCKING_VALUE, "../Assets/Images/blocking.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_SPAWN_VALUE, "../Assets/Images/og_ghost.png");
	mpGraphicsBufferManager->loadBuffer(PLAYER_SPAWN_VALUE, "../Assets/Images/og_pac.png");
	mpGraphicsBufferManager->loadBuffer(CANDY_VALUE, "../Assets/Images/candy.png");
	mpGraphicsBufferManager->loadBuffer(DOOR_VALUE, "../Assets/Images/door.png");

	//setup sprites
	GraphicsBuffer* pBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight() );
		std::cout << "Background sprite loaded" << std::endl;
	}

	pBuffer = mpGraphicsBufferManager->getBuffer(BLOCKING_VALUE);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(BLOCKING_VALUE, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
		std::cout << "Blocking sprite loaded" << std::endl;
	}

	pBuffer = mpGraphicsBufferManager->getBuffer(ENEMY_SPAWN_VALUE);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_SPAWN_VALUE, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
		std::cout << "Enemy spawn sprite loaded" << std::endl;
	}

	pBuffer = mpGraphicsBufferManager->getBuffer(PLAYER_SPAWN_VALUE);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(PLAYER_SPAWN_VALUE, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
		std::cout << "Player spawn sprite loaded" << std::endl;
	}

	pBuffer = mpGraphicsBufferManager->getBuffer(CANDY_VALUE);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(CANDY_VALUE, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
		std::cout << "Candy sprite loaded" << std::endl;
	}

	pBuffer = mpGraphicsBufferManager->getBuffer(DOOR_VALUE);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(DOOR_VALUE, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
		std::cout << "Door sprite loaded" << std::endl;
	}

	std::ifstream theStream(getFilename());
	loadGrid(theStream);
	theStream.close();
	mpGridVisualizer->setModified();
	std::cout << "Loaded map from " << getFilename() << std::endl;

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

	delete mpHelpMenu;
	mpHelpMenu = NULL;
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

	mpGridVisualizer->draw(*(mpGraphicsSystem->getBackBuffer()));
	mpHelpMenu->draw();

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
