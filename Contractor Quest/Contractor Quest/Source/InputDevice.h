#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "SDL.h"
#include "SoundDevice.h"
#include <vector>

class InputDevice {
	public:
		InputDevice(SoundDevice* sDevice);
		~InputDevice();

		enum UserInputs { NONE, UP, DOWN, LEFT, RIGHT, QUIT, NUM_EVENTS };

		void update();

		bool getEvent(UserInputs gEvent);
	private:
		UserInputs translate();
		std::vector<bool> keyStates;
		SDL_Event* event;
		SoundDevice* sDevice;
};

#endif