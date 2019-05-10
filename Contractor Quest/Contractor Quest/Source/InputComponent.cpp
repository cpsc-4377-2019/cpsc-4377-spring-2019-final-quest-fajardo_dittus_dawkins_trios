#include "InputComponent.h"
#include "SoundDevice.h"
#include "Object.h"

bool InputComponent::initialize(ObjectFactoryPresets presets) {
	this->inputDevice = presets.inputDevice;
	this->pDevice = presets.pDevice;
	this->sDevice = presets.sDevice;

	return true;
}

InputComponent::InputComponent(Object * owner, ObjectFactoryPresets presets) : Component(owner) {
}

InputComponent::~InputComponent() {
}

Object* InputComponent::update(vector<Object*> objects) {

	BodyComponent* body = owner->GetComponent<BodyComponent>();
	if (getEvent(InputDevice::UP)) {
		body->setLinearImpulse({0.0f, -JUMP_HEIGHT});	//FIXME: make sure this only happens once on key press
	}
	if (getEvent(InputDevice::DOWN)) {
		body->setLinearImpulse({ 0.0f, FAST_FALL_SPEED });
	}
	if (getEvent(InputDevice::LEFT)) {
		sDevice->playSound("walking", 1, 2);
		body->setLinearVelocity({(pDevice->GetLinearVelocity(owner).x - (RUN_SPEED*DT)), (pDevice->GetLinearVelocity(owner)).y});
	}
	if (getEvent(InputDevice::RIGHT)) {
		sDevice->playSound("walking", 1, 2);
		body->setLinearVelocity({ (pDevice->GetLinearVelocity(owner).x + (RUN_SPEED*DT)), (pDevice->GetLinearVelocity(owner)).y });
	}

	return nullptr; //This object never creates an object.
}

void InputComponent::start() {
	//No action needed.
}

void InputComponent::finish() {
	//No action needed.
}

bool InputComponent::getEvent(InputDevice::UserInputs gEvent) {
	return inputDevice->getEvent(gEvent);
}