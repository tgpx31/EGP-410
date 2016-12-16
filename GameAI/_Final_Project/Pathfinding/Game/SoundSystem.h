#pragma once

/**
*	Sound Sysyem.h
*	Multiple sound "channels"
*	Play sounds on message
**/

#include "Trackable.h"
#include <string>
#include <allegro5\allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Sound;

// Constants
const int SOUND_CHANNELS = 5;
const int SOURCE_COUNT = 5;

class SoundSystem : public Trackable
{
private:
	Sound* mChannels[SOUND_CHANNELS];
	ALLEGRO_SAMPLE* mSources[SOURCE_COUNT];
public:
	SoundSystem();
	~SoundSystem();

	void playSound(const int& channel);
	void loopSound(const int& channel);
};