#include "CrazyPersonBehaviorComponent.h"
#include <math.h>
#include <random>
#include "Object.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Definitions.h"
#include "Initializers.h"
#include "PhysicsDevice.h"
#include "ObjectFactory.h"

CrazyPersonBehaviorComponent::CrazyPersonBehaviorComponent(Object * owner, ObjectFactoryPresets presets) : Component(owner) {
}

CrazyPersonBehaviorComponent::~CrazyPersonBehaviorComponent() {
}

bool CrazyPersonBehaviorComponent::initialize(ObjectFactoryPresets presets) {
	objectFactory = presets.objectFactory;

	if (objectFactory != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

Object* CrazyPersonBehaviorComponent::update(vector<Object*> objects) {

	//Decrement timer
	if (rockCooldown > 0) rockCooldown--;

	//Locate Player
	Object* player = nullptr;
	for (int i = 0; i < objects.size(); i++) {
		if (objects.at(i)->getType() == "Player") {
			player = objects.at(i);
		}
	}

	Object* rock = nullptr;

	//Ensure player is not destroyed before checking players location.
	if (player != nullptr) {

		//Determine player's radial distance.
		BodyComponent* playerBody = player->GetComponent<BodyComponent>();
		BodyComponent* ownBody = owner->GetComponent<BodyComponent>();
		Position positionDistance = playerBody->getPosition() - ownBody->getPosition();
		double radialDistance = sqrt(pow(positionDistance.x, 2) + pow(positionDistance.y, 2));

		//If within aggro range, face the player.
		if (radialDistance < AGGRO_RADIUS) {

			if (playerBody->getPosX() <= ownBody->getPosX()) {
				ownBody->setState(BodyComponent::STANDING_LEFT);
			}
			else {
				ownBody->setState(BodyComponent::STANDING_RIGHT);
			}

			//Set presets and create throwning rock if a long enough amount of time has passed since the last.
			if (rockCooldown <= 0) {

				//Reset timer
				rockCooldown = 100;

				SpriteComponent* ownSprite = owner->GetComponent<SpriteComponent>();

				//Set values to be passed into the object factories create methode.
				ObjectFactoryPresets presets;
				presets.bodyInitializers.pDevice = ownBody->pDevice;
				presets.pDevice = ownBody->pDevice;
				presets.objectType = "Rock";
				presets.bodyInitializers.isDead = false;
				presets.bodyCompNeeded = true;
				presets.spriteCompNeeded = true;
				presets.timedLifeCompNeeded = true;
				presets.bodyInitializers.position.y = ownBody->getPosition().y + 5.0f;
				presets.bodyInitializers.angle = 0.0f;
				presets.bodyInitializers.density = 2.4f; //Value based on concrete density: 2.4 g/cm^3
				presets.bodyInitializers.friction = 4.0f;
				presets.bodyInitializers.angularDamping = 0.0f;
				presets.bodyInitializers.linearDamping = 0.0f;
				presets.bodyInitializers.bodyType = GAME_BODY_TYPE::GAME_DYNAMIC;
				presets.bodyInitializers.bodyShape = GAME_OBJECT_SHAPE::GAME_RECTANGLE;
				if (ownBody->getState() == BodyComponent::STANDING_LEFT) {
					presets.bodyInitializers.position.x = ownBody->getPosition().x - 5.0f;
					presets.bodyInitializers.linearVelocity = { -500.0f, -20.0f }; //FIXME: The velocity values may need to be changed
					presets.bodyInitializers.angularVelocity = -10.0f;
				}
				else if (ownBody->getState() == BodyComponent::STANDING_RIGHT) {
					presets.bodyInitializers.position.x = ownBody->getPosition().x + ownSprite->texture->getWidth() + 5.0f;
					presets.bodyInitializers.linearVelocity = { 500.0f, -20.0f }; //FIXME: The velocity values may need to be changed
					presets.bodyInitializers.angularVelocity = 10.0f;
				}

				//Create rock.
				rock = objectFactory->create(presets);
			}
		}
		else {
			//At random intervals, turn around.
			random_device seed;
			default_random_engine engine(seed());
			bernoulli_distribution distribution(0.005);

			bool turn = distribution(engine);

			if (turn) {
				if (ownBody->getState() == BodyComponent::STANDING_LEFT) {
					ownBody->setState(BodyComponent::STANDING_RIGHT);
				}
				else if (ownBody->getState() == BodyComponent::STANDING_RIGHT) {
					ownBody->setState(BodyComponent::STANDING_LEFT);
				}
			}
		}
	}

	return rock;
}

void CrazyPersonBehaviorComponent::start() {
	//No action needed
}

void CrazyPersonBehaviorComponent::finish() {
	//No action needed
}
