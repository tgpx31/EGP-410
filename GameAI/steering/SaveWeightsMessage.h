#ifndef SAVE_WEIGHTS_MESSAGE_H
#define SAVE_WEIGHTS_MESSAGE_H

#include "GameMessage.h"
#include <string>

class SaveWeightsMessage : public GameMessage
{
private:
	const std::string mFile = "savedWeights.txt";

public:
	SaveWeightsMessage();
	~SaveWeightsMessage();

	void process();
};


#endif