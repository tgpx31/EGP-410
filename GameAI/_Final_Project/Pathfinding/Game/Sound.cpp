#include "Sound.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>

Sound::Sound()
{
	mSourcePath = "";
	mpSoundSample = NULL;
}

Sound::Sound(const std::string & soundPath)
{
	mSourcePath = soundPath;
	mpSoundSample = NULL;

	mpSoundSample = al_load_sample(mSourcePath.c_str());
	if (!mpSoundSample)
	{
		std::cout << "\nSOUND FAILED TO LOAD FROM: " << mSourcePath << std::endl;
	}
}

Sound::~Sound()
{
	al_destroy_sample(mpSoundSample);
}

void Sound::setSource(const std::string & newSource)
{
	mSourcePath = newSource;
	mpSoundSample = al_load_sample(mSourcePath.c_str());
}

void Sound::playSound()
{
	// Plays the sound one time
	al_play_sample(mpSoundSample, 1.0f, 1.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Sound::loopSound()
{
	al_play_sample(mpSoundSample, 1.0f, 1.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void Sound::stopSound()
{
	al_destroy_sample(mpSoundSample);
	mpSoundSample = al_load_sample(mSourcePath.c_str());
}