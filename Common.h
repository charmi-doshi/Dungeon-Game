// Common.h
#pragma once
#include <SDL3/SDL.h>

struct Point
{
    int x = 0, y = 0;
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};

enum class Terrain { Wall, Floor, StairsDown };

namespace Palette
{
    inline constexpr SDL_Color BG = { 12,  12,  18, 255 };
    inline constexpr SDL_Color WALL = { 60,  60,  80, 255 };
    inline constexpr SDL_Color FLOOR = { 80,  80, 100, 255 };
    inline constexpr SDL_Color EXPLORED = { 40,  40,  55, 255 };
    inline constexpr SDL_Color PLAYER = { 240, 240, 200, 255 };
    inline constexpr SDL_Color STAIRS = { 180, 160, 100, 255 };
}

static constexpr int MAP_W = 80;
static constexpr int MAP_H = 40;
static constexpr int CELL_W = 14;
static constexpr int CELL_H = 14;
static constexpr int WIN_W = MAP_W * CELL_W;
static constexpr int WIN_H = MAP_H * CELL_H + 60; 