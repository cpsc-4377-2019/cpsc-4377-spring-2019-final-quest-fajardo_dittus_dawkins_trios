#include "Object.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "PhysicsDevice.h"
#include "ObjectFactory.h"
#include "Initializers.h"
#include "BodyComponent.h"

Object::Object() {

	initialized = false;
	isDead = false;

}

Object::~Object() {

	//Delete vector of components for object
	for (auto component : components) {
		delete component;
	}
}

bool Object::initialize(ObjectFactoryPresets presets)
{
	type = presets.objectType;
	if (!initialized)
	{
		for (auto comp : components)
		{
			comp->initialize(presets);
		}
		initialized = true;
	}

	return(initialized);
}

void Object::addComponent(Component* component)
{
	components.push_back(component);
}


Object* Object::update(vector<Object*> objects) {

	Object* newObject = nullptr;

	for (auto& component : components)
	{
		auto tempObject = component->update(objects);
		if (tempObject != nullptr)
		{
			newObject = tempObject;
		}
		
	}

	return newObject;
}

void Object::draw() {

	SpriteComponent* sprite = GetComponent<SpriteComponent>();
	if (sprite != nullptr)
	{
		sprite->draw();
	}

}

string Object::getType() {
	return type;
}

Texture* Object::getTexture() {
	return GetComponent<SpriteComponent>()->texture;
}

PhysicsDevice* Object::getPhysicsDevice() {
	return GetComponent<BodyComponent>()->pDevice;
}
bool Object::getIsDead() {
	return isDead;
}

void Object::setIsDead(bool isDead) {
	this->isDead = isDead;
}
