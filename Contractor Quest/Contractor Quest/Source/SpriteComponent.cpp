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
	this->texture = presets.spriteTexture;
}

SpriteComponent::~SpriteComponent() {
}

bool SpriteComponent::initialize(ObjectFactoryPresets presets)
{
	this->gDevice = presets.spriteInitializers.gdevice;
	this->pDevice = presets.pDevice;
	texture = presets.spriteInitializers.spriteTexture;
	
	return true;
}

void SpriteComponent::draw() {
	Position position = pDevice->GetPosition(owner);
	float angle = pDevice->GetAngle(owner);
	View* view = gDevice->getView();
	
	texture->draw(gDevice->getRenderer(), { position.x - view->getPosX(), position.y - view->getPosY() }, angle);
}

Object * SpriteComponent::update(vector<Object*>)
{
	return nullptr;
}

void SpriteComponent::start() {

}

void SpriteComponent::finish() {

}