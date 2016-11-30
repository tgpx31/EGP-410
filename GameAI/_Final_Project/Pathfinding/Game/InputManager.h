#pragma once

/* Input Manager:
 * Handle all user input
 * convert to messages to affect game state
 */

#include "Trackable.h"
#include "allegro5\allegro.h"

class Vector2D;

class InputManager : public Trackable
{
private:
	ALLEGRO_EVENT_QUEUE* mpEventQ;		// Queue to check key events
	ALLEGRO_EVENT mEvent;				// Event in the Q
	ALLEGRO_MOUSE_STATE mMouseState;	// Check mouse input
	bool holdClick = false;				// Prevent holding mouse button
	bool startNode = true;				// Mandates a new start node for each calculated path

	void getMouseInput();				// Get mouse input
	void getKeyboardInput();			// Get Keyboard Input

	void cleanUp();						// Clean up allocated memory
	void drawFirst(Vector2D start);

public:
	InputManager() {};
	~InputManager() { cleanUp(); };

	bool init();
	void update();
};