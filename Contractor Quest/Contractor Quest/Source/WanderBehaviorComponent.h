#ifndef WANDERBEHAVIORCOMPONENT_H
#define WANDERBEHAVIORCOMPONENT_H

#include "Component.h"
#include <vector>

class Object;

class WanderBehaviorComponent: public Component {
	public:
		WanderBehaviorComponent() = delete;
		WanderBehaviorComponent(Object* owner, ObjectFactoryPresets presets);
		~WanderBehaviorComponent();

		bool initialize(ObjectFactoryPresets presets);
		Object* update(vector<Object*>);
		void start();
		void finish();

		const float RUN_SPEED = 100.0f; //FIXME: This value may need to be changed.

	private:
};

#endif