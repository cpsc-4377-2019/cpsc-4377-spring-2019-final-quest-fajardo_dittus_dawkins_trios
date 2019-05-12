#include "SoundDevice.h"

SoundDevice::SoundDevice() {

	{
		auto flags = MIX_INIT_OGG;
		auto initted = Mix_Init(flags);

		if (initted && flags != flags)
		{
			printf("Mix_Init: Failed to init required ogg and mod support!\n");
			printf("Mix_Init: %s\n", Mix_GetError());
			initialized = false;
		}
	}

	//load the mixer subsystem
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("SDL Mixer could not initialize! SDL_Error: %s\n", Mix_GetError());
		exit(1);
	}

	//allow enough channels
	Mix_AllocateChannels(100);
	initialized = true;
	Mix_SetPanning(channelID, maxVolume, 0);

}

SoundDevice::~SoundDevice() {

	Mix_CloseAudio();
	Mix_Quit();
}


bool SoundDevice::playSound(string sound, int numLoops) {

	Mix_SetPosition(channelID, (Sint16)soundDirection, (Uint8)soundDistance);
	Mix_PlayChannel(channelID, getSoundEffect(sound), numLoops);
	return true;
}

//this is if we need to use a specific channel
bool SoundDevice::playSound(string sound, int numLoops, int channelID) {
	
	//Mix_SetPosition(channelID, (Sint16)soundDirection, (Uint8)soundDistance);
	Mix_PlayChannel(channelID, getSoundEffect(sound), numLoops);
	return true;
}

Mix_Chunk* SoundDevice::getSoundEffect(string name) {

	return library->soundEffectLibrary.find(name)->second;

}

Mix_Music* SoundDevice::getMusic(string name) {

	return library->musicLibrary.find(name)->second;

}

void SoundDevice::getLibrary(Library* library) {
	this->library = library;
}

int SoundDevice::updateSound(int minVal, int maxVal, int curValue, int increment) {
	
	int value = curValue + increment;

	if (value >= maxVal)
	{
		value = maxVal;
	}

	if (value <= minVal)
	{
		value = minVal;
	}

	return(value);
}

int SoundDevice::updateSoundDirection(int minVal, int maxVal, int curValue, int increment) {

	int value = curValue + increment;

	if (value > maxVal)
	{
		value = minVal + increment;
	}

	if (value < minVal)
	{
		value = maxVal + increment;
	}

	return(value);
}

