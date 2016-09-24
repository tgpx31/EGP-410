#include <allegro5/allegro.h>
#include "InputManager.h"

InputManager::InputManager()
{
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

void InputManager::update(double frameTime)
{
}
