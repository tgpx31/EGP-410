#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	ADD_UNIT_MESSAGE = 1,
	DELETE_UNIT_MESSAGE = 2,
	EXIT_GAME_MESSAGE = 3,
	TOGGLE_PROPERTIES_MESSAGE = 4,
	SELECT_PROPERTIES_MESSAGE = 5,
	CHANGE_CURRENT_PROPERTY_MESSAGE = 6
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};
