#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Definitions.h"

using namespace std;

class GraphicsDevice;

class Texture {

public:
	Texture();
	Texture(GraphicsDevice* gDevice, string levelPath, bool isSprite = true);
	~Texture();
	bool load(SDL_Texture* texture);
	void free();
	void draw(SDL_Renderer* renderer, Position position, EngineFloat angle, SDL_Rect* clip = NULL);
	int getWidth();
	int getHeight();
	bool initialized = false;

private:
	int width;
	int height;
	SDL_Texture* sprite;

};

#endif