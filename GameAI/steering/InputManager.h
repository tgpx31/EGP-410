#pragma once

#include "Trackable.h"

#include "Defines.h"
#include "Vector2D.h"
#include "GameMessage.h"
#include "PlayerMoveToMessage.h"
#include "Game.h"
#include "GameMessageManager.h"

#include <sstream>

/* Input Manager:
 * Handle Keyboard and mouse inputs
 * Convert to messages/events that affect game state
 */

class InputManager : public Trackable
{
private:
	void cleanUp();
	void getMouseInput();
	void getKeyboardInput();

	ALLEGRO_FONT* mpFont;

public:
	InputManager(ALLEGRO_FONT* font = NULL);
	~InputManager();

	bool init();
	

	void update(double frameTime);
};

// When you read an input...
// send a message:

/*
if( al_mouse_button_down( &mouseState, 1 ) )//left mouse click
	{
		Vector2D pos( mouseState.x, mouseState.y );
		GameMessage* pMessage = new PlayerMoveToMessage( pos );
		MESSAGE_MANAGER->addMessage( pMessage, 0 );
	}
*/