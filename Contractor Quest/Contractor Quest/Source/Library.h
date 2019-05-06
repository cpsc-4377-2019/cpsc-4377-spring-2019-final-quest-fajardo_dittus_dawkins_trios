#ifndef LIBRARY_H
#define LIBRARY_H


#include<string>
#include<map>
#include "ObjectFactory.h"
#include "Texture.h"
#include "SDL_mixer.h"

class SoundDevice;
class GraphicsDevice;

class Library {

public:
	Library(GraphicsDevice* graphicsDevice);
	~Library();

	map<string, Texture*> artLibrary;
	map<string, Mix_Chunk*> soundEffectLibrary;
	map<string, Mix_Music*> musicLibrary;
};

#endif