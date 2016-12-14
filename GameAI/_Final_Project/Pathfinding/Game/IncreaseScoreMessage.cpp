#include "IncreaseScoreMessage.h"
#include "GameApp.h"

IncreaseScoreMessage::~IncreaseScoreMessage()
{
}

void IncreaseScoreMessage::process()
{
	// Increase the score, stored in GameApp
	gpGameApp->setScore(mValue);
}
