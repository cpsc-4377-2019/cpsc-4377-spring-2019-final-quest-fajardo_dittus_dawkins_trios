#include "SentryBehaviorComponent.h"
#include <math.h>
#include <random>
#include "Object.h"
#include "BodyComponent.h"
#include "SoundDevice.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Definitions.h"
#include "Initializers.h"
#include "PhysicsDevice.h"
#include "ObjectFactory.h"
#include "Library.h"

SentryBehaviorComponent::SentryBehaviorComponent(Object * owner, ObjectFactoryPresets presets) : Component(owner) {
}

SentryBehaviorComponent::~SentryBehaviorComponent() {
}

bool SentryBehaviorComponent::initialize(ObjectFactoryPresets presets) {

	objectFactory = presets.objectFactory;
	sDevice = presets.sDevice;
	library = presets.library;

	if (objectFactory != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

Object* SentryBehaviorComponent::update(vector<Object*> objects) {

	//Decrement timer
	if (rockTimer > 0) rockTimer--;

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
			if (rockTimer <= 0) {

				//Reset timer
				rockTimer = ROCK_COOLDOWN;

				SpriteComponent* ownSprite = owner->GetComponent<SpriteComponent>();

				//Set values to be passed into the object factories create methode.
				ObjectFactoryPresets presets;
				presets.bodyInitializers.pDevice = ownBody->pDevice;
				presets.pDevice = ownBody->pDevice;
				presets.objectType = "Rock";
				presets.spriteInitializers.textures.push_back(library->artLibrary.find("Rock")->second);
				presets.spriteInitializers.textures.push_back(library->artLibrary.find("Rock")->second);
				presets.spriteInitializers.textures.push_back(library->artLibrary.find("Rock")->second);
				presets.spriteInitializers.textures.push_back(library->artLibrary.find("Rock")->second);
				presets.spriteInitializers.currentTexture = presets.spriteInitializers.textures[0];
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
					presets.bodyInitializers.linearVelocity = { -500.0f, -20.0f };
					presets.bodyInitializers.angularVelocity = -10.0f;
				}
				else if (ownBody->getState() == BodyComponent::STANDING_RIGHT) {
					presets.bodyInitializers.position.x = ownBody->getPosition().x + ownSprite->currentTexture->getWidth() + 5.0f;
					presets.bodyInitializers.linearVelocity = { 500.0f, -20.0f };
					presets.bodyInitializers.angularVelocity = 10.0f;
				}

				//Create rock.
				rock = objectFactory->create(presets);
				sDevice->playSound("throwing", 0, -1);
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

	return rock; //Returns an rock object if created; otherwise, returns nullptr
}

void SentryBehaviorComponent::start() {
	//No action needed
}

void SentryBehaviorComponent::finish() {
	//No action needed
}
