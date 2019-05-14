#include "SpriteComponent.h"
#include "Object.h"
#include "GraphicsDevice.h"
#include "InputComponent.h"
#include "tinyxml2.h"
#include "Engine.h"
#include "Definitions.h"
#include "Library.h"
#include "Texture.h"
#include "BodyComponent.h"
#include "View.h"

using namespace std;

SpriteComponent::SpriteComponent(Object* owner, const SpritePresets& presets) :Component(owner)
{
	this->gDevice = presets.gdevice;
	this->currentTexture = presets.currentTexture;
}

SpriteComponent::~SpriteComponent() {
}

bool SpriteComponent::initialize(ObjectFactoryPresets presets)
{
	this->gDevice = presets.spriteInitializers.gdevice;
	this->pDevice = presets.pDevice;
	currentTexture = presets.spriteInitializers.currentTexture;
	textures = presets.spriteInitializers.textures;
	
	return true;
}

void SpriteComponent::addTexture(Texture* texture) {
	textures.push_back(texture);
}

void SpriteComponent::draw() {
	Position position = pDevice->GetPosition(owner);
	float angle = pDevice->GetAngle(owner);
	View* view = gDevice->getView();
	
	currentTexture->draw(gDevice->getRenderer(), { position.x - view->getPosX(), position.y - view->getPosY() }, angle);
}

Object* SpriteComponent::update(vector<Object*>)
{
	currentTexture = textures[owner->GetComponent<BodyComponent>()->getState()];

	if (currentTexture == nullptr) {
		textures[0]; //If an error occurs, it will default to the first texture.
	}

	return nullptr;
}

void SpriteComponent::start() {

}

void SpriteComponent::finish() {

}