#include "ContactListener.h"
#include "Object.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "PhysicsDevice.h"
#include <string>

//Define how objects should interact here; write/re-write code as necessary
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());

	//If a rock collides with the player, set both objects to be destroyed.
	if (objectA->getType() == "Player" && objectB->getType() == "Rock" || 
		objectA->getType() == "Rock" && objectB->getType() == "Player") {
		objectA->setIsDead(true);
		objectB->setIsDead(true);
	}

	//If a rock collides with an object other than a rock, set the rock to be destroyed.
	if (objectA->getType() == "Rock" && (objectB->getType() != "Rock" && objectB->getType() != "CrazyPerson" && objectB->getType() != "CrazyPersonArm")) {
		objectA->setIsDead(true);
	}
	else if (objectB->getType() == "Rock" && (objectA->getType() != "Rock" && objectA->getType() != "CrazyPerson" && objectA->getType() != "CrazyPersonArm")) {
		objectB->setIsDead(true);
	}

	//Handle collisions between the player and mobs.
	//First determine if player mob contact occured.
	if (playerMobContact(objectA, objectB)) {

		//Make player and mob b2Body & object pointers to make future checks easier.
		b2Body* playerB2Body = nullptr;
		Object* playerObject = nullptr;
		b2Body* mobB2Body = nullptr;
		Object* mobObject = nullptr;
		if (objectA->getType() == "Player") {
			playerB2Body = bodyA;
			playerObject = objectA;
			mobB2Body = bodyB;
			mobObject = objectB;
		}
		else {
			playerB2Body = bodyB;
			playerObject = objectB;
			mobB2Body = bodyA;
			mobObject = objectA;
		}
		
		//FIXME: For now, player mob contact results in the death of the player.  In the future, this will
		//likely be changed to check how the contact occured.  If the player stomped the mob, the mob will be
		//killed instead.  Therefore, the pointers remain to be used when such changes are made.

		playerObject->setIsDead(true);
	}

	//Handle collisions between racoons and blocks in racoons path.
	//Results in racoon turning around.
	if (racoonBlockContact(objectA, objectB)) {
		//Make racoon and block component pointers make the following work easier.
		BodyComponent* racoonBody = nullptr;
		SpriteComponent* racoonSprite = nullptr;
		BodyComponent* blockBody = nullptr;
		SpriteComponent* blockSprite = nullptr;
		if (objectA->getType() == "Racoon") {
			racoonBody = objectA->GetComponent<BodyComponent>();
			racoonSprite = objectA->GetComponent<SpriteComponent>();
			blockBody = objectB->GetComponent<BodyComponent>();
			blockSprite = objectB->GetComponent<SpriteComponent>();
		}
		else {
			racoonBody = objectB->GetComponent<BodyComponent>();
			racoonSprite = objectB->GetComponent<SpriteComponent>();
			blockBody = objectA->GetComponent<BodyComponent>();
			blockSprite = objectA->GetComponent<SpriteComponent>();
		}

		//Check that the block is not underneath the racoon.
		if ((blockBody->getPosition().y  < racoonBody->getPosition().y + racoonSprite->texture->getHeight()) ||
			(blockBody->getPosition().y + blockSprite->texture->getHeight() < racoonBody->getPosition().y + racoonSprite->texture->getHeight())) {
			//Turn around.
			if (racoonBody->getState() == BodyComponent::RUNNING_LEFT) {
				racoonBody->setState(BodyComponent::RUNNING_RIGHT);
			}
			else if (racoonBody->getState() == BodyComponent::RUNNING_RIGHT) {
				racoonBody->setState(BodyComponent::RUNNING_LEFT);
			}
		}
	}

}

//Returns true if one object is the player and the other is an enemy mob, else return false.
bool ContactListener::playerMobContact(Object* objectA, Object* objectB) {
	string objectAType = objectA->getType();
	string objectBType = objectB->getType();

	if (objectAType == "Player" || objectBType == "Player") {
		if ((objectAType == "Racoon" || objectAType == "RabidRacoon" || objectAType == "CrazyPerson") ||
			(objectBType == "Racoon" || objectBType == "RabidRacoon" || objectBType == "CrazyPerson")) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//Returns true if one object is a racoon and the other is a block, else returns false.
bool ContactListener::racoonBlockContact(Object* objectA, Object* objectB) {
	string objectAType = objectA->getType();
	string objectBType = objectB->getType();

	if (objectAType == "Racoon" || objectBType == "Racoon") {
		if (objectAType == "Block" || objectBType == "Block") {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}