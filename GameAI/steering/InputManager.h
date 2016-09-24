#pragma once

#include "Trackable.h"

/* Input Manager:
 * Handle Keyboard and mouse inputs
 * Convert to messages/events that affect game state
 */

class InputManager : public Trackable
{
private:


	void cleanUp();

public:
	InputManager();
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