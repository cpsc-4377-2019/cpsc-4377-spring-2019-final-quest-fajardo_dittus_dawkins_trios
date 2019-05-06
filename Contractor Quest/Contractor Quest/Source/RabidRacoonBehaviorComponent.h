#ifndef RABIDRACOONBEHAVIORCOMPONENT_H
#define RABIDRACOONBEHAVIORCOMPONENT_H

#include "Component.h"
#include <vector>

class Object;
class BodyComponent;
class SpriteComponent;

class RabidRacoonBehaviorComponent: public Component {
	public:
		RabidRacoonBehaviorComponent() = delete;
		RabidRacoonBehaviorComponent(Object* owner, ObjectFactoryPresets presets);
		~RabidRacoonBehaviorComponent();

		bool initialize(ObjectFactoryPresets presets);
		Object* update(vector<Object*>);
		void start();
		void finish();

		const float DETECTION_RANGE = 10.0f;
		const int COOLDOWN_TIME = 100;
		const float RUN_SPEED = 150.0f;
		const float JUMP_HEIGHT = 700.0f; //FIXME: may need to change these values

	private:

		//Helper Functions
		bool objectIsInRange(BodyComponent* objectBody, SpriteComponent* objectSprite);

		//Private members
		int jumpCooldown = 0;
		
};

#endif