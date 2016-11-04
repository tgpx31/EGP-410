#include "GameApp.h"
#include "InputManager.h"
#include "Vector2D.h"

#include "GameMessageManager.h"
#include "PathToMessage.h"

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

	if (al_mouse_button_down(&mMouseState, 1) && !holdClick)	// left mouse click
	{
		static Vector2D lastPos(0.0f, 0.0f);
		Vector2D pos(mMouseState.x, mMouseState.y);
		if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
		{
			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			lastPos = pos;
		}
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
	//get current keyboard state
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	// put keyboard inputs here

	// When you read an input...
	// send a message:

	while (!al_event_queue_is_empty(mpEventQ))
	{
		al_wait_for_event(mpEventQ, &mEvent);

		// Exit game key input
		if (mEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			/*GameMessage* aMessage = new ExitGameMessage();
			MESSAGE_MANAGER->addMessage(aMessage, 0);*/
			gpGame->markForExit();
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
