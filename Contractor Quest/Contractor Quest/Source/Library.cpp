#include "Library.h"
#include "Engine.h"
#include "Object.h"
#include "GraphicsDevice.h"

Library::Library(GraphicsDevice* graphicsDevice)
{	
	//Populate artLibrary
	artLibrary["Block"] = new Texture(graphicsDevice, "./Assets/Images/Block.png");
	artLibrary["Building"] = new Texture(graphicsDevice, "./Assets/Images/Building.png");
	artLibrary["Concrete"] = new Texture(graphicsDevice, "./Assets/Images/Concrete.png");
	artLibrary["CrazyPerson"] = new Texture(graphicsDevice, "./Assets/Images/CrazyPerson.png");
	artLibrary["CrazyPersonArm"] = new Texture(graphicsDevice, "./Assets/Images/CrazyPersonArm.png");
	artLibrary["Lunchbox"] = new Texture(graphicsDevice, "./Assets/Images/Lunchbox.png");
	artLibrary["Player"] = new Texture(graphicsDevice, "./Assets/Images/Player.png");
	artLibrary["RabidRacoon"] = new Texture(graphicsDevice, "./Assets/Images/RabidRacoon.png");
	artLibrary["Racoon"] = new Texture(graphicsDevice, "./Assets/Images/Racoon.png");
	artLibrary["Rock"] = new Texture(graphicsDevice, "./Assets/Images/Rock.png");
	artLibrary["Tree"] = new Texture(graphicsDevice, "./Assets/Images/Tree.png");
	artLibrary["SteelBeam"] = new Texture(graphicsDevice, "./Assets/Images/SteelBeam.png");

	soundEffectLibrary["walking"] = Mix_LoadWAV("./Assets/Sounds/walking.ogg");
	soundEffectLibrary["throwing"] = Mix_LoadWAV("./Assets/Sounds/throwing.ogg");

	musicLibrary["background"] = Mix_LoadMUS("./Assets/Sounds/background.ogg");
}

Library::~Library() {

	//Delete textures from heap.
	
	delete artLibrary.at("Block");
	delete artLibrary.at("Building");
	delete artLibrary.at("CrazyPerson");
	delete artLibrary.at("CrazyPersonArm");
	delete artLibrary.at("Concrete");
	delete artLibrary.at("Lunchbox");
	delete artLibrary.at("Player");
	delete artLibrary.at("RabidRacoon");
	delete artLibrary.at("Racoon");
	delete artLibrary.at("Rock");
	delete artLibrary.at("Tree");
	delete artLibrary.at("SteelBeam");

	delete musicLibrary.at("background");
	delete soundEffectLibrary.at("walking");

	//Empty artLibrary map
	artLibrary.clear();
	soundEffectLibrary.clear();
	musicLibrary.clear();

}