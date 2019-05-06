#ifndef SOUNDDEVICE_H
#define SOUNDDEVICE_H

#include "SDL_mixer.h"
#include <string>
#include "Library.h"

using namespace std;

class SoundDevice {

public:
	SoundDevice();
	~SoundDevice();

	bool playSound(string sound, int numLoops);

	void setAsBackground(string background);

	Mix_Chunk* getSoundEffect(string name);
	Mix_Music* getMusic(string name);

	void getLibrary(Library* library);

	//commented out until sound direction/distance is implemented
	//int updateSound(int minVal, int maxVal, int curValue, int increment);
	//int updateSoundDirection(int minVal, int maxVal, int curValue, int increment);

	bool getInitialized() { return initialized; }

private:
	Library* library = nullptr;
	bool initialized = false;
	
	//commented out until sound direction/distance is implemented
	//int maxVolume = 255;
	//int soundDirection = 0;
	//int soundDistance = (int)((float)maxVolume / 2);
	//int distanceIncrement = 5;
	//int directionIncrement = 5;
};

#endif