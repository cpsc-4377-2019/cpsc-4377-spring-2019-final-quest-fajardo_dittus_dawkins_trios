#ifndef COMPONENT_H
#define COMPONENT_H

//Do not include ANY other header files here!
#include "Initializers.h"
#include <vector>

class Object;

class Component {
	public:
		//Constructors and Deconstructors
		Component() = delete;
		Component(Object* owner);
		virtual ~Component() {}
		
		//Getter
		Object* getOwner();
		void OwnerDestroyed();
		
		virtual bool initialize(ObjectFactoryPresets presets) = 0;
		virtual Object* update(vector<Object*>) = 0;
		virtual void start() = 0;
		virtual void finish() = 0;
		

	protected:
		Object* owner;
};

#endif