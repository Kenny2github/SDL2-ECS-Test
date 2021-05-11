#pragma once
#include <unordered_map>
#include <unordered_set>

const int WIDTH = 800;
const int HEIGHT = 600;
const int FPS = 30;
const int SPEED = 5;

typedef std::unordered_map<std::string, std::unordered_set<int>> EventAttrs;