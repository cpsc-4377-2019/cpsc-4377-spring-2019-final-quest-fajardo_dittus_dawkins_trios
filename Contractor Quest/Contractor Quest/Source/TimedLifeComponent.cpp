#include "TimedLifeComponent.h"
#include "Object.h"

TimedLifeComponent::TimedLifeComponent(Object* owner, ObjectFactoryPresets presets) : Component(owner) {

}

TimedLifeComponent::~TimedLifeComponent() {

}

bool TimedLifeComponent::initialize(ObjectFactoryPresets presets) {
	return true;
}

Object* TimedLifeComponent::update(vector<Object*> object) {

	lifeTime--;
	if (lifeTime <= 0) owner->setIsDead(true);

	return nullptr;
}

void TimedLifeComponent::start() {

}
void TimedLifeComponent::finish() {

}