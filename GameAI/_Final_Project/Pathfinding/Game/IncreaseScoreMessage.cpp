#include "IncreaseScoreMessage.h"
#include "GameApp.h"
#include "SoundSystem.h"

IncreaseScoreMessage::~IncreaseScoreMessage()
{
}

void IncreaseScoreMessage::process()
{
	// Increase the score, stored in GameApp
	if (mValue <= 10)
		gpGameApp->getSS()->playSound(1);
	if (mValue >= 50)
		gpGameApp->getSS()->playSound(2);

	gpGameApp->setScore(mValue);
}
