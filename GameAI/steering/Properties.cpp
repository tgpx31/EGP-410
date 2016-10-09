#include "Properties.h"

Properties::Properties(ALLEGRO_FONT* font)
{
	mShouldDisplay = false;
	int mSize = 8;

	mCurrentProperty = INVALID_PROPERTY;
	mpFont = font;

	mPropertyTexts.push_back("[V]elocity");
	mPropertyTexts.push_back("[R]eaction Radius");
	mPropertyTexts.push_back("[A]ngular Velocity");
	mPropertyTexts.push_back("[C]Max Accel");

	std::cout << "\nProperties UI initialized\n";
}

Properties::~Properties()
{
}

void Properties::draw()
{
	if (!mShouldDisplay)
	{
		return;
	}
	else if (mShouldDisplay)
	{
		// Draw the text
		//std::cout << "\nSHOULD BE DISPLAYING TEXT RIGHT NOW\n";
		ALLEGRO_COLOR myColor = al_map_rgb(255, 255, 255);
		ALLEGRO_COLOR hiColor = al_map_rgb(255, 0, 0);

		

		switch (mCurrentProperty)
		{
		case 0: 
			al_draw_text(mpFont, hiColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());
			break;
		case 1:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, hiColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());
			break;
		case 2:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, hiColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());
			break;
		case 3:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, hiColor, 0, 48, 0, mPropertyTexts[3].c_str());
			break;
		default:
			al_draw_text(mpFont, al_map_rgb(255, 255, 255), 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, al_map_rgb(255, 255, 255), 0, 12, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, al_map_rgb(255, 255, 255), 0, 24, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, al_map_rgb(255, 255, 255), 0, 36, 0, mPropertyTexts[3].c_str());
			return;
		}
	}
}

void Properties::update()
{
	// Set the activate property to a different color
}

