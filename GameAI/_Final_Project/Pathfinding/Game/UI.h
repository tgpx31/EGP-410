#pragma once

#include "Trackable.h"
#include <vector>
#include <string>

#include <allegro5\allegro_font.h>

class UserInterface : public Trackable
{
private:
	// Font formatting
	ALLEGRO_FONT* mpFont;
	int mSize;

	// Other Properties
	bool mDisplayProperties;
	int mActiveProperty;
	std::vector<std::string> mProperties;

	// Score
	std::string mScoreDisplay;

	ALLEGRO_COLOR scoreColor;
	ALLEGRO_COLOR myColor;
	ALLEGRO_COLOR hiColor;
public:
	UserInterface(ALLEGRO_FONT* font);
	~UserInterface();

	inline void toggleProperties() { mDisplayProperties = !mDisplayProperties; };
	inline bool isDisplaying() const { return mDisplayProperties; };

	inline void setActiveProperty(const int& prop) { mActiveProperty = prop; };
	inline int getActiveProperty() const { return mActiveProperty; };

	void draw();
	void drawProperties();

	void update() {};
	void setStrings();
};