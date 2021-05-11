#pragma once
#include <vector>
#include "Components.h"

class World
{
public:
	std::vector<Occupied> occupied;
	std::vector<Position> positions;
	std::vector<Velocity> velocities;
	std::vector<Size> sizes;
	std::vector<Input> inputs;

	bool HasComponent(size_t entity, Component component);

	void DestroyEntity(size_t entity);
	size_t CreateEntity();

	// Specific entity creators
	size_t CreateBox(int x, int y, int width, int height);
};