#include "PhysicsDevice.h"
#include "Object.h"
#include "Texture.h"
#include "ContactListener.h"

PhysicsDevice::PhysicsDevice() {

}

PhysicsDevice::PhysicsDevice(Position gravity) : gravity(RW2PW(gravity.x), RW2PW(gravity.y))
{	
	
}

PhysicsDevice::~PhysicsDevice() {

}

bool PhysicsDevice::Initialize() {

	world = new b2World(gravity);
	if (world == nullptr) return false;
	ContactListener* c1 = new ContactListener();
	world->SetContactListener(c1);
	return true;
}

bool PhysicsDevice::Update(float dt) {
	world->Step(dt, 8, 3);	//Can adjust numbers as needed
	return true;
}

bool PhysicsDevice::CreateFixture(
	Object * object,
	Position position,
	EngineFloat angle,
	GAME_BODY_TYPE bodyType,
	GAME_OBJECT_SHAPE objectShape,
	EngineFloat density,
	EngineFloat friction,
	EngineFloat restitution,
	EngineFloat angularDamping,
	EngineFloat linearDamping)
{
	//Make body
	b2BodyDef * bd = new b2BodyDef();

	b2PolygonShape pShape;
	b2CircleShape cShape;

	bd->userData = object;

	//FIXME:Add a clause for bullet body types here if projectiles have collision issues!

	switch (bodyType) {
	case GAME_STATIC:
		bd->type = b2_staticBody;
		break;
	case GAME_KINEMATIC:
		bd->type = b2_kinematicBody;
		break;
	case GAME_DYNAMIC:
		bd->type = b2_dynamicBody;
		break;
	}
	bd->position.Set(RW2PW(position.x), RW2PW(position.y));
	bd->angle = RW2PWAngle(angle);	//FIXME: this may need to be changed to RW2PW

	//Set body in world
	b2Body* body = world->CreateBody(bd);
	body->SetAngularDamping(angularDamping);
	body->SetLinearDamping(linearDamping);

	//Create fixture
	b2FixtureDef shapefd;

	switch (objectShape) {
	case GAME_RECTANGLE:
		pShape.SetAsBox(
			RW2PW(object->getTexture()->getWidth() / 2.0f),
			RW2PW(object->getTexture()->getHeight() / 2.0f));
		shapefd.shape = &pShape;
		break;

	case GAME_CIRCLE:
		cShape.m_radius = (RW2PW(object->getTexture()->getWidth() / 2.0f));
		shapefd.shape = &cShape;
		break;
	}

	shapefd.density = density;
	shapefd.friction = friction;
	shapefd.restitution = restitution;

	body->CreateFixture(&shapefd);

	return true;
}

bool PhysicsDevice::createEdge(Position start, Position finish)
{
	b2BodyDef bd;
	b2Body* edge = world->CreateBody(&bd);
	b2EdgeShape shape;

	shape.Set(GV2PV(start), GV2PV(finish));
	edge->CreateFixture(&shape, 0);

	return true;
}

bool PhysicsDevice::createDistanceJoint(
	Object* object1,
	Object* object2,
	EngineFloat maxDistance,
	Position anchor1,
	Position anchor2,
	bool collide)
{
	b2DistanceJointDef jd;
	jd.bodyA = findBody(object1);
	jd.bodyB = findBody(object2);
	jd.collideConnected = collide;
	jd.localAnchorA = GV2PV(anchor1);
	jd.localAnchorB = GV2PV(anchor2);
	jd.length = RW2PW(maxDistance);

	world->CreateJoint(&jd);
	return true;
}

//Overload for createDistanceJoint that uses object centers
bool PhysicsDevice::createDistanceJoint(
	Object * object1,
	Object * object2,
	EngineFloat maxDistance,
	bool collide)
{
	return (createDistanceJoint(
		object1,
		object2,
		maxDistance,
		PV2GV(findBody(object1)->GetLocalCenter()),
		PV2GV(findBody(object2)->GetLocalCenter()),
		collide
	));
}

bool PhysicsDevice::createRopeJoint(
	Object* object1,
	Object* object2,
	EngineFloat maxDistance,
	Position anchor1,
	Position anchor2,
	bool collide)
{
	b2RopeJointDef jd;
	jd.bodyA = findBody(object1);
	jd.bodyB = findBody(object2);
	jd.collideConnected = collide;
	jd.localAnchorA = GV2PV(anchor1);
	jd.localAnchorB = GV2PV(anchor2);
	jd.maxLength = RW2PW(maxDistance);

	world->CreateJoint(&jd);
	return true;
}

