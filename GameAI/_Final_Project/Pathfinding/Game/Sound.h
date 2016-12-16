#pragma once

/**
*	Sound.h 
*	Play sound from SoundSource
*	Check active sound
*	Set the SoundSource
**/

#include "Trackable.h"
#include <allegro5\allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>


class Sound : public Trackable
{
private:
	ALLEGRO_SAMPLE* mpSoundSample;

public:
	Sound();								// no source
	~Sound();								// destructor

	void setSource(ALLEGRO_SAMPLE* newSource);

	void playSound();						// play a sound
	void loopSound();						// loop the sound
};