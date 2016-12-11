#include "SoundSystem.h"
#include "Sound.h"

SoundSystem::SoundSystem()
{
	for (Sound* i : mChannels)
		i = new Sound();

	for (std::string i : mSources)
		i = "";
}

SoundSystem::~SoundSystem()
{
	for (Sound* i : mChannels)
	{
		i->stopSound();
		delete i;
		i = NULL;
	}
}

void SoundSystem::loadSources(const std::string sources[])
{
	for (int i = 0; i < SOURCE_COUNT; ++i)
	{
		mSources[i] = sources[i];
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

void SoundSystem::stopSound(const int & channel)
{
	mChannels[channel]->stopSound();
}
