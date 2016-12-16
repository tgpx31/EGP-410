#include "Sound.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>

Sound::Sound()
{
	mpSoundSample = NULL;
}

Sound::~Sound()
{
}

void Sound::setSource(ALLEGRO_SAMPLE*  newSource)
{
	mpSoundSample = newSource;
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