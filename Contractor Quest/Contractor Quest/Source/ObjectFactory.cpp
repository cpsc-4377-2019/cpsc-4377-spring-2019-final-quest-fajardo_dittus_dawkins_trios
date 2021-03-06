#include "ObjectFactory.h"
#include "Library.h"
#include "InputDevice.h"
#include "PhysicsDevice.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "SoundDevice.h"
#include "InputComponent.h"
#include "SeekPlayerBehaviorComponent.h"
#include "WanderBehaviorComponent.h"
#include "SentryBehaviorComponent.h"
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
			for (tinyxml2::XMLElement* textureElement = componentElement->FirstChildElement(); textureElement; textureElement = textureElement->NextSiblingElement())
			{
				string textureName = textureElement->Attribute("textureName");
				presets.spriteInitializers.textures.push_back(objectLibrary->artLibrary.find(textureName)->second);
			}

			//Set the current sprite to the first temporarly.  It will be update by the sprite component before the game displays.
			presets.spriteInitializers.currentTexture = presets.spriteInitializers.textures[0];
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
		else if (componentName == "WanderBehaviorComponent") {
			newObject->addComponent(new WanderBehaviorComponent(newObject, presets));
		}
		else if (componentName == "SeekPlayerBehaviorComponent") {
			newObject->addComponent(new SeekPlayerBehaviorComponent(newObject, presets));
		}
		else if (componentName == "TimedLifeComponent") {
			newObject->addComponent(new TimedLifeComponent(newObject, presets));
		}
		else if (componentName == "SentryBehaviorComponent") {
			presets.objectFactory = this;
			presets.library = objectLibrary;
			newObject->addComponent(new SentryBehaviorComponent(newObject, presets));
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
		presets.spriteInitializers.currentTexture = objectLibrary->artLibrary.find(presets.objectType)->second;
		presets.spriteInitializers.gdevice = gDevice;
		newObject->addComponent(new SpriteComponent(newObject, presets.spriteInitializers));
	}
	if (presets.inputCompNeeded) {
		newObject->addComponent(new InputComponent(newObject, presets));
	}
	if (presets.wanderBehaviorCompNeeded) {
		newObject->addComponent(new WanderBehaviorComponent(newObject, presets));
	}
	if (presets.seekPlayerBehaviorCompNeeded) {
		newObject->addComponent(new SeekPlayerBehaviorComponent(newObject, presets));
	}
	if (presets.timedLifeCompNeeded) {
		newObject->addComponent(new TimedLifeComponent(newObject, presets));
	}
	if (presets.sentryBehaviorCompNeeded) {
		presets.objectFactory = this;
		newObject->addComponent(new SentryBehaviorComponent(newObject, presets));
	}
	if (presets.timedLifeCompNeeded) {
		newObject->addComponent(new TimedLifeComponent(newObject, presets));
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