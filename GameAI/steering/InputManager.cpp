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
	al_get_mouse_state(&mMouseState);

	// outdated. from last assignment
	//if (al_mouse_button_down(&mMouseState, 1))	//left mouse click
	//{
	//	Vector2D pos(mMouseState.x, mMouseState.y);
	//	GameMessage* pMessage = new PlayerMoveToMessage(pos);
	//	MESSAGE_MANAGER->addMessage(pMessage, 0);
	//}

	//create mouse text
	std::stringstream mousePos;
	mousePos << mMouseState.x << ":" << mMouseState.y;

	//write text at mouse position
	al_draw_text(mpFont, al_map_rgb(255, 255, 255), mMouseState.x, mMouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());
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
			// Use this to spawn boids
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_I)
			{
				al_get_mouse_state(&mMouseState);

				GameMessage* pMessage = new AddUnitMessage(Vector2D(mMouseState.x, mMouseState.y), BOIDS_BEHAVIOR);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}


			// Properties
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_P)
			{
				GameMessage* pMessage = new TogglePropertiesMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_C)
			{
				GameMessage* pMessage = new SelectPropertiesMessage(COHESION_WEIGHT);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_S && !(al_key_down(&keyState, ALLEGRO_KEY_LCTRL) || al_key_down(&keyState, ALLEGRO_KEY_RCTRL)))
			{
				GameMessage* pMessage = new SelectPropertiesMessage(SEPERATION_WEIGHT);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_A)
			{
				GameMessage* pMessage = new SelectPropertiesMessage(ALIGNMENT_WEIGHT);
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

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_N)
			{
				GameMessage* pMessage = new SelectPropertiesMessage(ANGULAR_VELOCITY);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_M)
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

			// Save the weights
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_S && (al_key_down(&keyState, ALLEGRO_KEY_LCTRL) || al_key_down(&keyState, ALLEGRO_KEY_RCTRL))) // Allegro doesn't let you check two of the ALLEGRO_EVENTS at the same time
			{
				GameMessage* pMessage = new SaveWeightsMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			// Deletion key inputs
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_D)
			{
				if (gpGame->getUnitManager()->getMap().empty())
				{
					GameMessage* aMessage = new ExitGameMessage();
					MESSAGE_MANAGER->addMessage(aMessage, 0);
				}
				else
				{
					GameMessage* pMessage = new DeleteUnitMessage();
					MESSAGE_MANAGER->addMessage(pMessage, 0);
				}
			}

			// Exit game key input
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				GameMessage* aMessage = new ExitGameMessage();
				MESSAGE_MANAGER->addMessage(aMessage, 0);
			}
		}
	}
}

void InputManager::update(double frameTime)
{
	getMouseInput();
	getKeyboardInput();
}
