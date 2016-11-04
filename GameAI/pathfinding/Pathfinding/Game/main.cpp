/*main.cpp
 *	Adapted from: Example program for the Allegro library, by Shawn Hargreaves.
 *	Sets up all systems and runs the main game loop until it is time to quit.
 *
 *	Dean Lawson
 *	Champlain College
 *	2011
 *
 */
#define ALLEGRO_USE_CONSOLE //allows the console to be used
#include <allegro5/allegro.h>
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

#include "Game.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Timer.h"
#include "MemoryTracker.h"
#include <PerformanceTracker.h>

PerformanceTracker* gpPerformanceTracker = NULL;
GameApp* gpGameApp = NULL;

int main(void)
{
	// Downcasting to allow calling getMessageManager in input system
	gpPerformanceTracker = new PerformanceTracker();

	gpGame = new GameApp();
	gpGameApp = dynamic_cast<GameApp*>(gpGame);
	gpGame->init();

	GraphicsBuffer* pWallpaper = new GraphicsBuffer( "wallpaper.bmp" );//should "live" someplace else


	bool shouldExit = false;

	while( !shouldExit )
	{
		gpGame->beginLoop();
		gpGame->processLoop();
		shouldExit = gpGame->endLoop();
	}

	//cleanup
	delete pWallpaper;
	gpGame->cleanup();
	delete gpGame;
	gpGameApp = nullptr;

	delete gpPerformanceTracker;

	gMemoryTracker.reportAllocations( std::cout );

	system("pause");

	return 0;
}

