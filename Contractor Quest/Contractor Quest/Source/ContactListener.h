#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "Box2D/Box2D.h"

class Object;

class ContactListener : public b2ContactListener {

public:

	void BeginContact(b2Contact* contact) {}
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

	//PreSolve helper function(s).
	bool playerMobContact(Object* objectA, Object* objectB);
	void handleRacoonObstacleContact(Object* objectA, Object* objectB);
	void handleMobSurfaceContact(b2Body* b2BodyA, Object* objectA, b2Body* b2BodyB, Object* objectB);

private:
	const float ERROR_MARGIN = 20.0f;

};

#endif