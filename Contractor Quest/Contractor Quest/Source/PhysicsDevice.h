#ifndef PHYSICSDEVICE_H
#define PHYSICSDEVICE_H

#include "Box2D/Box2D.h"
#include "Definitions.h"

class Object;	//Forward declarations

class PhysicsDevice {

public:

	//Constructors/Deconstructors
	PhysicsDevice();
	PhysicsDevice(Position gravity);
	~PhysicsDevice();

	//Public Methods
	bool Initialize();
	bool Update(float dt);
	bool CreateFixture(
		Object* object,
		Position position,
		EngineFloat angle,
		GAME_BODY_TYPE bodyType,
		GAME_OBJECT_SHAPE objectShape,
		EngineFloat density,
		EngineFloat friction,
		EngineFloat restitution,
		EngineFloat angularDamping,
		EngineFloat linearDamping
		);

	bool createEdge(Position start, Position finish);

	bool createDistanceJoint(
		Object* object1,
		Object* object2,
		EngineFloat maxDistance,
		Position anchor1,
		Position anchor2,
		bool collide);
	bool createDistanceJoint(
		Object* object1,
		Object* object2,
		EngineFloat maxDistance,
		bool collide);

	bool createRopeJoint(
		Object* object1,
		Object* object2,
		EngineFloat maxDistance,
		Position anchor1,
		Position anchor2,
		bool collide);
	bool createRopeJoint(
		Object* object1,
		Object* object2,
		EngineFloat maxDistance,
		bool collide);

	bool createRevolvingJoint(
		Object* object1,
		Object* object2,
		Position anchor1,
		Position anchor2,
		bool collide,
		EngineFloat referenceAngle,
		bool enableLimit,
		EngineFloat lowerAngle,
		EngineFloat upperAngle,
		bool enableMotor,
		EngineFloat motorSpeed,
		EngineFloat maxMotorTorque);

	bool deleteBody(Object* object);
	bool SetTransform(Object* object, Position position, EngineFloat angle);
	bool SetLinearVelocity(Object* object, Position linearVelocity);
	bool SetAngularVelocity(Object* object, EngineFloat angularVelocity);
	bool SetTorque(Object* object, EngineFloat torque);
	bool SetLinearImpulse(Object* object, Position forceVec, Position forceCenter);
	bool SetStatic(Object* object);
	bool SetStopPhysics(Object* object);
	bool SetAngle(Object* object, EngineFloat angle);

	EngineFloat GetAngularVelocity(Object* object);
	Position GetPosition(Object* object);
	EngineFloat GetAngle(Object* object);
	Position GetVelocity(Object* object);
	Position GetLinearVelocity(Object* object);
	Position AlignCenters(Object* object);

private:

	//Physics world to real world conversions (and vice-versa)
	inline float PW2RW(EngineFloat x) { return x * fPRV; }
	inline float RW2PW(EngineFloat x) { return x / fPRV; }
	inline float RW2PW(EngineInt x) { return (float)x / fPRV; }	

	inline float RW2PWAngle(EngineFloat x) { return((float)x*(2.0f*3.14149f) / 360.0f); }
	inline float PW2RWAngle(EngineFloat x) { return((float)x*360.0f / (2.0f*3.14149f)); }

	inline b2Vec2 GV2PV(Position v) { return (b2Vec2(RW2PW(v.x), RW2PW(v.y))); }
	inline Position PV2GV(b2Vec2 v);

	//Other Private Methods
	b2Body* findBody(Object* object);

	//Private Members
	b2World * world;
	const b2Vec2 gravity;
};

#endif
