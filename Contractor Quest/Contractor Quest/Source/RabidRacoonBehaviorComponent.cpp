#include "RabidRacoonBehaviorComponent.h"
#include "Object.h"
#include "BodyComponent.h"
#include "Texture.h"

bool RabidRacoonBehaviorComponent::initialize(ObjectFactoryPresets presets) {
	return true;
}

RabidRacoonBehaviorComponent::RabidRacoonBehaviorComponent(Object * owner, ObjectFactoryPresets presets): Component(owner) {
}

RabidRacoonBehaviorComponent::~RabidRacoonBehaviorComponent() {
}

Object* RabidRacoonBehaviorComponent::update(vector<Object*> objects) {

	BodyComponent* ownBody = owner->GetComponent<BodyComponent>();
	SpriteComponent* ownSprite = owner->GetComponent<SpriteComponent>();

	if (jumpCooldown > 0) jumpCooldown--;

	//Locate Player and determine if the Racoon needs to jump over an object
	bool willJump = false;
	Object* player = nullptr;
	BodyComponent* currentBody;
	SpriteComponent* currentSprite;

	for (int i = 0; i < objects.size(); i++) {

		currentBody = objects.at(i)->GetComponent<BodyComponent>();
		currentSprite = objects.at(i)->GetComponent<SpriteComponent>();

		if (objects.at(i)->getType() == "Player") {
			player = objects.at(i);
		}

		//Racoon will jump if an object is in its way, and if jumpCooldown is 0
		else if (jumpCooldown <= 0 && objectIsInRange(currentBody, currentSprite)) {
			willJump = true;
			jumpCooldown = COOLDOWN_TIME;	//Reset jumpCooldown
		}
	}

	//Determine player's location and follow them.
	BodyComponent* playerBody = player->GetComponent<BodyComponent>();

	if (playerBody->getPosX() <= ownBody->getPosX()) {
		ownBody->setState(BodyComponent::RUNNING_LEFT);
		ownBody->setLinearVelocity({ -RUN_SPEED, ownBody->getVelocity().y });
	}
	else {
		ownBody->setState(BodyComponent::RUNNING_RIGHT);
		ownBody->setLinearVelocity({ RUN_SPEED, ownBody->getVelocity().y });
	}

	//Jump if conditions are met
	if (willJump) ownBody->setLinearImpulse({ 0.0f, -JUMP_HEIGHT });

	return nullptr; //This object will never return an object.
}

void RabidRacoonBehaviorComponent::start() {
	//No action needed.
}

void RabidRacoonBehaviorComponent::finish() {
	//No action needed.
}

bool RabidRacoonBehaviorComponent::objectIsInRange(BodyComponent* objectBody, SpriteComponent* objectSprite)
{
	bool inRange = false;
	BodyComponent* ownBody = owner->GetComponent<BodyComponent>();
	SpriteComponent* ownSprite = owner->GetComponent<SpriteComponent>();

	//Calculations made with respect to the top left pixel of racoon and object

	//Make sure the object isn't below or above the racoon's height (with 1-pixel margin of error)
	if (ownBody->getPosY() < (objectBody->getPosY() + objectSprite->texture->getHeight() + 1.0f)
		&& (ownBody->getPosY() > (objectBody->getPosY() - ownSprite->texture->getHeight() + 1.0f))) {

		//If the object is within detection range and in front of the racoon, set inRange to true
		if (ownBody->getState() == BodyComponent::RUNNING_LEFT
			&& ((abs(ownBody->getPosX() - (objectBody->getPosX() + objectSprite->texture->getWidth())) <= DETECTION_RANGE))
			&& (ownBody->getPosX() > objectBody->getPosX())) inRange = true;

		else if (ownBody->getState() == BodyComponent::RUNNING_RIGHT
			&& ((abs((ownBody->getPosX() + ownSprite->texture->getWidth()) - objectBody->getPosX())) <= DETECTION_RANGE)
			&& (ownBody->getPosX() < objectBody->getPosX())) inRange = true;
	}

	return inRange;
}
