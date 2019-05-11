#include "ObjectFactory.h"
#include "Library.h"
#include "InputDevice.h"
#include "PhysicsDevice.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "SoundDevice.h"
#include "InputComponent.h"
#include "RabidRacoonBehaviorComponent.h"
#include "RacoonBehaviorComponent.h"
#include "CrazyPersonBehaviorComponent.h"
#include "TimedLifeComponent.h"
#include "tinyxml2.h"

using namespace std;

BodyComponent* ObjectFactory::createBodyComponent(Object* newObject, PhysicsDevice* pDevice, tinyxml2::XMLElement* componentElement, ObjectFactoryPresets & presets)
{
	presets.bodyInitializers.pDevice = pDevice;

	componentElement->QueryFloatAttribute("posX", &(presets.bodyInitializers.position.x));
	componentElement->QueryFloatAttribute("posY", &(presets.bodyInitializers.position.y));
	componentElement->QueryFloatAttribute("angle", &(presets.bodyInitializers.angle));
	componentElement->QueryIntAttribute("state", &(presets.bodyInitializers.state));
	componentElement->QueryFloatAttribute("friction", &(presets.bodyInitializers.friction));
	componentElement->QueryFloatAttribute("density", &(presets.bodyInitializers.density));
	componentElement->QueryFloatAttribute("restitution", &(presets.bodyInitializers.restitution));
	componentElement->QueryFloatAttribute("angularDamping", &(presets.bodyInitializers.angularDamping));
	componentElement->QueryFloatAttribute("linearDamping", &(presets.bodyInitializers.linearDamping));
	
	string bodyType = componentElement->Attribute("bodyType");		//For some reason, xml doesn't like to compare
	string bodyShape = componentElement->Attribute("bodyShape");	//strings to element attributes directly

	if (bodyType == "DYNAMIC")
	{
		presets.bodyInitializers.bodyType = GAME_BODY_TYPE::GAME_DYNAMIC;
	}
	else if (bodyType == "KINEMATIC") {
		presets.bodyInitializers.bodyType = GAME_BODY_TYPE::GAME_KINEMATIC;
	}
	else if (bodyType == "STATIC")
	{
		presets.bodyInitializers.bodyType = GAME_BODY_TYPE::GAME_STATIC;
	}

	if (bodyShape == "RECTANGLE")
	{
		presets.bodyInitializers.bodyShape = GAME_OBJECT_SHAPE::GAME_RECTANGLE;
	}
	else if (bodyShape == "CIRCLE")
	{
		presets.bodyInitializers.bodyShape = GAME_OBJECT_SHAPE::GAME_CIRCLE;
	}
	
	return new BodyComponent(newObject, pDevice, std::move(presets.bodyInitializers));
}

ObjectFactory::ObjectFactory(GraphicsDevice* gDevice, Library* objectLibrary)
{
	this->gDevice = gDevice;
	this->objectLibrary = objectLibrary;
}

Object* ObjectFactory::create(tinyxml2::XMLElement* objectElement, GraphicsDevice* graphicDevice, Library* objectLibrary, InputDevice* inputDevice, PhysicsDevice* pDevice, SoundDevice* sDevice)
{
	Object* newObject = new Object();
	ObjectFactoryPresets presets;
	presets.sDevice = sDevice;

	presets.objectType = objectElement->Attribute("type");

	for (tinyxml2::XMLElement* componentElement = objectElement->FirstChildElement(); componentElement; componentElement = componentElement->NextSiblingElement())
	{
		string componentName = componentElement->Attribute("name");
		if (componentName == "Sprite")
		{
			presets.spriteInitializers.spriteTexture = objectLibrary->artLibrary.find(presets.objectType)->second;
			presets.spriteInitializers.gdevice = graphicDevice;
			presets.pDevice = pDevice;
			newObject->addComponent(new SpriteComponent(newObject, presets.spriteInitializers));

		}
		else if (componentName == "Body")
		{
			newObject->addComponent(createBodyComponent(newObject, pDevice, componentElement, presets));
		}
		else if (componentName == "InputComponent") {
			presets.inputDevice = inputDevice;
			newObject->addComponent(new InputComponent(newObject, presets));
		}
		else if (componentName == "RacoonBehaviorComponent") {
			newObject->addComponent(new RacoonBehaviorComponent(newObject, presets));
		}
		else if (componentName == "RabidRacoonBehaviorComponent") {
			newObject->addComponent(new RabidRacoonBehaviorComponent(newObject, presets));
		}
		else if (componentName == "TimedLifeComponent") {
			newObject->addComponent(new TimedLifeComponent(newObject, presets));
		}
		else if (componentName == "CrazyPersonBehaviorComponent") {
			presets.objectFactory = this;
			newObject->addComponent(new CrazyPersonBehaviorComponent(newObject, presets));
		}
	}

	if (newObject->initialize(presets))
	{
		return newObject;
	}
	else
	{
		cout << "Object did not initialize!" << endl;
		return nullptr;
	}
}

//Used for dynamic object creation.  Presets should be set by the object that created the new object.
Object* ObjectFactory::create(ObjectFactoryPresets presets) {
	Object* newObject = new Object();
	
	if (presets.bodyCompNeeded) {
		newObject->addComponent(new BodyComponent(newObject, presets.bodyInitializers.pDevice, presets.bodyInitializers));
	}
	if (presets.spriteCompNeeded) {
		presets.spriteInitializers.spriteTexture = objectLibrary->artLibrary.find(presets.objectType)->second;
		presets.spriteInitializers.gdevice = gDevice;
		newObject->addComponent(new SpriteComponent(newObject, presets.spriteInitializers));
	}
	if (presets.inputCompNeeded) {
		newObject->addComponent(new InputComponent(newObject, presets));
	}
	if (presets.racoonBehaviorCompNeeded) {
		newObject->addComponent(new RacoonBehaviorComponent(newObject, presets));
	}
	if (presets.rabidracoonBehaviorCompNeeded) {
		newObject->addComponent(new RabidRacoonBehaviorComponent(newObject, presets));
	}
	if (presets.timedLifeCompNeeded) {
		newObject->addComponent(new TimedLifeComponent(newObject, presets));
	}
	if (presets.crazyPersonBehaviorCompNeeded) {
		presets.objectFactory = this;
		newObject->addComponent(new CrazyPersonBehaviorComponent(newObject, presets));
	}
	if (presets.timedLifeCompNeeded) {
		newObject->addComponent(new TimedLifeComponent(newObject, presets)); //FIXME: Check that this works properly after branches are merged.
	}

	if (newObject->initialize(presets))
	{
		return newObject;
	}
	else
	{
		cout << "Object did not initialize!" << endl;
		return nullptr;
	}
}