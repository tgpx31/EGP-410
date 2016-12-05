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
	
	int editGridValue = pEditor->getEditGridValue();
	
	ALLEGRO_FONT* pFont = pEditor->getFont();
	int lineHeight = al_get_font_line_height(pFont);

	std::string editString;

	//TODO: Make this display current edit string
	al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 0, ALLEGRO_ALIGN_LEFT, "Current Edit Value is: 0");

	//TODO: Add conditional help menu information
	al_draw_text(pFont, al_map_rgb(255, 255, 255), 0, lineHeight * 1, ALLEGRO_ALIGN_LEFT, "Press ~ to toggle help menu");
}