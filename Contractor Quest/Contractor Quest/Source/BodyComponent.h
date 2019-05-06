#ifndef BODYCOMPONENT_H
#define BODYCOMPONENT_H

#include "Component.h"
#include "Definitions.h"
#include "PhysicsDevice.h"

class Object;
class GraphicsDevice;
class PhysicsDevice;

class BodyComponent: public Component {
	public:
		//constructors/deconstructors
		BodyComponent()=delete;
		BodyComponent(Object* owner, PhysicsDevice* pDevice, BodyPresets presets);
		~BodyComponent();

		Object* update(vector<Object*>);
		void start();
		void finish();


		bool initialize(ObjectFactoryPresets presets);
		
		enum STATE_TYPES { STANDING_LEFT, STANDING_RIGHT, RUNNING_LEFT, RUNNING_RIGHT };

		Position getPosition();
		EngineFloat getAngle();
		EngineFloat getPosX();
		EngineFloat getPosY(); 
		Position getVelocity();
		int getState() { return state; }
		GAME_BODY_TYPE getBodyType() { return bodyType; }

		void setPosition(Position position);
		void setPosX(EngineFloat x) { setPosition({ x, position.y }); }
		void setPosY(EngineFloat y) { setPosition({ position.x, y }); }
		void setState(int state) { this->state = state; }
		void setAngle(EngineFloat angle);
		void setVelocity(Position velocity);
		void setLinearImpulse(Position forceVec);
		void setLinearVelocity(Position velocity);

		PhysicsDevice* pDevice;

protected:
	    Position position;
		float angle;
		int state;
		GAME_BODY_TYPE bodyType;
};

#endif