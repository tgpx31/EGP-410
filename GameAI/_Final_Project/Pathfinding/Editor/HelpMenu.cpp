#include "HelpMenu.h"
#include "Editor.h"
#include "Grid.h"

#include "allegro5\allegro_font.h"

#include <string>

HelpMenu::HelpMenu()
{
}

HelpMenu::~HelpMenu()
{
}

void HelpMenu::draw()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	
	ALLEGRO_FONT* pFont = pEditor->getFont();
	int lineHeight = al_get_font_line_height(pFont);

	std::string editString = "You are currently placing a ";
	std::string currentMap = "Current map: " + pEditor->getFilename();

	switch (pEditor->getEditGridValue())
	{
	case BLOCKING_VALUE:
		editString += "Wall";
		break;
	case ENEMY_SPAWN_VALUE:
		editString += "Enemy Spawn";
		break;
	case PLAYER_SPAWN_VALUE:
		editString += "Player Spawn";
		break;
	case CANDY_VALUE:
		editString += "Candy";
		break;
	case DOOR_VALUE:
		editString += "Door";
		break;
	}

	al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 0, ALLEGRO_ALIGN_LEFT, currentMap.c_str());
	al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 1, ALLEGRO_ALIGN_LEFT,  editString.c_str());
	al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 2, ALLEGRO_ALIGN_LEFT, "Press F1 to toggle help menu");

	if (pEditor->getShowHelp())
	{
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 3, ALLEGRO_ALIGN_LEFT, "Press 1 to select Wall");
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 4, ALLEGRO_ALIGN_LEFT, "Press 2 to select Enemy Spawn");
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 5, ALLEGRO_ALIGN_LEFT, "Press 3 to select Player Spawn");
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 6, ALLEGRO_ALIGN_LEFT, "Press 4 to select Candy");
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 7, ALLEGRO_ALIGN_LEFT, "Press 5 to select Door");
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 8, ALLEGRO_ALIGN_LEFT, "Press S to save current map");
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 9, ALLEGRO_ALIGN_LEFT, "Press L to load current map");
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 10, ALLEGRO_ALIGN_LEFT, "Press Up to increment current map");
		al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 11, ALLEGRO_ALIGN_LEFT, "Press Down to decrement current map");
	}
}