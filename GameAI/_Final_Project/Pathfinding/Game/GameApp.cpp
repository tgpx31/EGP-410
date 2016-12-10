#include <allegro5/allegro.h>
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"

#include "InputManager.h"
#include "UnitManager.h"
#include "KinematicUnit.h"
#include "GameMapManager.h"

const IDType BACKGROUND_ID = 0;
const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "../Editor/pathgrid.txt";

GameApp::GameApp()
:mpMessageManager(NULL)
,mpInputManager(NULL)
,mpUnitManager(NULL)
,mpPlayerUnit(NULL)
,mpGameMapManager(NULL)
{
	mLoopTargetTime = LOOP_TARGET_TIME;
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

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}

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
	mpGraphicsBufferManager->loadBuffer(PLAYER, "../Assets/Images/og_pac.png");
	mpGraphicsBufferManager->loadBuffer(COIN, "../Assets/Images/coin.png");
	mpGraphicsBufferManager->loadBuffer(DOOR, "../Assets/Images/door.png");
	mpGraphicsBufferManager->loadBuffer(CANDY, "../Assets/Images/candy.png");

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

	pBuffer = gpGameApp->getGraphicsBufferManager()->getBuffer(PLAYER);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(PLAYER, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
	}
	pBuffer = gpGameApp->getGraphicsBufferManager()->getBuffer(COIN);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(COIN, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
	}
	pBuffer = gpGameApp->getGraphicsBufferManager()->getBuffer(DOOR);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(DOOR, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
	}
	pBuffer = gpGameApp->getGraphicsBufferManager()->getBuffer(CANDY);
	if (pBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(CANDY, pBuffer, 0, 0, pBuffer->getWidth(), pBuffer->getHeight());
	}




	mpUnitManager = new UnitManager();
	mpUnitManager->addUnit(Vector2D(100, 100), mpSpriteManager->getSprite(ENEMY_REG));

	// Player Unit
	// There should be a function for this!
	// Initialize @ player spawn point for current level
	mpPlayerUnit = new KinematicUnit(mpSpriteManager->getSprite(PLAYER), Vector2D(0,0), 0, Vector2D(0,0), 0, 5.0f, 1.0f);

	mpGameMapManager = new GameMapManager();
	mpGameMapManager->loadMap(0, "../Assets/Maps/map0.txt");
	mpGameMapManager->loadMap(1, "../Assets/Maps/map1.txt");
	mpGameMapManager->loadMap(2, "../Assets/Maps/map2.txt");
	mpGameMapManager->loadMap(3, "../Assets/Maps/map3.txt");
	mpGameMapManager->setCurrentMap(0);

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpInputManager;
	mpInputManager = nullptr;

	delete mpUnitManager;
	mpUnitManager = nullptr;

	delete mpPlayerUnit;
	mpPlayerUnit = nullptr;

	delete mpGameMapManager;
	mpGameMapManager = NULL;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//Get Input
	mpInputManager->update();

	//Update
	mpMessageManager->processMessagesForThisframe();
	mpPlayerUnit->update();
	mpUnitManager->update();

	//Draw
	mpGameMapManager->drawCurrentMap();
	mpPlayerUnit->draw(mpGraphicsSystem->getBackBuffer());
	mpUnitManager->draw(mpGraphicsSystem);

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}