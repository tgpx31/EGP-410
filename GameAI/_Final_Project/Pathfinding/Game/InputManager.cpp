#include "GameApp.h"
#include "InputManager.h"
#include "Vector2D.h"

#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "ExitGameMessage.h"
#include "ChangeMethodMessage.h"
#include "GridPathfinder.h"

#include "Grid.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

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

void InputManager::drawFirst(Vector2D start)
{
	// Draw the start node
	Vector2D ulPos = gpGameApp->getGrid()->getULCornerOfSquare(gpGameApp->getGrid()->getSquareIndexFromPixelXY((int)start.getX(), (int)start.getY()));


	al_draw_filled_rectangle(ulPos.getX(), ulPos.getY(), ulPos.getX() + 32, ulPos.getY() + 32, al_map_rgb(1, 255, 128));

	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 
				ulPos.getX() + gpGameApp->getGrid()->getSquareSize() / 4, ulPos.getY() + gpGameApp->getGrid()->getSquareSize() / 4,
				ALLEGRO_ALIGN_LEFT, "S");
}


/* Get Input: Mouse*/
void InputManager::getMouseInput()
{
	al_get_mouse_state(&mMouseState);
	static Vector2D lastPos(0.0f, 0.0f);

	if (al_mouse_button_down(&mMouseState, 1) && !holdClick)	// left mouse click
	{
		
		Vector2D pos(mMouseState.x, mMouseState.y);

		if (startNode)
		{
			lastPos = Vector2D(mMouseState.x, mMouseState.y);

			// Can you clear the path?
			gpGameApp->getPathfinder()->clearPath();
			gpGameApp->getPathfinder()->clearFinalPath();

			startNode = false;
		}
		else
		{
			Vector2D pos(mMouseState.x, mMouseState.y);

			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);

			startNode = true;
		}

		holdClick = true;
	}

	if (!startNode)
	{
		drawFirst(lastPos);
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

		if (mEvent.type != ALLEGRO_EVENT_KEY_CHAR || mEvent.keyboard.repeat == true)
		{
			continue;
		}

		switch (mEvent.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
		{
			GameMessage* aMessage = new ExitGameMessage();
			gpGameApp->getMessageManager()->addMessage(aMessage, 0);
			break;
		}

		/**
		*	WASD for PLAYER movement
		**/
		case ALLEGRO_KEY_W:
		{
			std::cout << "\nNO WASD YET W\n";
			/*GameMessage* aMessage = new ChangeMethodMessage(false);
			gpGameApp->getMessageManager()->addMessage(aMessage, 0);*/
			break;
		}

		case ALLEGRO_KEY_A:
		{
			std::cout << "\nNO WASD YET A\n";
			break;
		}

		case ALLEGRO_KEY_S:
		{
			std::cout << "\nNO WASD YET S\n";
			break;
		}

		case ALLEGRO_KEY_D:
		{
			std::cout << "\nNO WASD YET D\n";
			break;
		}

		/**
		*	I for INVINCIBLE PLAYER
		**/
		case ALLEGRO_KEY_I:
		{
			std::cout << "\nMAKE THE PLAYER INVINCIBLE\n";
			break;
		}

		/**
		*	P for PROPERTIES
		*	Up and Down arrows toggle through property list
		*	+/- to edit values
		**/

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
