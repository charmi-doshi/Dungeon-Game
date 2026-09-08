// MapGen.h
#pragma once
#include "Common.h"
#include "Map.h"
#include <vector>

struct BSPNode
{
    SDL_Rect region;
    SDL_Rect room = { 0, 0, 0, 0 };
    int      left = -1;
    int      right = -1;
};

class MapGen
{
public:
    static void generate(Map& map, int maxDepth = 4);

private:
    static void split(int idx, std::vector<BSPNode>& nodes, int depth, Map& map);
    static void placeRoom(int idx, std::vector<BSPNode>& nodes, Map& map);
    static void connectChildren(int idx, std::vector<BSPNode>& nodes, Map& map);
    static void createCorridor(Map& map, Point p1, Point p2);
    static Point getRoomCenter(const SDL_Rect& rect);
};