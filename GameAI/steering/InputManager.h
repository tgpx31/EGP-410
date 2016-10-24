#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Game.h"
#include "Vector2D.h"

#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "AddUnitMessage.h"
#include "DeleteUnitMessage.h"
#include "ExitGameMessage.h"
#include "TogglePropertiesMessage.h"
#include "SelectPropertiesMessage.h"
#include "ChangeCurrentPropertyMessage.h"

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

	ALLEGRO_EVENT_QUEUE* mpEventQ;
	ALLEGRO_EVENT mEvent;

public:
	InputManager(ALLEGRO_FONT* font = NULL);
	~InputManager();

	bool init();
	

	void update(double frameTime);
};

#endif