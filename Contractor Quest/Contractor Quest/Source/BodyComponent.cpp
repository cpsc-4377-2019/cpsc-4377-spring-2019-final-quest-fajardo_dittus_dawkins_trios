#include "BodyComponent.h"
#include "GraphicsDevice.h"
#include "Definitions.h"
#include "Object.h"


BodyComponent::BodyComponent(Object* owner, PhysicsDevice* pDevice, BodyPresets presets) : Component(owner) {

}

bool BodyComponent::initialize(ObjectFactoryPresets presets) {

	bodyType = presets.bodyInitializers.bodyType;

	this->pDevice = presets.bodyInitializers.pDevice;
	pDevice->CreateFixture(owner,
		presets.bodyInitializers.position, 
		presets.bodyInitializers.angle, 
		presets.bodyInitializers.bodyType, 
		presets.bodyInitializers.bodyShape, 
		presets.bodyInitializers.density, 
		presets.bodyInitializers.friction, 
		presets.bodyInitializers.restitution, 
		presets.bodyInitializers.angularDamping, 
		presets.bodyInitializers.linearDamping);

	pDevice->SetLinearVelocity(owner, presets.bodyInitializers.linearVelocity);
	pDevice->SetAngularVelocity(owner, presets.bodyInitializers.angularVelocity);

	position = getPosition();
	angle = getAngle();

	return true;
}

BodyComponent::~BodyComponent() {
	pDevice->deleteBody(owner);
}

Object* BodyComponent::update(vector<Object*> objects) {
	position = getPosition();
	angle = getAngle();
	return nullptr;
}

Position BodyComponent::getPosition() {
	return pDevice->GetPosition(owner);
}

EngineFloat BodyComponent::getAngle() {
	return pDevice->GetAngle(owner);
}


EngineFloat BodyComponent::getPosX() {
	return getPosition().x;
}

EngineFloat BodyComponent::getPosY() {
	return getPosition().y;
}

void BodyComponent::setPosition(Position position) {
	pDevice->SetTransform(owner, position, pDevice->GetAngle(owner));
}

void BodyComponent::start() {

}

void BodyComponent::finish() {

}

Position BodyComponent::getVelocity() {
	return pDevice->GetVelocity(owner);
}

void BodyComponent::setAngle(EngineFloat angle)
{
	pDevice->SetAngle(owner, angle);
}

void BodyComponent::setVelocity(Position velocity) {
	pDevice->SetLinearVelocity(owner, velocity);
}

void BodyComponent::setLinearImpulse(Position forceVec)
{
	pDevice->SetLinearImpulse(owner, forceVec, { position.x, position.y });
}

void BodyComponent::setLinearVelocity(Position velocity)
{
	pDevice->SetLinearVelocity(owner, velocity);
}
