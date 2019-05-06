#ifndef TIMEDLIFE_H
#define TIMEDLIFE_H

#include "Component.h"

class Object;
struct ObjectFactoryPresets;

class TimedLifeComponent : public Component {

public:
	TimedLifeComponent(Object* owner, ObjectFactoryPresets presets);
	~TimedLifeComponent();

	bool initialize(ObjectFactoryPresets presets);
	Object* update(vector<Object*> object);

	void start();
	void finish();

private:

	int lifeTime = 100;	//100 = 1 second
};

#endif