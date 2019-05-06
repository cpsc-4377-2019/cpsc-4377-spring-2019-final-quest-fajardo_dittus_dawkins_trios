#include "InputDevice.h"

InputDevice::InputDevice() {
	event = new SDL_Event;

	for (int i = 0; i <= NUM_EVENTS; i++) {
		keyStates.push_back(false);
	}
}

InputDevice::~InputDevice() {
}

InputDevice::UserInputs InputDevice::translate() {
	//InputDevice will accept input direction input from either the arrow keys and wasd.
	switch (event->key.keysym.sym) {
		case SDLK_LEFT:
		case SDLK_a:
			return UserInputs::LEFT;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			return UserInputs::RIGHT;
			break;
		case SDLK_UP:
		case SDLK_w:
			return UserInputs::UP;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			return UserInputs::DOWN;
			break;
	}

	return UserInputs::NONE;
}

void InputDevice::update() {

	UserInputs gEvent = NONE;
	if (SDL_PollEvent(event)) {
		switch (event->type) {
			case SDL_KEYDOWN:
				gEvent = translate();
				keyStates.at(gEvent) = true;
				break;
			case SDL_KEYUP:
				gEvent = translate();
				keyStates.at(gEvent) = false;
				break;
			case SDL_QUIT:
				keyStates.at(QUIT) = true;
			default:
				break;
		}
	}
}

bool InputDevice::getEvent(InputDevice::UserInputs gEvent) {
	return keyStates.at(gEvent);
}