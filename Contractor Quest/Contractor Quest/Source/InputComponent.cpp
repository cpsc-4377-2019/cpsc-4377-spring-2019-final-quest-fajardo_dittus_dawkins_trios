#include "InputComponent.h"
#include "SoundDevice.h"
#include "Object.h"

bool InputComponent::initialize(ObjectFactoryPresets presets) {
	this->inputDevice = presets.inputDevice;
	this->pDevice = presets.pDevice;
	this->sDevice = presets.sDevice;
	jumpCooldown = 0;
	soundTimer = 0;
	return true;
}

InputComponent::InputComponent(Object * owner, ObjectFactoryPresets presets) : Component(owner) {
}

InputComponent::~InputComponent() {

}

Object* InputComponent::update(vector<Object*> objects) {

	if (jumpCooldown > 0) jumpCooldown--;
	if (soundTimer > 0) soundTimer--;

	BodyComponent* body = owner->GetComponent<BodyComponent>();
	if (getEvent(InputDevice::UP) && jumpCooldown <= 0) {

		if (body->getIsGrounded()) {
			jumpCooldown = COOLDOWN_TIME;
			body->setLinearImpulse({ 0.0f, -JUMP_HEIGHT });
		}
	}
	if (getEvent(InputDevice::DOWN)) {
		body->setLinearImpulse({ 0.0f, FAST_FALL_SPEED });
	}
	if (getEvent(InputDevice::LEFT)) {
		if (soundTimer <= 0) {
			soundTimer = SOUND_INCREMENT;
			sDevice->playSound("walking", 0, 2);
		}
		if (pDevice->GetLinearVelocity(owner).x >= (-MAX_VELOCITY*DT)) {
			body->setState(BodyComponent::RUNNING_LEFT);
			body->setLinearVelocity({ (pDevice->GetLinearVelocity(owner).x - (RUN_SPEED*DT)), (pDevice->GetLinearVelocity(owner)).y });
		}
		else {
			body->setLinearVelocity({ (-MAX_VELOCITY*DT), (pDevice->GetLinearVelocity(owner)).y });
		}
	}
	if (getEvent(InputDevice::RIGHT)) {
		if (soundTimer <= 0) {
			soundTimer = SOUND_INCREMENT;
			sDevice->playSound("walking", 0, 2);
		}
		if (pDevice->GetLinearVelocity(owner).x <= (MAX_VELOCITY * DT)) {
			body->setState(BodyComponent::RUNNING_RIGHT);
			body->setLinearVelocity({ (pDevice->GetLinearVelocity(owner).x + (RUN_SPEED*DT)), (pDevice->GetLinearVelocity(owner)).y });
		}
		else {
			body->setLinearVelocity({ (MAX_VELOCITY * DT), (pDevice->GetLinearVelocity(owner)).y });
		}
	}
	if (getEvent(InputDevice::NONE)) {
		if (body->getState() == BodyComponent::STANDING_LEFT || body->getState() == BodyComponent::RUNNING_LEFT) {
			body->setState(BodyComponent::STANDING_LEFT);
		}
		else if (body->getState() == BodyComponent::STANDING_RIGHT || body->getState() == BodyComponent::RUNNING_RIGHT) {
			body->setState(BodyComponent::STANDING_RIGHT);
		}
	}

	if (body->getVelocity().y != 0) {
		body->setIsGrounded(false);
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