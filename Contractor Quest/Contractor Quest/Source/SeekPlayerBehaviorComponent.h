#ifndef SEEKPLAYERBEHAVIORCOMPONENT_H
#define SEEKPLAYERBEHAVIORCOMPONENT_H

#include "Component.h"
#include <vector>

class Object;
class BodyComponent;
class SpriteComponent;

class SeekPlayerBehaviorComponent: public Component {
	public:
		SeekPlayerBehaviorComponent() = delete;
		SeekPlayerBehaviorComponent(Object* owner, ObjectFactoryPresets presets);
		~SeekPlayerBehaviorComponent();

		bool initialize(ObjectFactoryPresets presets);
		Object* update(vector<Object*>);
		void start();
		void finish();

		const float DETECTION_RANGE = 10.0f;
		const int COOLDOWN_TIME = 100;
		const float RUN_SPEED = 100.0f;
		const float JUMP_HEIGHT = 700.0f; //FIXME: may need to change these values

	private:

		//Helper Functions
		bool objectIsInRange(BodyComponent* objectBody, SpriteComponent* objectSprite);

		//Private members
		int jumpCooldown = 0;
		
};

#endif