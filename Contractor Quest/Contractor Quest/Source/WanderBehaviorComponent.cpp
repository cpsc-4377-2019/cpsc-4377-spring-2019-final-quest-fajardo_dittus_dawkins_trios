#include "WanderBehaviorComponent.h"
#include "Object.h"
#include "BodyComponent.h"

WanderBehaviorComponent::WanderBehaviorComponent(Object * owner, ObjectFactoryPresets presets) : Component(owner) {
}

WanderBehaviorComponent::~WanderBehaviorComponent() {
}

bool WanderBehaviorComponent::initialize(ObjectFactoryPresets presets) {
	return true;
}

Object* WanderBehaviorComponent::update(vector<Object*> objects) {

	//turnTimer is reset to TURN_COOLDOWN by the contact listner.
	if (turnTimer > 0) {
		turnTimer--;
	}
	
	//Move in the direction that is currently being faced.
	BodyComponent* body = owner->GetComponent<BodyComponent>();
	int state = body->getState();
	if (body != nullptr) {
		if (state == BodyComponent::RUNNING_LEFT || state == BodyComponent::STANDING_LEFT) {
			body->setState(BodyComponent::RUNNING_LEFT);
			body->pDevice->SetLinearVelocity(owner, { -RUN_SPEED, body->pDevice->GetLinearVelocity(owner).y });
		}
		else if (state == BodyComponent::RUNNING_RIGHT || state == BodyComponent::STANDING_RIGHT) {
			body->setState(BodyComponent::RUNNING_RIGHT);
			body->pDevice->SetLinearVelocity(owner, { RUN_SPEED, body->pDevice->GetLinearVelocity(owner).y });
		}
	}

	return nullptr; //This object will never return an object.
}

void WanderBehaviorComponent::start() {
	//No action needed.
}

void WanderBehaviorComponent::finish() {
	//No action needed.
}