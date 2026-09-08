#pragma once
#include "Common.h"
#include "Map.h"
#include <cmath>

class FOV
{
public:
    
    static void compute(Map& map, Point origin, int radius);

private:
    
    static void castRay(Map& map, Point from, Point to);
};
