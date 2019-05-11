#include "Engine.h"
#include "Library.h"
#include "Object.h"
#include "Timer.h"
#include "InputDevice.h"
#include "PhysicsDevice.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"
#include "View.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include <iostream>

//default constructor
Engine::Engine()
{
	graphicsDevice = new GraphicsDevice(1920, 1080, true);
	soundDevice = new SoundDevice();
	objectLibrary = new Library(graphicsDevice);
	soundDevice->getLibrary(objectLibrary);
	factory = new ObjectFactory(graphicsDevice, objectLibrary);
	timer = new Timer;
	

	if (!timer->Initialize(100)) {
		printf("Framer Timer couldn't initialize!");
		exit(1);
	}

	view = graphicsDevice->getView();
	currentLevel = 0;
}

//constructor that loads level
Engine::Engine(vector<string> levelPaths)
{
	//Initilize devices/members.
	graphicsDevice = new GraphicsDevice(1024, 768, true);
	soundDevice = new SoundDevice();
	objectLibrary = new Library(graphicsDevice);
	soundDevice->getLibrary(objectLibrary);
	factory = new ObjectFactory(graphicsDevice, objectLibrary);
	inputDevice = new InputDevice(soundDevice);

	pDevice = new PhysicsDevice(GRAVITY);
	if (!pDevice->Initialize()) {
		printf("Physics Device couldn't initialize!");
		exit(1);
	}
	
	timer = new Timer;
	if (!timer->Initialize(100)) {
		printf("Framer Timer couldn't initialize!");
		exit(1);
	}

	Mix_PlayMusic(soundDevice->getMusic("background"), -1);

	view = graphicsDevice->getView();

	levels = levelPaths;
	currentLevel = 0;

	//Load the first level
	loadLevel(levels.at(currentLevel));
}

//deconstructor
Engine::~Engine() {

}

//Resets view and empties object vector.
void Engine::reset() {
	view->update(0.0f);

	for (int i = 0; i < objects.size(); i++) {
		delete objects.at(i);
	}
	objects.clear();
}

void Engine::loadLevel(string levelPath) {	
	tinyxml2::XMLDocument doc;
	string elementType;

	if (doc.LoadFile(levelPath.c_str()) != tinyxml2::XML_SUCCESS) {
		printf("Bad File Path");
		exit(1);
	}

	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* element = root->FirstChildElement();

	while (element) {
		elementType = element->Attribute("elementType");
		if (elementType == "Joint") {
			createJointedObject(element, graphicsDevice, objectLibrary, inputDevice, pDevice, soundDevice);
		}
		else {
			objects.push_back(factory->create(element, graphicsDevice, objectLibrary, inputDevice, pDevice, soundDevice));
		}

		element = element->NextSiblingElement();
	}

}

void Engine::update() {

	vector<Object*>::iterator objectIter;

	//Remove "dead" objects.
	for (objectIter = objects.begin(); objectIter < objects.end(); /*Incremented in loop*/) {
		if ((*objectIter)->getIsDead()) {
			delete (*objectIter);
			objectIter = objects.erase(objectIter);
		}
		else {
			objectIter++;
		}
	}

	//Update Input Device to obtain current key states.
	inputDevice->update();

	//Update all objects, temporarily store dynamically created objects, and locate the player.
	Object* newObject;
	vector<Object*> newObjectVector;
	Object* player = nullptr;
	for (objectIter = objects.begin(); objectIter < objects.end(); objectIter++) { 
		newObject = (*objectIter)->update(objects);

		if (newObject != nullptr) {
			newObjectVector.push_back(newObject);
		}

		//Locate player.  To be used to update view.
		if ((*objectIter)->getType() == "Player") {
			player = (*objectIter);
		}
	}

	//Locate player's body and sprite compoents
	BodyComponent* playerBody = player->GetComponent<BodyComponent>();
	SpriteComponent* playerSprite = player->GetComponent<SpriteComponent>();

	//Keep player within the horizontal bounds of the view and from going left of the leftmost portion of the map.
	if (playerBody->getPosX() < 0) {
		playerBody->setLinearVelocity({ 0.0f, playerBody->getVelocity().y });
		playerBody->setPosition({ (playerSprite->texture->getWidth() / 2.0f), playerBody->getPosY() + playerSprite->texture->getHeight()/2.0f });
	}
	else if (playerBody->getPosX() < view->getPosX()) {
		playerBody->setLinearVelocity({ 0.0f, playerBody->getVelocity().y });
		playerBody->setPosition({ (playerSprite->texture->getWidth() / 2.0f) + view->getPosX(), playerBody->getPosY() + playerSprite->texture->getHeight() / 2.0f });
	}

	//If the player has exceeded the mid-point point of the view, move the view so that the player 
	//now appears to be at the mid-point of screen.
	if (playerBody->getPosX() > (view->getPosX() + (graphicsDevice->SCREEN_WIDTH / 2))) {
		view->update(playerBody->getPosX() - (graphicsDevice->SCREEN_WIDTH / 2));
	}

	//Player dies if they fall below the screen
	if (playerBody->getPosY() > (view->getPosY() + (graphicsDevice->SCREEN_HEIGHT))) {
		player->setIsDead(true);
	}

	//Add dynamically created objects to engine's objects vector.
	for (objectIter = newObjectVector.begin(); objectIter < newObjectVector.end(); objectIter++) {
		objects.push_back((*objectIter));
	}

	pDevice->Update(DT);
}

