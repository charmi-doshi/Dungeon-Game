#include "MapGen.h"

void MapGen::generate(Map& map, int depth, unsigned int seed)
{
    // 1. Trigger Map's built-in procedural generation
    // Use cellular caves for deeper levels, BSP rooms for earlier ones
    if (depth >= 4) {
        map.generateCaves(seed);
    }
    else {
        map.generate(seed);
    }

    // 2. Ensure fog of war (explored state) is reset across the map
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            map.tiles[y][x].explored = false;
            map.tiles[y][x].visible = false;
        }
    }
}