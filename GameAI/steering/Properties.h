#pragma once

#include "Trackable.h"
#include "Game.h"


class Properties : public Trackable
{
private:
	// Currently selected property
	GameProperties mCurrentProperty;
	bool mShouldDisplay;

	// Text
public:
	Properties();
	~Properties();

	void draw();
	void update();
};