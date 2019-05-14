#include "ContactListener.h"
#include "Object.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "WanderBehaviorComponent.h"
#include "Texture.h"
#include "PhysicsDevice.h"
#include <string>

void ContactListener::EndContact(b2Contact* contact) {
	//If an object is not in contact with anything, set isGrounded to false.
	if (!(contact->IsTouching())) {
		b2Body* pBody = contact->GetFixtureA()->GetBody();
		Object* airbornObject = static_cast<Object*>(pBody->GetUserData());

		airbornObject->GetComponent<BodyComponent>()->setIsGrounded(false);
	}
}

//Define how objects should interact here; write/re-write code as necessary
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());

	//If the player collides with the building or lunchbox, destroy the object (ending the level)
	if (objectA->getType() == "Player" && (objectB->getType() == "Building" || objectB->getType() == "Lunchbox")) objectB->setIsDead(true);
	else if ((objectA->getType() == "Building" || objectA->getType() == "Lunchbox") && objectB->getType() == "Player") objectA->setIsDead(true);

	//If a rock collides with the player, set both objects to be destroyed.
	if (objectA->getType() == "Player" && objectB->getType() == "Rock" || 
		objectA->getType() == "Rock" && objectB->getType() == "Player") {
		objectA->setIsDead(true);
		objectB->setIsDead(true);
	}

	//If a rock collides with an object other than a rock or crazyPerson, set the rock to be destroyed.
	if (objectA->getType() == "Rock" && (objectB->getType() != "Rock" && objectB->getType() != "CrazyPerson" && objectB->getType() != "CrazyPersonArm")) {
		objectA->setIsDead(true);
	}
	else if (objectB->getType() == "Rock" && (objectA->getType() != "Rock" && objectA->getType() != "CrazyPerson" && objectA->getType() != "CrazyPersonArm")) {
		objectB->setIsDead(true);
	}

	//Handle collisions between the player and mobs.
	//First determine if player mob contact occured.
	if (playerMobContact(objectA, objectB)) {

		//Make player and mob object pointers to make future checks easier.
		Object* playerObject = nullptr;
		Object* mobObject = nullptr;
		if (objectA->getType() == "Player") {
			playerObject = objectA;
			mobObject = objectB;
		}
		else {
			playerObject = objectB;
			mobObject = objectA;
		}

		//Create Component pointers to make the following checks easier.
		BodyComponent* playerBody = playerObject->GetComponent<BodyComponent>();
		SpriteComponent* playerSprite = playerObject->GetComponent<SpriteComponent>();
		BodyComponent* mobBody = mobObject->GetComponent<BodyComponent>();
		SpriteComponent* mobSprite = mobObject->GetComponent<SpriteComponent>();

		if (((playerBody->getPosition().y + playerSprite->currentTexture->getHeight() - ERROR_MARGIN) <= mobBody->getPosition().y)) {
			mobObject->setIsDead(true);
		}
		else {
			playerObject->setIsDead(true);
		}
	}

	//Handle collisions between racoons and obstacles in racoons path.
	//Results in racoon turning around.
	handleRacoonObstacleContact(objectA, objectB);

	//Sets isGrounded based on whether a dynamic object is in contact with an object.
	handleMobSurfaceContact(bodyA, objectA, bodyB, objectB);
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
void ContactListener::handleRacoonObstacleContact(Object* objectA, Object* objectB) {

	if (objectA->getType() == "Racoon" || objectB->getType() == "Racoon") {
		//Make racoon and obstacle component pointers make the following work easier.
		BodyComponent* racoonBody = nullptr;
		SpriteComponent* racoonSprite = nullptr;
		WanderBehaviorComponent* racoonWanderBehavior = nullptr;
		BodyComponent* obstacleBody = nullptr;
		SpriteComponent* obstacleSprite = nullptr;
		if (objectA->getType() == "Racoon") {
			racoonBody = objectA->GetComponent<BodyComponent>();
			racoonSprite = objectA->GetComponent<SpriteComponent>();
			racoonWanderBehavior = objectA->GetComponent<WanderBehaviorComponent>();
			obstacleBody = objectB->GetComponent<BodyComponent>();
			obstacleSprite = objectB->GetComponent<SpriteComponent>();
		}
		else {
			racoonBody = objectB->GetComponent<BodyComponent>();
			racoonSprite = objectB->GetComponent<SpriteComponent>();
			racoonWanderBehavior = objectB->GetComponent<WanderBehaviorComponent>();
			obstacleBody = objectA->GetComponent<BodyComponent>();
			obstacleSprite = objectA->GetComponent<SpriteComponent>();
		}

		//Check that the obstacle is not underneath or on top of the racoon.
		if (((obstacleBody->getPosition().y < racoonBody->getPosition().y + racoonSprite->currentTexture->getHeight()) ||
			(obstacleBody->getPosition().y + obstacleSprite->currentTexture->getHeight() < racoonBody->getPosition().y + racoonSprite->currentTexture->getHeight()))
			&& ((obstacleBody->getPosition().y + obstacleSprite->currentTexture->getHeight()) > (racoonBody->getPosition().y))) {
			if (racoonWanderBehavior->turnTimer <= 0) {
				//Turn around.
				if (racoonBody->getState() == BodyComponent::RUNNING_LEFT) {
					racoonBody->setState(BodyComponent::RUNNING_RIGHT);
				}
				else if (racoonBody->getState() == BodyComponent::RUNNING_RIGHT) {
					racoonBody->setState(BodyComponent::RUNNING_LEFT);
				}

				racoonWanderBehavior->turnTimer = racoonWanderBehavior->TURN_COOLDOWN;
			}
		}
	}
}

//Checks if a dynamic object has made contact with an object.  If so, it is set to be grounded.
//This is used to limit jumping and allows for wall jumps.
void ContactListener::handleMobSurfaceContact(b2Body* b2BodyA, Object* objectA, b2Body* b2BodyB, Object* objectB) {
	if (b2BodyA->GetType() == GAME_BODY_TYPE::GAME_DYNAMIC) {
		objectA->GetComponent<BodyComponent>()->setIsGrounded(true);
	}
	if (b2BodyB->GetType() == GAME_BODY_TYPE::GAME_DYNAMIC) {
		objectB->GetComponent<BodyComponent>()->setIsGrounded(true);
	}
}