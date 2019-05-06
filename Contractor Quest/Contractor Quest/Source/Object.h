#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <memory>
#include "ObjectFactory.h"
#include "Component.h"

using namespace std;

class View;
class GraphicsDevice;
class PhysicsDevice;
class Texture;
class Component;
class ObjectFactory;
struct ObjectFactoryPresets;

class Object {

	public:
		//Default Constructor/Deconstructor
		Object();
		~Object();

		bool initialize(ObjectFactoryPresets presets);
		void addComponent(Component* component);
		Object* update(vector<Object*>);
		void draw();
		string getType();
		Texture* getTexture();
		PhysicsDevice* getPhysicsDevice();
		bool getIsDead();

		void setIsDead(bool);

		template<class T>
		T* GetComponent() const
		{
			for (auto& component : components)
			{
				T* target = nullptr;
				if (target = dynamic_cast<T*>(component))
				{
					return(target);
				}
			}
			return(nullptr);
		}
		

	protected:
		vector<Component*> components;
		bool initialized;
	
		string type;
		bool isDead;
	
};

#endif