#include "Systems.h"
#include "Consts.h"

Systems::Systems()
{
	window = SDL_CreateWindow(
		"Hello World!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, 0
	);
	renderer = SDL_CreateRenderer(
		window, -1,
		SDL_RENDERER_ACCELERATED
	);
}

Systems::~Systems()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Systems::Events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (
			event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE
		)) {
			stop = true;
			return;
		}
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			for (size_t i = 0; i < world.inputs.size(); ++i)
			{
				if (!world.HasComponent(i, Component::Size | Component::Position)) continue;
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					if (event.type == SDL_KEYDOWN)
						world.occupied[i].components = world.occupied[i].components & ~Component::Input;
					else
						world.occupied[i].components = world.occupied[i].components | Component::Input;
				}
			}
		}
	}
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	for (size_t i = 0; i < world.inputs.size(); ++i)
	{
		if (!world.HasComponent(i, Component::Velocity | Component::Input)) continue;
		if (keys[SDL_SCANCODE_UP]) {
			world.velocities[i].y = -SPEED;
		}
		if (keys[SDL_SCANCODE_DOWN]) {
			world.velocities[i].y = SPEED;
		}
		if (keys[SDL_SCANCODE_LEFT]) {
			world.velocities[i].x = -SPEED;
		}
		if (keys[SDL_SCANCODE_RIGHT]) {
			world.velocities[i].x = SPEED;
		}
	}
}

void Systems::Movement()
{
	for (size_t i = 0; i < world.inputs.size(); ++i)
	{
		if (!world.HasComponent(i, Component::Position | Component::Velocity)) continue;
		int signx = 0, signy = 0;
		if (world.velocities[i].x > 0) signx = -1;
		else if (world.velocities[i].x < 0) signx = 1;
		if (world.velocities[i].y > 0) signy = -1;
		else if (world.velocities[i].y < 0) signy = 1;
		world.velocities[i].x += signx;
		world.velocities[i].y += signy;
		world.positions[i].x += world.velocities[i].x;
		world.positions[i].y += world.velocities[i].y;
	}
}

void Systems::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_Rect rect = { 0, 0, 0, 0 };
	for (size_t i = 0; i < world.occupied.size(); ++i)
	{
		if (!(world.occupied[i].components & (Component::Position | Component::Size))) continue;
		rect.x = world.positions[i].x;
		rect.y = world.positions[i].y;
		rect.w = world.sizes[i].w;
		rect.h = world.sizes[i].h;
		SDL_RenderFillRect(renderer, &rect);
	}
	SDL_RenderPresent(renderer);
}

void Systems::Run()
{
	while (!stop)
	{
		Events();
		Movement();
		Render();
		SDL_Delay(1000 / FPS);
	}
}