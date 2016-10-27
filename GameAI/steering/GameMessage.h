#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	ADD_UNIT_MESSAGE = 1,					// Add a Unit with a specific behaivor
	DELETE_UNIT_MESSAGE = 2,				// Delete a Unit 
	EXIT_GAME_MESSAGE = 3,					// Exit the game
	TOGGLE_PROPERTIES_MESSAGE = 4,			// Toggle properties menu
	SELECT_PROPERTIES_MESSAGE = 5,			// Select active property
	CHANGE_CURRENT_PROPERTY_MESSAGE = 6,	// Modify current property
	SAVE_WEIGHTS_MESSAGE = 7				// Save the weights for the Boids Steering
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

#endif