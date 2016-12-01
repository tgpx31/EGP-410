#pragma once

/* Input Manager:
* Handle all user input
* convert to messages to affect game state
*/

#include "Trackable.h"
#include "allegro5\allegro.h"

class InputManager : public Trackable
{
private:
	ALLEGRO_EVENT_QUEUE* mpEventQ;		// Queue to check key events
	ALLEGRO_EVENT mEvent;				// Event in the Q
	ALLEGRO_MOUSE_STATE mMouseState;	// Check mouse input
	bool holdClick = false;				// Prevent holding mouse button

	void getMouseInput();				// Get mouse input
	void getKeyboardInput();			// Get Keyboard Input

	void cleanUp();						// Clean up allocated memory

public:
	InputManager() {};
	~InputManager() { cleanUp(); };

	bool init();
	void update();
};