#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <memory>
#include <vector>
#include <map>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Definitions.h"
#include "View.h"

class Texture;

class GraphicsDevice
{
public:

	//Constructors and Destructors
	GraphicsDevice(Uint32, Uint32,bool);
	~GraphicsDevice();

	//startup and Shutdown
	bool ShutDown();

	//Parameters
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;

	//create window and renderer
	SDL_Window* screen{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	std::unique_ptr<View> view{ nullptr };
	
	//Rendering functions
	void Begin();
	void Present();

	//getters
	SDL_Renderer* getRenderer();

	View* getView();

	//setters
	void setView(View* view);

	TTF_Font* font{ nullptr };
	SDL_Color color{ 0,0,0,255 };

	void changeBackground(Uint8, Uint8, Uint8, Uint8);

private:
	EngineFloat Center(EngineFloat centerOn, EngineFloat width);
};

#endif