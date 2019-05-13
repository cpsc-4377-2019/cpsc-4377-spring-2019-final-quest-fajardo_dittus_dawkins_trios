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
	bool playSound(string sound, int numLoops, int channelID);

	Mix_Chunk* getSoundEffect(string name);
	Mix_Music* getMusic(string name);

	void setLibrary(Library* library);

	int updateSound(int minVal, int maxVal, int curValue, int increment);
	int updateSoundDirection(int minVal, int maxVal, int curValue, int increment);

	bool getInitialized() { return initialized; }

	int maxVolume = 200;
	int soundDirection = 0;
	int soundDistance = (int)((float)maxVolume / 2);
	int distanceIncrement = 5;
	int directionIncrement = 5;
	int channelID = -1;

private:
	Library* library = nullptr;
	bool initialized = false;
};

#endif