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

#include "Player.h"
#include "EnemyManager.h"

const IDType BACKGROUND_ID = 0;

GameApp::GameApp()
:mpMessageManager(NULL)
,mpInputManager(NULL)
,mpGameMapManager(NULL)
,mpEnemyManager(NULL)
,mpPlayer(NULL)
,mCoinSpawnRate(25)
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

	initGraphicsBuffers();
	initSprites();	

	mpInputManager = new InputManager();
	if (!mpInputManager->init())
	{
		printf("InputManager failed to init!\n");
		return false;
	}
	
	// Init the enemymanager
	mpEnemyManager = new EnemyManager(mpSpriteManager->getSprite(ENEMY_REG), mpSpriteManager->getSprite(ENEMY_SCARED));

	mpGameMapManager = new GameMapManager();
	initMaps();

	mpPlayer = new Player(mpSpriteManager->getSprite(PLAYER));
	// Spawn enemies based on the spawn points in the map
	// TESTING ADD/DELETE
	mpEnemyManager->addEnemy(Vector2D(200,200));
	/*mpEnemyManager->addEnemy(Vector2D(300, 200));
	mpEnemyManager->deleteEnemy();*/

	

	mScore = 0;

	mpMasterTimer->start();

	mShouldUpdate = true;
	return true;
}

void GameApp::initGraphicsBuffers()
{
	mpGraphicsBufferManager->loadBuffer(BACKGROUND_ID, "wallpaper.bmp");

	mpGraphicsBufferManager->loadBuffer(ENEMY_REG, "../Assets/Images/og_ghost.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_SCARED, "../Assets/Images/scared_ghost.png");
	mpGraphicsBufferManager->loadBuffer(PLAYER, "../Assets/Images/og_pac.png");
	mpGraphicsBufferManager->loadBuffer(COIN, "../Assets/Images/coin.png");
	mpGraphicsBufferManager->loadBuffer(DOOR, "../Assets/Images/door.png");
	mpGraphicsBufferManager->loadBuffer(CANDY, "../Assets/Images/candy.png");
}

void GameApp::initSprites()
{
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(BACKGROUND_ID);
	if (pBackGroundBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight());
	}

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
}

void GameApp::initMaps()
{
	mpGameMapManager->loadMap(0, "../Assets/Maps/map0.txt");
	mpGameMapManager->loadMap(1, "../Assets/Maps/map1.txt");
	mpGameMapManager->loadMap(2, "../Assets/Maps/map2.txt");
	mpGameMapManager->loadMap(3, "../Assets/Maps/map3.txt");
	mpGameMapManager->connectDoors();
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpInputManager;
	mpInputManager = nullptr;

	delete mpGameMapManager;
	mpGameMapManager = NULL;

	delete mpEnemyManager;
	mpEnemyManager = NULL;

	delete mpPlayer;
	mpPlayer = NULL;

	delete mpSpriteManager;
	mpSpriteManager = NULL;
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
	mpGameMapManager->update(LOOP_TARGET_TIME / 1000.0F);
	//mpEnemy->update(LOOP_TARGET_TIME / 1000.0F);
	if (mShouldUpdate)
	{
		mpPlayer->update(LOOP_TARGET_TIME / 1000.0F);
		mpEnemyManager->update(LOOP_TARGET_TIME/ 10.0f);
	}
	
	mpEnemyManager->draw();
	//Draw
	mpGameMapManager->drawCurrentMap();
	//mpEnemy->draw();
	mpPlayer->draw();

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}