#pragma once
#include <SDL2/SDL.h>
#include "Entities.h"

class Systems
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool stop = false;

	void Events();
	void Movement();
	void Render();
public:
	World world;

	Systems();
	~Systems();
	void Run();
};

