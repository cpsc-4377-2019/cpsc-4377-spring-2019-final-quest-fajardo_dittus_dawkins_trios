#include<iostream>
#include "SDL2_gfxPrimitives.h"
#include "GraphicsDevice.h"
#include "View.h" 
#include "Texture.h"




GraphicsDevice::GraphicsDevice(Uint32 width, Uint32 height, bool fullScreen = true) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{

	//initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	
	}

	//initialize SDL_image subsystems
	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError());
	}

	//initialize SDL_ttf subsystems
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_Error: %s\n", TTF_GetError());
	}

	if (!fullScreen)
	{
		//Construct and check window construction
		screen = SDL_CreateWindow("Contractor Quest",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		screen = SDL_CreateWindow("Contractor Quest",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	}
	if (screen == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	//Construct the renderer
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	//initialize the background color (default of black).  Color is changed by load level.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//========================================
	//create view
	//========================================
	float posX = 0;
	float posY = 0;
	view = std::make_unique<View>(posX,posY);
}

GraphicsDevice::~GraphicsDevice()
{
	//Free the window
	SDL_DestroyWindow(screen);
	screen = nullptr;

	//Free renderer
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;


	//Quit SDL Subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool GraphicsDevice::ShutDown()
{
	//Free the window
	SDL_DestroyWindow(screen);
	screen = nullptr;

	//Free renderer
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;


	//Quit SDL Subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();


	return(true);
}

void GraphicsDevice::Begin()
{
	SDL_RenderClear(renderer);
}

void GraphicsDevice::Present()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* GraphicsDevice::getRenderer()
{
	return(renderer);
}

View * GraphicsDevice::getView()
{
	return view.get();
}

void GraphicsDevice::setView(View * view)
{
	this->view = std::unique_ptr<View>(view);
}

EngineFloat GraphicsDevice::Center(EngineFloat centerOn, EngineFloat width)
{


	EngineFloat point = (centerOn - width) / 2;

	return point;
}

void GraphicsDevice::changeBackground(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
