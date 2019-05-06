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
	//bool initialize(bool);
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
	//void draw();
	void Present();

	//void drawFilledCircle(Position position, EngineInt radius, RGBA RGBA);
	//bool drawBox(Position topLeft, Position bottomRight, RGBA RGBA);

	//void drawOverlay
	//(
	//	//round corner box that contains overlay
	//	Position topLeft, Position bottomRight, RGBA boxBackgroundColor, RGBA boxBorderColor,
	//	//any objects drawn in stated box
	//	//at given position
	//	std::map<Texture*, Position> objects

	//);

	//getters
	SDL_Renderer* getRenderer();

	//SDL_Window* getWindow();
	View* getView();

	//setters
	void setView(View* view);

	TTF_Font* font{ nullptr };
	SDL_Color color{ 0,0,0,255 };

private:
	EngineFloat Center(EngineFloat centerOn, EngineFloat width);
	//You need these!!! Mr. Orme.
	
	/*struct overlay
	{
		Position topLeft{ 0 };
		Position bottomRight{ 0 };
		RGBA boxBackgroundColor{ 0,0,0,0 };
		RGBA boxBorderColor{ 0,0,0,0 };
		std::map<Texture*, Position> objects;
	};

	std::vector<overlay> overlays;*/



};

#endif