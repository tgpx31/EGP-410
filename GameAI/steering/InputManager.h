#pragma once

#include "Trackable.h"

#include "Game.h"

#include "Defines.h"
#include "Vector2D.h"

#include "GameMessage.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"

#include "AddUnitMessage.h"
#include "DeleteUnitMessage.h"
#include "ExitGameMessage.h"

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

