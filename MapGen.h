#pragma once

#include "Map.h"

class MapGen
{
public:
    // Helper function to invoke map generation and reset state
    static void generate(Map& map, int depth = 1, unsigned int seed = 0);
};