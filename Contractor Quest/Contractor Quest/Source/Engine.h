#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include "tinyxml2.h"

using namespace std;

class Library;
class InputDevice;
class PhysicsDevice;
class View;
class Object;
class Timer;
class GraphicsDevice;
class ObjectFactory;
class SoundDevice;

class Engine {

public:

	Engine();
	Engine(vector<string>);
	~Engine();

	void reset();
	void loadLevel(string levelPath);
	void update();
	void draw();
	bool run();
	
private:

	void createJointedObject(tinyxml2::XMLElement* jointElement, GraphicsDevice*, Library*, InputDevice*, PhysicsDevice*, SoundDevice*);
	void checkWinLoseConditions();


	Library* objectLibrary;
	ObjectFactory* factory;
	vector <Object*> objects;
	InputDevice* inputDevice;
	PhysicsDevice* pDevice;
	Timer* timer;
	GraphicsDevice* graphicsDevice;
	View* view;
	SoundDevice* soundDevice;

	int currentLevel;
	vector<string> levels;
	bool isRunning;
};

#endif