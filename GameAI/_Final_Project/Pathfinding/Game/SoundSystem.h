#pragma once

/**
*	Sound Sysyem.h
*	Multiple sound "channels"
*	Play sounds on message
**/

#include "Trackable.h"
#include <string>

class Sound;

// Constants
const int SOUND_CHANNELS = 5;
const int SOURCE_COUNT = 5;
const int BGM_INDEX = 0;		// BGM will be the first sound

class SoundSystem : public Trackable
{
private:
	Sound* mChannels[SOUND_CHANNELS];
	std::string mSources[SOURCE_COUNT];
public:
	SoundSystem();
	~SoundSystem();

	void loadSources(const std::string sources[]);
	void playSound(const int& channel);
	void loopSound(const int& channel);
	void stopSound(const int& channel);
};