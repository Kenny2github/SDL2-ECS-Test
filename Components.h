#pragma once
#include <unordered_set>
#include "Consts.h"
#include <SDL2/SDL.h>

enum class Component {
	None = 0,
	Position = 1 << 0,
	Velocity = 1 << 1,
	Size = 1 << 2,
	Input = 1 << 3
};

inline Component operator |(Component a, Component b)
{
	return static_cast<Component>(static_cast<int>(a) | static_cast<int>(b));
}

inline Component operator &(Component a, Component b)
{
	return static_cast<Component>(static_cast<int>(a) & static_cast<int>(b));
}

inline bool operator !(Component a)
{
	return !static_cast<int>(a);
}

inline Component operator ~(Component a)
{
	return static_cast<Component>(~static_cast<int>(a));
}

typedef struct Occupied {
	Component components;
	Occupied() : components(Component::None) {};
} Occupied;

typedef struct {
	int x;
	int y;
} Position;

typedef Position Velocity;

typedef struct {
	int w;
	int h;
} Size;

typedef struct {
} Input;