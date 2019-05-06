#ifndef RACOONBEHAVIORCOMPONENT_H
#define RACOONBEHAVIORCOMPONENT_H

#include "Component.h"
#include <vector>

class Object;

class RacoonBehaviorComponent: public Component {
	public:
		RacoonBehaviorComponent() = delete;
		RacoonBehaviorComponent(Object* owner, ObjectFactoryPresets presets);
		~RacoonBehaviorComponent();

		bool initialize(ObjectFactoryPresets presets);
		Object* update(vector<Object*>);
		void start();
		void finish();

		const float RUN_SPEED = 100.0f; //FIXME: This value may need to be changed.
	private:
};

#endif