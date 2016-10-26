#include "Properties.h"
#include "UnitManager.h"
#include "KinematicUnit.h"

Properties::Properties(ALLEGRO_FONT* font)
{
	mShouldDisplay = false;
	int mSize = 8;

	mCurrentProperty = INVALID_PROPERTY;
	mpFont = font;

	mPropertyTexts.push_back("");
	mPropertyTexts.push_back("");
	mPropertyTexts.push_back("");
	mPropertyTexts.push_back("");
	mPropertyTexts.push_back("");
	mPropertyTexts.push_back("");
	mPropertyTexts.push_back("");

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

		// Update the strings
		mPropertyTexts[0] = "[V]elocity: " + std::to_string(gpGame->getUnitManager()->getMaxVel());

		if (!gpGame->getUnitManager()->getMap().empty())
			mPropertyTexts[1] = "[R]eaction Radius: " + std::to_string(gpGame->getUnitManager()->getMap().begin()->second->getRadius());
		else
			mPropertyTexts[1] = "[R]eaction Radius: NO UNITS";

		mPropertyTexts[2] = "[N]Angular Velocity: ";
		mPropertyTexts[3] = "[M]ax Accel: ";
		mPropertyTexts[4] = "[C]ohesion Weight: ";
		mPropertyTexts[5] = "[S]eperation Weight: ";
		mPropertyTexts[6] = "[A]lignment Weight: ";

		switch (mCurrentProperty)
		{
		case 0: 
			al_draw_text(mpFont, hiColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());

			al_draw_text(mpFont, myColor, 0, 64, 0, mPropertyTexts[4].c_str());
			al_draw_text(mpFont, myColor, 0, 80, 0, mPropertyTexts[5].c_str());
			al_draw_text(mpFont, myColor, 0, 96, 0, mPropertyTexts[6].c_str());
			break;
		case 1:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, hiColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());

			al_draw_text(mpFont, myColor, 0, 64, 0, mPropertyTexts[4].c_str());
			al_draw_text(mpFont, myColor, 0, 80, 0, mPropertyTexts[5].c_str());
			al_draw_text(mpFont, myColor, 0, 96, 0, mPropertyTexts[6].c_str());
			break;
		case 2:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, hiColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());

			al_draw_text(mpFont, myColor, 0, 64, 0, mPropertyTexts[4].c_str());
			al_draw_text(mpFont, myColor, 0, 80, 0, mPropertyTexts[5].c_str());
			al_draw_text(mpFont, myColor, 0, 96, 0, mPropertyTexts[6].c_str());
			break;
		case 3:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, hiColor, 0, 48, 0, mPropertyTexts[3].c_str());

			al_draw_text(mpFont, myColor, 0, 64, 0, mPropertyTexts[4].c_str());
			al_draw_text(mpFont, myColor, 0, 80, 0, mPropertyTexts[5].c_str());
			al_draw_text(mpFont, myColor, 0, 96, 0, mPropertyTexts[6].c_str());
			break;
		case 4:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());

			al_draw_text(mpFont, hiColor, 0, 64, 0, mPropertyTexts[4].c_str());
			al_draw_text(mpFont, myColor, 0, 80, 0, mPropertyTexts[5].c_str());
			al_draw_text(mpFont, myColor, 0, 96, 0, mPropertyTexts[6].c_str());
			break;
		case 5:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());

			al_draw_text(mpFont, myColor, 0, 64, 0, mPropertyTexts[4].c_str());
			al_draw_text(mpFont, hiColor, 0, 80, 0, mPropertyTexts[5].c_str());
			al_draw_text(mpFont, myColor, 0, 96, 0, mPropertyTexts[6].c_str());
			break;
		case 6:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());

			al_draw_text(mpFont, myColor, 0, 64, 0, mPropertyTexts[4].c_str());
			al_draw_text(mpFont, myColor, 0, 80, 0, mPropertyTexts[5].c_str());
			al_draw_text(mpFont, hiColor, 0, 96, 0, mPropertyTexts[6].c_str());
			break;
		default:
			al_draw_text(mpFont, myColor, 0, 0, 0, mPropertyTexts[0].c_str());
			al_draw_text(mpFont, myColor, 0, 16, 0, mPropertyTexts[1].c_str());
			al_draw_text(mpFont, myColor, 0, 32, 0, mPropertyTexts[2].c_str());
			al_draw_text(mpFont, myColor, 0, 48, 0, mPropertyTexts[3].c_str());

			al_draw_text(mpFont, myColor, 0, 64, 0, mPropertyTexts[4].c_str());
			al_draw_text(mpFont, myColor, 0, 80, 0, mPropertyTexts[5].c_str());
			al_draw_text(mpFont, myColor, 0, 96, 0, mPropertyTexts[6].c_str());
			return;
		}
	}
}

void Properties::update()
{
	// Set the activate property to a different color
}

