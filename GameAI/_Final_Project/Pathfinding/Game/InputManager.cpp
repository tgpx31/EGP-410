#include "InputManager.h"
#include "GameApp.h"
#include "Vector2D.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"
#include "SetCurrentMapMessage.h"
#include "SetPlayerStateMessage.h"
#include "TogglePropertiesMessage.h"
#include "TogglePlayerInvincibilityMessage.h"
#include "EditPropertyMessage.h"
#include "Player.h"
#include "UI.h"

/* Initialize
 * If any component fails install, return false
 */
bool InputManager::init()
{
	holdClick = false;

	// Initialize Allegro
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

/* CleanUp
 * Get rid of the memory allocations and prevent leaks
 */
void InputManager::cleanUp()
{
	al_unregister_event_source(mpEventQ, al_get_keyboard_event_source());
	al_destroy_event_queue(mpEventQ);

	al_uninstall_keyboard();
	al_uninstall_mouse();
}

/* Get Input: Mouse*/
void InputManager::getMouseInput()
{
	al_get_mouse_state(&mMouseState);
	static Vector2D lastPos(0.0f, 0.0f);

	if (al_mouse_button_down(&mMouseState, 1) && !holdClick)	// left mouse click
	{
		std::cout << "Left mouse button down" << std::endl;
		holdClick = true;
	}

	// If they aren't holding the button down, let them click again
	if (!al_mouse_button_down(&mMouseState, 1))
	{
		holdClick = false;
	}
}

/* Get Input: Keyboard*/
void InputManager::getKeyboardInput()
{
	while (!al_event_queue_is_empty(mpEventQ))
	{
		al_wait_for_event(mpEventQ, &mEvent);

		if (mEvent.type != ALLEGRO_EVENT_KEY_CHAR || mEvent.keyboard.repeat == true)
		{
			continue;
		}

		switch (mEvent.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
		{
			GameMessage* pMessage = new ExitGameMessage();
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}

		/**
		*	WASD for PLAYER movement
		**/
		case ALLEGRO_KEY_W:
		{
			GameMessage* pMessage = new SetPlayerStateMessage(GOING_UP);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}

		case ALLEGRO_KEY_A:
		{
			GameMessage* pMessage = new SetPlayerStateMessage(GOING_LEFT);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}

		case ALLEGRO_KEY_S:
		{
			GameMessage* pMessage = new SetPlayerStateMessage(GOING_DOWN);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}

		case ALLEGRO_KEY_D:
		{
			GameMessage* pMessage = new SetPlayerStateMessage(GOING_RIGHT);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}

		/**
		*	I for INVINCIBLE PLAYER
		**/
		case ALLEGRO_KEY_I:
		{
			std::cout << "\nMAKE THE PLAYER INVINCIBLE\n";
			GameMessage* pMessage;
			if (gpGameApp->getPlayer()->getInvincible())
				pMessage = new TogglePlayerIvincibilityMessage(false);
			else
				pMessage = new TogglePlayerIvincibilityMessage(true);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}

		case ALLEGRO_KEY_1:
		{
			std::cout << "Switch to map0" << std::endl;
			GameMessage* pMessage = new SetCurrentMapMessage(0);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}
		case ALLEGRO_KEY_2:
		{
			std::cout << "Switch to map1" << std::endl;
			GameMessage* pMessage = new SetCurrentMapMessage(1);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}
		case ALLEGRO_KEY_3:
		{
			std::cout << "Switch to map2" << std::endl;
			GameMessage* pMessage = new SetCurrentMapMessage(2);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}
		case ALLEGRO_KEY_4:
		{
			std::cout << "Switch to map3" << std::endl;
			GameMessage* pMessage = new SetCurrentMapMessage(3);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}

		/**
		*	F1 for PROPERTIES
		*	Up and Down arrows toggle through property list
		*	+/- to edit values
		**/
		case ALLEGRO_KEY_F1:
		{
			//gpGameApp->toggleUpdating();
			GameMessage* pMessage = new TogglePropertiesMessage();
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			break;
		}

		if (gpGameApp->getUI()->isDisplaying())
		{
			case ALLEGRO_KEY_UP:
			{
				// go up in active properties
				if (gpGameApp->getUI()->getActiveProperty() <= 0 )
					gpGameApp->getUI()->setActiveProperty(5);
				else
					gpGameApp->getUI()->setActiveProperty(gpGameApp->getUI()->getActiveProperty() - 1);
				break;
			}
			case ALLEGRO_KEY_DOWN:
			{
				// go up in active properties
				if (gpGameApp->getUI()->getActiveProperty() >= 5)
					gpGameApp->getUI()->setActiveProperty(0);
				else
					gpGameApp->getUI()->setActiveProperty(gpGameApp->getUI()->getActiveProperty() + 1);
				break;
			}
			case ALLEGRO_KEY_PAD_PLUS:
			{
				GameMessage* pMessage = new EditPropertyMessage(gpGameApp->getUI()->getActiveProperty(), true);
				gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				break;
			}
			case ALLEGRO_KEY_PAD_MINUS:
			{
				GameMessage* pMessage = new EditPropertyMessage(gpGameApp->getUI()->getActiveProperty(), false);
				gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				break;
			}

		}


		/**
		*	X for DEBUG MODE
		**/

		default:
			std::cout << "\nYou hit the DEFAULT CASE\n";
			break;
		}
	}
}

/* Update
 * Check for the input
 */
void InputManager::update()
{
	getKeyboardInput();
	getMouseInput();
}