void Engine::draw() {
	graphicsDevice->Begin();
	for (auto& object : objects) {
		object->draw();
	}
	
	graphicsDevice->Present();
}

bool Engine::run() {

	//Terminate loop if we have quit.
	if (inputDevice->getEvent(InputDevice::QUIT)) {
		return false;
	}

	//Handle Win and Loss conditions
	vector<Object*>::iterator objectIter;
	for (objectIter = objects.begin(); objectIter < objects.end(); objectIter++) {

		//If the player dies, Game Over
		if ((*objectIter)->getType() == "Player") {
			if ((*objectIter)->getIsDead()) {
				cout << "Player died.  Game Over" << endl;
				return false;
			}
		}

		//If level is complete, transition to the next level or end the game if there are no others
		else if ((*objectIter)->getType() == "Building" || (*objectIter)->getType() == "Lunchbox") {
			if ((*objectIter)->getIsDead()) {

				cout << "Level Complete!" << endl;
				currentLevel++;

				//Go to next level if there are others
				if (currentLevel < NUM_LEVELS) {
					reset();
					loadLevel(levels.at(currentLevel));
					break;
				}

				//End the game if there are no more levels
				else return false;
			}
		}
	}

	//Start frame timer
	timer->start();

	update();
	draw();
	
	//Delay until proper refresh time has passed.
	timer->fpsRegulate();

	return true;
}

//Creates two objects jointed together
void Engine::createJointedObject(tinyxml2::XMLElement * jointElement, GraphicsDevice * gDevice, Library * objectLibrary, InputDevice * inputDevice, PhysicsDevice * pDevice, SoundDevice* sDevice)
{
	//Set joint presets
	Joints jointPresets;
	jointElement->QueryFloatAttribute("object1AnchorX", &jointPresets.AnchorA.x);
	jointElement->QueryFloatAttribute("object1AnchorY", &jointPresets.AnchorA.y);
	jointElement->QueryFloatAttribute("object2AnchorX", &jointPresets.AnchorB.x);
	jointElement->QueryFloatAttribute("object2AnchorY", &jointPresets.AnchorB.y);
	jointElement->QueryBoolAttribute("collide", &jointPresets.collide);
	jointElement->QueryFloatAttribute("maxDistance", &jointPresets.JointLimit);

	tinyxml2::XMLElement* objectElement = jointElement->FirstChildElement();

	Object* object1 = factory->create(objectElement, graphicsDevice, objectLibrary, inputDevice, pDevice, sDevice);
	objects.push_back(object1);
	objectElement = objectElement->NextSiblingElement();
	Object* object2 = factory->create(objectElement, graphicsDevice, objectLibrary, inputDevice, pDevice, sDevice);
	objects.push_back(object2);

	//Call createDistanceJoint(Object1*, Object2*, EngineFloat maxDistance, Position anchor1, Position anchor2)
	pDevice->createDistanceJoint(object1, object2, jointPresets.JointLimit, jointPresets.AnchorA, jointPresets.AnchorB, jointPresets.collide);
}