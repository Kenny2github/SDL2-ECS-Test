#include <unordered_set>
#include "Entities.h"

bool World::HasComponent(size_t entity, Component component)
{
	return (bool)(occupied[entity].components & component);
}

void World::DestroyEntity(size_t entity)
{
	occupied[entity].components = Component::None;
}

size_t World::CreateEntity()
{
	for (size_t i = 0; i < occupied.size(); ++i)
	{
		if (occupied[i].components == Component::None) return i;
	}
	occupied.push_back(Occupied());
	positions.push_back(Position());
	velocities.push_back(Velocity());
	sizes.push_back(Size());
	inputs.push_back(Input());
	return occupied.size() - 1;
}

size_t World::CreateBox(int x, int y, int width, int height)
{
	size_t entity = CreateEntity();
	occupied[entity].components = Component::Position | Component::Size | Component::Input;
	positions[entity].x = x;
	positions[entity].y = y;
	sizes[entity].w = width;
	sizes[entity].h = height;
	return entity;
}
