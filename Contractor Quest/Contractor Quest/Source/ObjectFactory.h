#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "tinyxml2.h"
#include "Object.h"
#include "SpriteComponent.h"
#include <string>

using namespace std;

struct ObjectFactoryPresets;
class GraphicsDevice;
class SoundDevice;
class Library;
class Object;
class InputDevice;
class BodyComponent;
class PhysicsDevice;

class ObjectFactory {
	public:
		ObjectFactory() = delete;
		ObjectFactory(GraphicsDevice*, Library*);
		Object* create(tinyxml2::XMLElement* objectElement, GraphicsDevice*, Library*, InputDevice*, PhysicsDevice*, SoundDevice*);
		Object* create(ObjectFactoryPresets);

	private:

		BodyComponent* createBodyComponent(Object* newObject, PhysicsDevice* pDevice, tinyxml2::XMLElement* componentElement, ObjectFactoryPresets & presets);
		SoundDevice* sDevice;
		GraphicsDevice* gDevice;
		Library* objectLibrary;

};

#endif