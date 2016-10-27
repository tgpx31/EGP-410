#ifndef SAVE_WEIGHTS_MESSAGE_H
#define SAVE_WEIGHTS_MESSAGE_H

#include "GameMessage.h"
#include <string>

class SaveWeightsMessage : public GameMessage
{
private:
	std::string mFile;

public:
	SaveWeightsMessage();
	~SaveWeightsMessage();

	void process();
};


#endif