//Overload for createRopeJoint that uses object centers
bool PhysicsDevice::createRopeJoint(
	Object * object1,
	Object * object2,
	EngineFloat maxDistance,
	bool collide)
{
	return (createRopeJoint(
		object1,
		object2,
		maxDistance,
		PV2GV(findBody(object1)->GetLocalCenter()),
		PV2GV(findBody(object2)->GetLocalCenter()),
		collide
	));
}

bool PhysicsDevice::createRevolvingJoint(
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
	EngineFloat maxMotorTorque)
{
	b2RevoluteJointDef jd;
	jd.bodyA = findBody(object1);
	jd.bodyB = findBody(object2);
	jd.collideConnected = collide;
	jd.localAnchorA = GV2PV(anchor1);
	jd.localAnchorB = GV2PV(anchor2);
	jd.referenceAngle = RW2PWAngle(referenceAngle);
	jd.enableLimit = enableLimit;
	jd.lowerAngle = RW2PWAngle(lowerAngle);
	jd.upperAngle = RW2PWAngle(upperAngle);
	jd.enableMotor = enableMotor;
	jd.motorSpeed = RW2PW(motorSpeed);
	jd.maxMotorTorque = RW2PW(maxMotorTorque);

	world->CreateJoint(&jd);
	return true;
}

bool PhysicsDevice::deleteBody(Object * object)
{
	b2Body* body = findBody(object);
	world->DestroyBody(body);
	return true;
}

bool PhysicsDevice::SetTransform(Object * object, Position position, EngineFloat angle)
{
	b2Body* body = findBody(object);
	body->SetTransform(
		GV2PV(position),
		RW2PWAngle(angle)
	);
	return true;
}

bool PhysicsDevice::SetLinearVelocity(Object * object, Position linearVelocity)
{
	b2Body* body = findBody(object);
	body->SetLinearVelocity(GV2PV(linearVelocity));
	return true;
}

bool PhysicsDevice::SetAngularVelocity(Object * object, EngineFloat angularVelocity)
{
	b2Body* body = findBody(object);
	body->SetAngularVelocity(RW2PW(angularVelocity));
	return true;
}

bool PhysicsDevice::SetTorque(Object * object, EngineFloat torque)
{
	b2Body* body = findBody(object);
	body->ApplyTorque(RW2PW(torque), true);
	return true;
}

bool PhysicsDevice::SetLinearImpulse(Object * object, Position forceVec, Position forceCenter)
{
	b2Body* body = findBody(object);
	body->ApplyLinearImpulse(
		GV2PV(forceVec),
		body->GetWorldPoint(GV2PV(forceCenter)),
		true
	);

	return true;
}

bool PhysicsDevice::SetStatic(Object * object)
{
	b2Body* body = findBody(object);
	body->SetType(b2_staticBody);
	return true;
}

bool PhysicsDevice::SetStopPhysics(Object * object)
{
	b2Body* body = findBody(object);
	body->SetActive(false);
	return true;
}

bool PhysicsDevice::SetAngle(Object * object, EngineFloat angle)
{
	b2Body* body = findBody(object);
	body->SetTransform(body->GetPosition(), RW2PWAngle(angle));
	return true;
}

EngineFloat PhysicsDevice::GetAngularVelocity(Object * object)
{
	b2Body* body = findBody(object);
	return (PW2RW(body->GetAngularVelocity()));
}

Position PhysicsDevice::GetPosition(Object * object)
{
	//b2Body* body = findBody(object);
	//return (PV2GV(body->GetPosition()));
	return (AlignCenters(object));
}

EngineFloat PhysicsDevice::GetAngle(Object * object)
{
	b2Body* body = findBody(object);
	return (PW2RWAngle(body->GetAngle()));
}

Position PhysicsDevice::GetVelocity(Object * object)
{
	b2Body* body = findBody(object);
	return (PV2GV(body->GetLinearVelocity()));
}

Position PhysicsDevice::GetLinearVelocity(Object * object)
{
	b2Body* body = findBody(object);
	return (PV2GV(body->GetLinearVelocity()));
}

Position PhysicsDevice::AlignCenters(Object * object)
{
	b2Body* body = findBody(object);
	b2Vec2 physPosition = body->GetPosition();
	Position position;
	Texture* texture = object->getTexture();

	//Subtract half the height and width
	position.x = PW2RW(physPosition.x) - (texture->getWidth() / 2);
	position.y = PW2RW(physPosition.y) - (texture->getHeight() / 2);

	return (position);
}

Position PhysicsDevice::PV2GV(b2Vec2 v)
{
	Position temp;
	temp.x = PW2RW(v.x);
	temp.y = PW2RW(v.y);
	return temp;
}

b2Body* PhysicsDevice::findBody(Object* object) {

	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext()) {

		if (object == body->GetUserData()) {
			return body;
		}
	}

	return nullptr;
}
