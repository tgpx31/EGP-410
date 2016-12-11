#pragma once

/**
*	Sound.h 
*	Play sound from SoundSource
*	Check active sound
*	Set the SoundSource
**/

#include "Trackable.h"
#include <allegro5\allegro_audio.h>

#include <string>


class Sound : public Trackable
{
private:
	std::string mSourcePath;
	ALLEGRO_SAMPLE* mpSoundSample;

public:
	Sound();								// no source
	Sound(const std::string& soundPath );	// assign source at creation
	~Sound();								// destructor

	void setSource(const std::string& newSource);

	void playSound();						// play a sound
	void loopSound();						// loop the sound
	void stopSound();						// stop the sound
};