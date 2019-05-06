#include "Library.h"
#include "Engine.h"
#include "Object.h"
#include "GraphicsDevice.h"

Library::Library(GraphicsDevice* graphicsDevice)
{	
	//Populate artLibrary
	//FIXME: commented out the sprites we don't have yet
	//artLibrary["BreakableBlock"] = new Texture(graphicsDevice, "./Assets/Images/BreakableBlock.png");
	artLibrary["Block"] = new Texture(graphicsDevice, "./Assets/Images/Block.png");
	artLibrary["CrazyPerson"] = new Texture(graphicsDevice, "./Assets/Images/CrazyPerson.png");
	artLibrary["CrazyPersonArm"] = new Texture(graphicsDevice, "./Assets/Images/CrazyPersonArm.png");
	artLibrary["Player"] = new Texture(graphicsDevice, "./Assets/Images/Player.png");
	artLibrary["RabidRacoon"] = new Texture(graphicsDevice, "./Assets/Images/RabidRacoon.png");
	artLibrary["Racoon"] = new Texture(graphicsDevice, "./Assets/Images/Racoon.png");
	artLibrary["Rock"] = new Texture(graphicsDevice, "./Assets/Images/Rock.png");

	soundEffectLibrary["walking"] = Mix_LoadWAV("./Assets/Sounds/walking.ogg");

	musicLibrary["background"] = Mix_LoadMUS("./Assets/Sounds/background.ogg");
}

Library::~Library() {

	//Delete textures from heap.
	//commented out the sprites we don't have yet
	delete artLibrary.at("Block");
	//delete artLibrary.at("BreakableBlock");
	delete artLibrary.at("CrazyPerson");
	delete artLibrary.at("Player");
	delete artLibrary.at("RabidRacoon");
	delete artLibrary.at("Racoon");
	delete artLibrary.at("Rock");

	//Empty artLibrary map
	artLibrary.clear();
	soundEffectLibrary.clear();
	musicLibrary.clear();

	//FIXME: will delete soundEffects and music from heap
}