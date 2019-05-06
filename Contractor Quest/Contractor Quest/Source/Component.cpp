#include "Component.h"
#include "Object.h"
#include "ObjectFactory.h"

Component::Component(Object* owner) {
	this->owner = owner;
}

bool Component::initialize(ObjectFactoryPresets presets) {
	return true;
}

Object* Component::getOwner() {
	return owner;
}

void Component::OwnerDestroyed(){
	finish();
	owner = nullptr;
}
