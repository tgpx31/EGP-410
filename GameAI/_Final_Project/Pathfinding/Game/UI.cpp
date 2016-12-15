#include "UI.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_primitives.h"
#include "Game.h"

const int SCORE_Y = 744;

UserInterface::UserInterface(ALLEGRO_FONT* font)
{
	mDisplayProperties = false;
	int mSize = 8;

	mActiveProperty = 0;
	mpFont = font;

	mProperties.push_back("");
	mProperties.push_back("");
	mProperties.push_back("");
	mProperties.push_back("");
	mProperties.push_back("");
	mProperties.push_back("");

	mScoreDisplay = "";

	std::cout << "\nUI Properties initialized\n";

	myColor = al_map_rgb(255, 255, 255);
	hiColor = al_map_rgb(255, 0, 0);
	scoreColor = al_map_rgb(252, 250, 133);
}

UserInterface::~UserInterface()
{
}

void UserInterface::draw()
{
	setStrings();

	if (mDisplayProperties)
	{
		drawProperties();
	}

	al_draw_text(gpGame->getFont(), scoreColor, 0, SCORE_Y, ALLEGRO_ALIGN_LEFT, mScoreDisplay.c_str());
}

void UserInterface::drawProperties()
{
	al_draw_filled_rectangle(0, 0, 400, 124, al_map_rgb(0, 0, 0));
	for (int i = 0; i < mProperties.size(); ++i)
	{
		if (i == mActiveProperty)
			al_draw_text(mpFont, hiColor, 4, 16 * i, 0, mProperties[i].c_str());
		else
			al_draw_text(mpFont, myColor, 4, 16 * i, 0, mProperties[i].c_str());
	}
}

void UserInterface::setStrings()
{
	mProperties[0] = "Player Speed: "				/*display the current max player speed here*/;
	mProperties[1] = "Enemy Speed: "				/*display enemy max velocity*/;
	mProperties[2] = "Enemy Respawn Timer: "		/*display total time needed to respawn dead enemy*/;
	mProperties[3] = "Enemy A* Calculation Delay: "	/*Tiles until recalc*/;
	mProperties[4] = "Candy Respawn Timer: "		/*Time for candy to respawn*/;
	mProperties[5] = "Player Invincible: "			/*True or false*/;

	mScoreDisplay = "SCORE: " /*add the score here*/;
}
