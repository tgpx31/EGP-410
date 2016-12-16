#include "InputManager.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"
#include "SaveMessage.h"
#include "LoadMessage.h"
#include "ChangeModeMessage.h"
#include "ToggleHelpMessage.h"
#include "EditGridMessage.h"
#include "ChangeMapMessage.h"
#include "Grid.h"
#include "Editor.h"

/* Initialize
* If any component fails install, return false
*/
bool InputManager::init()
{
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

	if (al_mouse_button_down(&mMouseState, 1))	//Left mouse click
	{
		Editor* pEditor = dynamic_cast<Editor*>(gpGame);
		GameMessage* pMessage = new EditGridMessage(mMouseState.x, mMouseState.y, pEditor->getEditGridValue());
		pEditor->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (al_mouse_button_down(&mMouseState, 2)) //Right mouse click
	{	
		Editor* pEditor = dynamic_cast<Editor*>(gpGame);
		GameMessage* pMessage = new EditGridMessage(mMouseState.x, mMouseState.y, CLEAR_VALUE);
		pEditor->getMessageManager()->addMessage(pMessage, 0);
	}
}

/* Get Input: Keyboard*/
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

		if (mEvent.type != ALLEGRO_EVENT_KEY_CHAR || mEvent.keyboard.repeat == true)
		{
			continue;
		}

		GameMessage* pMessage = NULL;

		switch (mEvent.keyboard.keycode)
		{
			case ALLEGRO_KEY_ESCAPE:
			{
				Editor* pEditor = dynamic_cast<Editor*>(gpGame);
				
				pMessage = new SaveMessage();
				pEditor->getMessageManager()->addMessage(pMessage, 0);

				pMessage = new ExitGameMessage();
				break;
			}
			case ALLEGRO_KEY_S:
				pMessage = new SaveMessage();
				break;
			case ALLEGRO_KEY_L:
				pMessage = new LoadMessage();
				break;
			case ALLEGRO_KEY_1:
				//Set editor to place wall blocks
				pMessage = new ChangeModeMessage(BLOCKING_VALUE);
				break;
			case ALLEGRO_KEY_2:
				//Set eidtor to place enemy spawn points
				pMessage = new ChangeModeMessage(ENEMY_SPAWN_VALUE);
				break;
			case ALLEGRO_KEY_3:
				//Set editor to place player spawn point
				pMessage = new ChangeModeMessage(PLAYER_SPAWN_VALUE);
				break;
			case ALLEGRO_KEY_4:
				//Set editor to place All-Mighty-Candy
				pMessage = new ChangeModeMessage(CANDY_VALUE);
				break;
			case ALLEGRO_KEY_F1:
				pMessage = new ToggleHelpMessage();
				break;
			case ALLEGRO_KEY_UP:
			{
				Editor* pEditor = dynamic_cast<Editor*>(gpGame);

				pMessage = new SaveMessage();
				pEditor->getMessageManager()->addMessage(pMessage, 0);

				pMessage = new ChangeMapMessage(pEditor->getCurrentMapID() + 1);
				pEditor->getMessageManager()->addMessage(pMessage, 0);

				pMessage = new LoadMessage(); //Doesn't add to message manager so below functionality still works
				break;
			}
			case ALLEGRO_KEY_DOWN:
			{
				Editor* pEditor = dynamic_cast<Editor*>(gpGame);

				pMessage = new SaveMessage();
				pEditor->getMessageManager()->addMessage(pMessage, 0);

				pMessage = new ChangeMapMessage(pEditor->getCurrentMapID() - 1);
				pEditor->getMessageManager()->addMessage(pMessage, 0);

				pMessage = new LoadMessage(); //Doesn't add to message manager so below functionality still works
				break;
			}
		}

		if (pMessage != NULL)
		{
			Editor* pEditor = dynamic_cast<Editor*>(gpGame);
			pEditor->getMessageManager()->addMessage(pMessage, 0);
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
