#include "Properties.h"

Properties::Properties(ALLEGRO_FONT* font)
{
	mShouldDisplay = false;
	int mSize = 12;

	mCurrentProperty = INVALID_PROPERTY;
	mpFont = font;

	mPropertyTexts.push_back("Velocity");
	mPropertyTexts.push_back("Reaction Radius");
	mPropertyTexts.push_back("Angular Velocity");
	mPropertyTexts.push_back("Wander Rotation");

	std::cout << "\nProperties UI initialized\n";
}

Properties::~Properties()
{
}
