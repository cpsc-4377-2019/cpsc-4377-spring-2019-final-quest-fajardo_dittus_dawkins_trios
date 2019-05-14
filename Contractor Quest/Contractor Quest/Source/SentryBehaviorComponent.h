#ifndef SENTRYBEHAVIORCOMPONENT_H
#define SENTRYBEHAVIORCOMPONENT_H

#include "Component.h"

class Texture;
class ObjectFactory;
class Library;

class SentryBehaviorComponent : public Component {
	public:
		SentryBehaviorComponent() = delete;
		SentryBehaviorComponent(Object* owner, ObjectFactoryPresets presets);
		~SentryBehaviorComponent();

		bool initialize(ObjectFactoryPresets presets);
		Object* update(vector<Object*>);
		void start();
		void finish();
	private:
		const float AGGRO_RADIUS = 750.0f;
		const int ROCK_COOLDOWN = 150;
		int rockTimer = 0;	//Timer to determine when rocks can be thrown
		ObjectFactory* objectFactory; //Used call create to create rocks.
		Library* library;
};

#endif