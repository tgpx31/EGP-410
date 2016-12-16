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
	else if (mValue <= 50)
		gpGameApp->getSS()->playSound(2);
	else if (mValue <= 100)
		gpGameApp->getSS()->playSound(3);

	gpGameApp->setScore(mValue);
}
