#pragma once

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	PATH_TO_MESSAGE = 1,
	EXIT_GAME_MESSAGE = 2,
	CHANGE_METHOD_MESSAGE = 3,
	SET_CURRENT_MAP_MESSAGE,
	SET_PLAYER_STATE_MESSAGE,
	SET_PLAYER_POSITION_MESSAGE,
	INCREASE_SCORE_MESSAGE,
	ADD_UNIT_MESSAGE,
	DELETE_UNIT_MESSAGE,
	PLAYER_DEATH_MESSAGE
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


