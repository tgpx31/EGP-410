#include <allegro5/allegro.h>
#include "InputManager.h"

#include "Game.h"

#include "KinematicUnit.h"
#include "Kinematic.h"
#include "UnitManager.h"

#include <map>

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

	mpEventQ = al_create_event_queue();
	al_register_event_source(mpEventQ, al_get_keyboard_event_source());

	return true;
}

void InputManager::cleanUp()
{
	al_unregister_event_source(mpEventQ, al_get_keyboard_event_source());
	al_destroy_event_queue(mpEventQ);

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

void InputManager::getKeyboardInput()
{
	//get current keyboard state
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	// put keyboard inputs here

	// When you read an input...
	// send a message:

	while (!al_event_queue_is_empty(mpEventQ))
	{

		al_wait_for_event(mpEventQ, &mEvent);

		// Keyboard
		if (mEvent.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_F)
			{
				GameMessage* pMessage = new AddUnitMessage(gpGame->getPlayerUnit()->getPosition(), WANDER_AND_FLEE);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_S)
			{
				GameMessage* pMessage = new AddUnitMessage(gpGame->getPlayerUnit()->getPosition(), WANDER_AND_SEEK);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_I)
			{
				GameMessage* pMessage = new TogglePropertiesMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_V)
			{
				GameMessage* pMessage = new SelectPropertiesMessage(ENEMY_VELOCITY);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_R)
			{
				GameMessage* pMessage = new SelectPropertiesMessage(REACTION_RADIUS);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_A)
			{
				GameMessage* pMessage = new SelectPropertiesMessage(ANGULAR_VELOCITY);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_C)
			{
				GameMessage* pMessage = new SelectPropertiesMessage(CHANGE_MAX_ACCEL);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_PAD_PLUS)
			{
				GameMessage* pMessage = new ChangeCurrentPropertyMessage(true, 10);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS)
			{
				GameMessage* pMessage = new ChangeCurrentPropertyMessage(false, 10);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}


			if (mEvent.keyboard.keycode == ALLEGRO_KEY_D)
			{
				GameMessage* pMessage = new DeleteUnitMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);

				if (gpGame->getUnitManager()->getMap().empty())
				{
					//return true;
					GameMessage* aMessage = new ExitGameMessage();
					MESSAGE_MANAGER->addMessage(aMessage, 0);
				}

			}

			//if escape key was down then exit the loop
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				//return true;
				GameMessage* aMessage = new ExitGameMessage();
				MESSAGE_MANAGER->addMessage(aMessage, 0);
			}
		}
	}


	/*if(al_key_down( &keyState, ALLEGRO_KEY_F ) )
	{
	GameMessage* pMessage = new AddUnitMessage(gpGame->getPlayerUnit()->getPosition(), WANDER_AND_FLEE);
	MESSAGE_MANAGER->addMessage( pMessage, 0 );
	}

	if (al_key_down(&keyState, ALLEGRO_KEY_S))
	{
		GameMessage* pMessage = new AddUnitMessage(gpGame->getPlayerUnit()->getPosition(), WANDER_AND_SEEK);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	
	if (al_key_down(&keyState, ALLEGRO_KEY_D))
	{
		GameMessage* pMessage = new DeleteUnitMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);

		if (gpGame->getUnitManager()->getMap().empty())
		{
			//return true;
			GameMessage* aMessage = new ExitGameMessage();
			MESSAGE_MANAGER->addMessage(aMessage, 0);
		}
			
	}

	//if escape key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		//return true;
		GameMessage* aMessage = new ExitGameMessage();
		MESSAGE_MANAGER->addMessage(aMessage, 0);
	}*/
}

void InputManager::update(double frameTime)
{
	getMouseInput();
	getKeyboardInput();
}
