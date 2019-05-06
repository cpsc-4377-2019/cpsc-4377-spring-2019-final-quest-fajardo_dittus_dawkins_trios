#include "RacoonBehaviorComponent.h"
#include "Object.h"
#include "BodyComponent.h"
#include <memory>

RacoonBehaviorComponent::RacoonBehaviorComponent(Object * owner, ObjectFactoryPresets presets) : Component(owner) {
}

RacoonBehaviorComponent::~RacoonBehaviorComponent() {
}

bool RacoonBehaviorComponent::initialize(ObjectFactoryPresets presets) {
	return true;
}

Object* RacoonBehaviorComponent::update(vector<Object*> objects) {
	
	//Move in the direction that is currently being faced.
	BodyComponent* body = owner->GetComponent<BodyComponent>();
	int state = body->getState();
	if (body != nullptr) {
		if (state = BodyComponent::RUNNING_LEFT || BodyComponent::STANDING_LEFT) {
			body->setState(BodyComponent::RUNNING_LEFT);
			body->pDevice->SetLinearVelocity(owner, { -RUN_SPEED, body->pDevice->GetLinearVelocity(owner).y });
		}
		else if (state = BodyComponent::RUNNING_RIGHT || BodyComponent::STANDING_RIGHT) {
			body->setState(BodyComponent::RUNNING_RIGHT);
			body->pDevice->SetLinearVelocity(owner, { RUN_SPEED, body->pDevice->GetLinearVelocity(owner).y });
		}
	}

	return nullptr; //This object will never return an object.
}

void RacoonBehaviorComponent::start() {
	//No action needed.
}

void RacoonBehaviorComponent::finish() {
	//No action needed.
}