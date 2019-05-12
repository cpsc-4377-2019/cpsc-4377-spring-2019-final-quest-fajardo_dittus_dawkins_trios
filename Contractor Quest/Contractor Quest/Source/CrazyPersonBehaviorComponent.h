#ifndef CRAZYPERSONBEHAVIORCOMPONENT_H
#define CRAZYPERSONBEHAVIORCOMPONENT_H

#include "Component.h"

class Texture;
class ObjectFactory;

class CrazyPersonBehaviorComponent : public Component {
	public:
		CrazyPersonBehaviorComponent() = delete;
		CrazyPersonBehaviorComponent(Object* owner, ObjectFactoryPresets presets);
		~CrazyPersonBehaviorComponent();

		bool initialize(ObjectFactoryPresets presets);
		Object* update(vector<Object*>);
		void start();
		void finish();
	private:
		const float AGGRO_RADIUS = 750.0f;	//FIXME: may need to adjust
		int rockCooldown = 0;	//Timer to determine when rocks can be thrown
		ObjectFactory* objectFactory; //Used call create to create rocks.
};

#endif