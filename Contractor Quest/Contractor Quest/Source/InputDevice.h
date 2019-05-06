#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "SDL.h"
#include <vector>

class InputDevice {
	public:
		InputDevice();
		~InputDevice();

		enum UserInputs { NONE, UP, DOWN, LEFT, RIGHT, QUIT, NUM_EVENTS };

		void update();

		bool getEvent(UserInputs gEvent);
	private:
		UserInputs translate();
		std::vector<bool> keyStates;
		SDL_Event* event;
};

#endif