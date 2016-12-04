#pragma once

#include "GameMessage.h"

enum EDIT_MODES
{
	WALL,
	ENEMY_SPAWN,
	PLAYER_SPAWN,
	CANDY
};

class ChangeModeMessage : public GameMessage
{
private:
	EDIT_MODES mMode;

public:
	ChangeModeMessage(EDIT_MODES mode);
	~ChangeModeMessage();

	void process();
};