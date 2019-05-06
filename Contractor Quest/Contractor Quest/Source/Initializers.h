#ifndef INITIALIZERS_H
#define INITIALIZERS_H

#include <iostream>
#include <string>
#include "Definitions.h"

using namespace std;

class Texture;
class SpriteComponent;
class SoundDevice;
class InputDevice;
class GraphicsDevice;
class PhysicsDevice;
class Object;
class ObjectFactory;

struct SpritePresets
{
	string textString = " ";
	Texture* spriteTexture = nullptr;
	GraphicsDevice* gdevice = nullptr;

};

struct Joints
{
	bool collide;
	Position AnchorA;
	Position AnchorB;
	EngineFloat JointLimit;
};

struct BodyPresets
{
	PhysicsDevice* pDevice;
	Position position = { 0,0 };
	EngineFloat angle = 0.0f;
	bool isDead = false;
	int state = 0;
	SpriteComponent* sprite = nullptr;
	GAME_BODY_TYPE bodyType{ GAME_BODY_TYPE::GAME_STATIC };
	GAME_OBJECT_SHAPE bodyShape{ GAME_OBJECT_SHAPE::GAME_RECTANGLE };
	EngineFloat density{ 0.0f };
	EngineFloat friction{ 0.0f };
	EngineFloat restitution{ 0.0f };
	Position linearVelocity{ 0.0f, 0.0f };
	EngineFloat angularVelocity{ 0.0f };
	EngineFloat angularDamping{ 0.0f };
	EngineFloat linearDamping{ 0.0f };
	Joints joint;

};

struct ObjectFactoryPresets
{
	string objectType = "";
	string textPath = "";
	SpritePresets spriteInitializers;
	BodyPresets bodyInitializers;
	GraphicsDevice* device = nullptr;
	InputDevice* inputDevice = nullptr;
	Object* object = nullptr;
	PhysicsDevice* pDevice = nullptr;
	ObjectFactory* objectFactory = nullptr;
	SoundDevice* sDevice = nullptr;

	//Used in dynamic object creation
	bool bodyCompNeeded = false;
	bool spriteCompNeeded = false;
	bool inputCompNeeded = false;
	bool racoonBehaviorCompNeeded = false;
	bool rabidracoonBehaviorCompNeeded = false;
	bool crazyPersonBehaviorCompNeeded = false;
	bool timedLifeCompNeeded = false;
	
};

#endif