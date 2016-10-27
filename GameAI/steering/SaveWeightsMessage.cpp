#include "SaveWeightsMessage.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"

#include <fstream>
#include <iostream>

SaveWeightsMessage::SaveWeightsMessage()
:GameMessage(SAVE_WEIGHTS_MESSAGE)
{
	mFile = "savedWeights.txt";
}

SaveWeightsMessage::~SaveWeightsMessage()
{
}

void SaveWeightsMessage::process()
{
	// Open a file stream
	std::ofstream fileOpen;

	fileOpen.open(mFile);
	if (!fileOpen.fail())
	{
		// Write to the save file
		// get the current weights
		// save them
		if (gpGame->getUnitManager()->getMap().empty())
		{
			fileOpen << 3 << std::endl;
			fileOpen << 6 << std::endl;
			fileOpen << 10 << std::endl;
		}

		fileOpen << gpGame->getUnitManager()->getMap().begin()->second->getSteering()->getWeight(0) << std::endl;
		fileOpen << gpGame->getUnitManager()->getMap().begin()->second->getSteering()->getWeight(1) << std::endl;
		fileOpen << gpGame->getUnitManager()->getMap().begin()->second->getSteering()->getWeight(2) << std::endl;
	}
	else
	{
		std::cout << "\nERROR BAD FILE\n";
	}

	// Close the file stream
	fileOpen.close();
}
