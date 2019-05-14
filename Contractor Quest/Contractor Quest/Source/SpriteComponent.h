#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "BodyComponent.h"
#include "Definitions.h"
#include "tinyxml2.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Texture;

class SpriteComponent : public Component {
	public:
		//constructors and deconstructors
		SpriteComponent()=delete;
		SpriteComponent(Object* owner, const SpritePresets& presets);
		~SpriteComponent();

		bool initialize(ObjectFactoryPresets presets);
		void addTexture(Texture* texture);

		void draw();

		Object* update(vector<Object*>);
		void start();
		void finish();
		Texture* currentTexture = nullptr;
		BodyComponent* spriteBody;
		SpriteComponent* sprite;
		

	protected:
		GraphicsDevice* gDevice = nullptr;
		PhysicsDevice* pDevice = nullptr;
		vector<Texture*> textures;
};

#endif