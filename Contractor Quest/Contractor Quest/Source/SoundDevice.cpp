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
	//FIXME: frequency and other params will be changed depending on audio files
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("SDL Mixer could not initialize! SDL_Error: %s\n", Mix_GetError());
		exit(1);
	}

	//allow enough channels
	Mix_AllocateChannels(100);
	initialized = true;

}

SoundDevice::~SoundDevice() {

	Mix_CloseAudio();
	Mix_Quit();
}


bool SoundDevice::playSound(string sound, int numLoops) {
	//in order to select the first available channel
	int channelID = -1;
	//Mix_SetPanning(channelID, maxVolume, 0); //commented out until sound direction/distance is implemented, also placement of this might change
	Mix_PlayChannel(channelID, getSoundEffect(sound), numLoops);
	return true;
}

void SoundDevice::setAsBackground(string background) {
	
	if (Mix_PlayMusic(getMusic(background), -1) == -1)
	{
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	}

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

//commented out until sound direction/distance is implemented
//int SoundDevice::updateSound(int minVal, int maxVal, int curValue, int increment) {
//	
//	int value = curValue + increment;
//
//	if (value >= maxVal)
//	{
//		value = maxVal;
//	}
//
//	if (value <= minVal)
//	{
//		value = minVal;
//	}
//
//	return(value);
//}
//
//int SoundDevice::updateSoundDirection(int minVal, int maxVal, int curValue, int increment) {
//
//	int value = curValue + increment;
//
//	if (value > maxVal)
//	{
//		value = minVal + increment;
//	}
//
//	if (value < minVal)
//	{
//		value = maxVal + increment;
//	}
//
//	return(value);
//}

