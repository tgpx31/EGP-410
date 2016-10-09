#pragma once

#include "Trackable.h"
#include <allegro5\allegro_font.h>
#include <iostream>
#include <vector>

#include "Game.h"


class Properties : public Trackable
{
private:
	// Currently selected property
	GameProperties mCurrentProperty;
	bool mShouldDisplay;

	// Text
	ALLEGRO_FONT* mpFont;
	int mSize;
	
	std::vector<std::string> mPropertyTexts;

public:
	Properties(ALLEGRO_FONT* font);
	~Properties();

	void toggleActive() { mShouldDisplay = !mShouldDisplay; };
	bool getActive() { return mShouldDisplay; };
	void setCurrentProperty(GameProperties prop) { mCurrentProperty = prop; };

	void draw();
	void update();
};