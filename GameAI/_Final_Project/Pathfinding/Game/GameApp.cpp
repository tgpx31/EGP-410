#include <allegro5/allegro.h>
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"

#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"

#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"

#include <fstream>
#include <vector>

#include "InputManager.h"

#include "UnitManager.h"

const IDType BACKGROUND_ID = 0;
const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "../Editor/pathgrid.txt";

GameApp::GameApp()
:mpMessageManager(NULL)
,mpGrid(NULL)
,mpGridGraph(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
,mpInputManager(NULL)
,mpUnitManager(NULL)
{
}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpMessageManager = new GameMessageManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	std::ifstream theStream( gFileName );
	mpGrid->load( theStream );

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();

	mpPathfinder = new DijkstraPathfinder(mpGridGraph);

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder );
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpInputManager = new InputManager();
	if (!mpInputManager->init())
	{
		printf("InputManager failed to init!\n");
		return false;
	}

	// Init the unit manager
	// Load the default sprites from buffers
	mpGraphicsBufferManager->loadBuffer(ENEMY_REG, "../Assets/Images/og_ghost.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_SCARED, "../Assets/Images/scared_ghost.png");

	GraphicsBuffer* pBuffer = gpGameApp->getGraphicsBufferManager()->getBuffer(ENEMY_REG);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_REG, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
	}
	pBuffer = gpGameApp->getGraphicsBufferManager()->getBuffer(ENEMY_SCARED);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_SCARED, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
	}

	mpUnitManager = new UnitManager();

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	delete mpInputManager;
	mpInputManager = nullptr;

	delete mpUnitManager;
	mpUnitManager = nullptr;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw( *pBackBuffer );
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer, mIsAStar);
#endif

	

	mpDebugDisplay->draw( pBackBuffer );

	mpMessageManager->processMessagesForThisframe();

	mpInputManager->update();

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}

void GameApp::changeMethod(bool isAStar)
{
	if (isAStar)
	{
		AStarPathfinder* pAStarPathfinder = new AStarPathfinder(mpGridGraph);
		setPathfinding(pAStarPathfinder);
		mIsAStar = isAStar;
	}
	else if (!isAStar)
	{
		DijkstraPathfinder* pDijkstraPathfinder = new DijkstraPathfinder(mpGridGraph);
		setPathfinding(pDijkstraPathfinder);
		mIsAStar = isAStar;
	}
}

void GameApp::setPathfinding(GridPathfinder * pathfinder)
{
	// Delete the old pathfinder and display
	delete mpPathfinder;
	delete mpDebugDisplay;

	// Set to the new instance
	mpPathfinder = pathfinder;

	// reinitialize the debug display, same way as in init
	PathfindingDebugContent* pDebugContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pDebugContent);
}
