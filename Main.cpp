#include <cstdio>
#include <SDL2/SDL.h>
#include "Systems.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return -1;
	}
	
	Systems system;
	size_t box = system.world.CreateBox(50, 50, 100, 100);
	system.Run();

	SDL_Quit();
	return 0;
}