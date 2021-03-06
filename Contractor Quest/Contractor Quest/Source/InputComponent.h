#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "Component.h"
#include "InputDevice.h"
#include <vector>

class InputDevice;
class SoundDevice;
class Object;

class InputComponent: public Component {
	public:
		InputComponent() = delete;
		InputComponent(Object* owner, ObjectFactoryPresets presets);
		~InputComponent();

		bool initialize(ObjectFactoryPresets presets);
		Object* update(vector<Object*>);
		void start();
		void finish();

		bool getEvent(InputDevice::UserInputs event);
	private:

		InputDevice* inputDevice;
		PhysicsDevice* pDevice;
		SoundDevice* sDevice;

		int jumpCooldown;
		int soundTimer;
		const int COOLDOWN_TIME = 50;
		const int SOUND_INCREMENT = 50;

		const float RUN_SPEED = 900.0f;
		const float MAX_VELOCITY = 32000.0f;
		const float JUMP_HEIGHT = 1000.0f;
		const float FAST_FALL_SPEED = 50.0f;
		
};

#endif