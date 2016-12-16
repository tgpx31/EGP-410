#include "SoundSystem.h"
#include "Sound.h"

SoundSystem::SoundSystem()
{
	mSources[0] = al_load_sample("../Assets/Sound/BGM.ogg");
	mSources[1] = al_load_sample("../Assets/Sound/coinNoise.ogg");
	mSources[2] = al_load_sample("../Assets/Sound/getCandy.ogg");
	mSources[3] = al_load_sample("../Assets/Sound/killEnemy.ogg");
	mSources[4] = al_load_sample("../Assets/Sound/playerDeath.ogg");

	for (int i = 0; i < SOUND_CHANNELS; ++i)
	{
		mChannels[i] = new Sound();
		mChannels[i]->setSource(mSources[i]);
	}
}

SoundSystem::~SoundSystem()
{
	for (ALLEGRO_SAMPLE* sam : mSources)
	{
		al_destroy_sample(sam);
		sam = NULL;
	}
	for (Sound* i : mChannels)
	{
		delete i;
		i = NULL;
	}
}

void SoundSystem::playSound(const int & channel)
{
	mChannels[channel]->playSound();
}

void SoundSystem::loopSound(const int & channel)
{
	mChannels[channel]->loopSound();
}
