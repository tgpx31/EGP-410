#include <allegro5/allegro.h>
#include "InputManager.h"
#include "Game.h"
#include "KinematicUnit.h"
#include "Kinematic.h"

InputManager::InputManager(ALLEGRO_FONT* font)
{
	mpFont = font;
}

InputManager::~InputManager()
{
	cleanUp();
}

bool InputManager::init()
{
	// Initialize all needed for input

	if (!al_install_keyboard())
	{
		printf("Keyboard not installed!\n");
		return false;
	}

	if (!al_install_mouse())
	{
		printf("Mouse not installed!\n");
		return false;
	}

	return true;
}

void InputManager::cleanUp()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

void InputManager::getMouseInput()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		Vector2D pos(mouseState.x, mouseState.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//create mouse text
	std::stringstream mousePos;
	mousePos << mouseState.x << ":" << mouseState.y;

	//write text at mouse position
	al_draw_text(mpFont, al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());
}

bool InputManager::getKeyboardInput()
{
	//get current keyboard state
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	// put keyboard inputs here

	// When you read an input...
	// send a message:

	
	if(al_key_down( &keyState, ALLEGRO_KEY_A ) )
	{
	GameMessage* pMessage = new AddUnitMessage(gpGame->getPlayerUnit()->getPosition(), false);
	MESSAGE_MANAGER->addMessage( pMessage, 0 );
	}
	

	//if escape key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::update(double frameTime)
{
	getMouseInput();
	return (getKeyboardInput());
}
