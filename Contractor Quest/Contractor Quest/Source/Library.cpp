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
	artLibrary["CrazyPersonLeft"] = new Texture(graphicsDevice, "./Assets/Images/CrazyPersonLeft.png");
	artLibrary["CrazyPersonRight"] = new Texture(graphicsDevice, "./Assets/Images/CrazyPersonRight.png");
	artLibrary["CrazyPersonArm"] = new Texture(graphicsDevice, "./Assets/Images/CrazyPersonArm.png");
	artLibrary["Lunchbox"] = new Texture(graphicsDevice, "./Assets/Images/Lunchbox.png");
	artLibrary["PlayerLeft"] = new Texture(graphicsDevice, "./Assets/Images/PlayerLeft.png");
	artLibrary["PlayerRight"] = new Texture(graphicsDevice, "./Assets/Images/PlayerRight.png");
	artLibrary["RabidRacoonLeft"] = new Texture(graphicsDevice, "./Assets/Images/RabidRacoonLeft.png");
	artLibrary["RabidRacoonRight"] = new Texture(graphicsDevice, "./Assets/Images/RabidRacoonRight.png");
	artLibrary["RacoonLeft"] = new Texture(graphicsDevice, "./Assets/Images/RacoonLeft.png");
	artLibrary["RacoonRight"] = new Texture(graphicsDevice, "./Assets/Images/RacoonRight.png");
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
	delete artLibrary.at("CrazyPersonLeft");
	delete artLibrary.at("CrazyPersonRight");
	delete artLibrary.at("CrazyPersonArm");
	delete artLibrary.at("Concrete");
	delete artLibrary.at("Lunchbox");
	delete artLibrary.at("PlayerLeft");
	delete artLibrary.at("PlayerRight");
	delete artLibrary.at("RabidRacoonLeft");
	delete artLibrary.at("RabidRacoonRight");
	delete artLibrary.at("RacoonLeft");
	delete artLibrary.at("RacoonRight");
	delete artLibrary.at("Rock");
	delete artLibrary.at("Tree");
	delete artLibrary.at("SteelBeam");

	delete musicLibrary.at("background");

	delete soundEffectLibrary.at("walking");
	delete soundEffectLibrary.at("throwing");

	//Empty artLibrary map
	artLibrary.clear();
	soundEffectLibrary.clear();
	musicLibrary.clear();

}